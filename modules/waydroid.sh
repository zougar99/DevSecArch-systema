#!/usr/bin/env bash
#===============================================================================
# ForxoOS - Android Support Module (Waydroid)
# Runs Android apps (.apk) inside ForxoOS via a full Android container
#===============================================================================

set -euo pipefail

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m'

check_root() {
    if [[ $EUID -ne 0 ]]; then
        echo -e "${RED}[!] Run as root: sudo bash modules/waydroid.sh${NC}"
        exit 1
    fi
}

check_kernel() {
    echo -e "${CYAN}[1/6] Checking kernel modules...${NC}"

    # Waydroid needs binder_linux + ashmem (or binderfs)
    modprobe binder_linux 2>/dev/null || true
    modprobe ashmem_linux 2>/dev/null || true

    if ! ls /dev/binder* 2>/dev/null | grep -q binder; then
        echo -e "${YELLOW}binder not loaded. Attempting binderfs...${NC}"
        mkdir -p /dev/binderfs
        mount -t binder binder /dev/binderfs 2>/dev/null || true
    fi

    echo -e "${GREEN}Kernel check done (may need reboot if modules are missing)${NC}"
}

install_waydroid() {
    echo -e "${CYAN}[2/6] Installing Waydroid...${NC}"

    # Waydroid is in AUR. Try yay/paru first, else flatpak.
    if command -v yay &>/dev/null; then
        echo -e "${YELLOW}Installing waydroid via yay...${NC}"
        sudo -u "$SUDO_USER" yay -S --noconfirm waydroid
    elif command -v paru &>/dev/null; then
        echo -e "${YELLOW}Installing waydroid via paru...${NC}"
        sudo -u "$SUDO_USER" paru -S --noconfirm waydroid
    else
        echo -e "${YELLOW}No AUR helper. Installing deps + building waydroid...${NC}"
        pacman -S --needed --noconfirm \
            python python-pip python-pyclip \
            libevdev libgbm lxc gst-plugins-base \
            gst-plugins-good gst-plugins-bad \
            meson extra-cmake-modules wayland-protocols \
            ninja base-devel git

        # Clone + build waydroid (AUR PKGBUILD)
        if [ ! -d /tmp/waydroid-aur ]; then
            git clone https://aur.archlinux.org/waydroid.git /tmp/waydroid-aur
        fi
        cd /tmp/waydroid-aur
        makepkg -si --noconfirm
        cd -
    fi

    echo -e "${GREEN}Waydroid installed${NC}"
}

init_waydroid() {
    echo -e "${CYAN}[3/6] Initializing Android container...${NC}"

    # Download the Android images (GAPPS by default)
    if ! waydroid init 2>&1 | tee /tmp/waydroid-init.log; then
        echo -e "${YELLOW}Default init failed, trying GAPPS variant...${NC}"
        waydroid init -s GAPPS || true
    fi

    echo -e "${GREEN}Android container initialized${NC}"
}

install_apk_helper() {
    echo -e "${CYAN}[4/6] Creating apk helper scripts...${NC}"

    # Install .apk helper
    cat > /usr/local/bin/install-apk << 'HELPER'
#!/bin/bash
# install-apk - Install an Android .apk into Waydroid
if [ -z "$1" ]; then
    echo "Usage: install-apk <file.apk>"
    exit 1
fi
if [ ! -f "$1" ]; then
    echo "Error: File not found: $1"
    exit 1
fi
echo "Installing APK into Android container..."
waydroid app install "$1" && echo "Installed successfully!" || echo "Failed to install"
HELPER
    chmod +x /usr/local/bin/install-apk

    # Launch app by package name helper
    cat > /usr/local/bin/run-apk << 'HELPER'
#!/bin/bash
# run-apk - Launch an Android app by package name in Waydroid
if [ -z "$1" ]; then
    echo "Usage: run-apk <package.name>"
    echo "List apps: waydroid app list"
    exit 1
fi
waydroid show-full-ui &
sleep 2
waydroid session_manager start
waydroid app launch "$1"
HELPER
    chmod +x /usr/local/bin/run-apk

    echo -e "${GREEN}Helpers created: install-apk, run-apk${NC}"
}

enable_service() {
    echo -e "${CYAN}[5/6] Enabling Waydroid service...${NC}"

    systemctl enable waydroid-container 2>/dev/null || true

    echo -e "${GREEN}Waydroid container service enabled${NC}"
}

summary() {
    echo -e "${CYAN}[6/6] Done${NC}"
    echo ""
    echo -e "${GREEN}========================================${NC}"
    echo -e "${GREEN}  Waydroid Android installed!${NC}"
    echo -e "${GREEN}========================================${NC}"
    echo ""
    echo "  Usage:"
    echo "    Start Android:      waydroid show-full-ui"
    echo "    Install .apk:       install-apk myapp.apk"
    echo "    Or double-click .apk → Open with install-apk"
    echo "    Launch by name:     run-apk com.whatsapp"
    echo ""
    echo "  Or open from the ForxoOS Store:"
    echo "    Android category → install directly"
    echo ""
    echo "  Note:"
    echo "    - Needs binder kernel module. If missing, reboot after install."
    echo "    - Waydroid runs a full Android container (like an emulator)."
    echo "    - Some apps need Google Play services (use GAPPS variant)."
    echo ""
}

# MIME for .apk → install-apk
register_mime() {
    echo -e "${YELLOW}Registering .apk MIME types...${NC}"
    mkdir -p ~/.local/share/applications

    cat > ~/.local/share/applications/install-apk.desktop << 'DESKTOP'
[Desktop Entry]
Name=Install APK (Waydroid)
Comment=Install Android app into Waydroid container
Exec=install-apk %f
Icon=waydroid
Terminal=false
Type=Application
Categories=Utility;
MimeType=application/vnd.android.package-archive;
NoDisplay=true
DESKTOP

    # Register .apk mime type
    mkdir -p ~/.local/share/mime/packages
    cat > ~/.local/share/mime/packages/apk.xml << 'XML'
<?xml version="1.0" encoding="UTF-8"?>
<mime-info xmlns="http://www.freedesktop.org/standards/shared-mime-info">
  <mime-type type="application/vnd.android.package-archive">
    <comment>Android package</comment>
    <glob pattern="*.apk"/>
    <glob pattern="*.APK"/>
    <icon name="application-vnd.android.package-archive"/>
  </mime-type>
</mime-info>
XML
    update-mime-database ~/.local/share/mime 2>/dev/null || true
    xdg-mime default install-apk.desktop application/vnd.android.package-archive 2>/dev/null || true

    echo -e "${GREEN}APK MIME types registered${NC}"
}

# Install .apk MIME into airootfs too for the ISO
register_mime_system() {
    mkdir -p /usr/share/mime/packages
    cat > /usr/share/mime/packages/apk.xml << 'XML'
<?xml version="1.0" encoding="UTF-8"?>
<mime-info xmlns="http://www.freedesktop.org/standards/shared-mime-info">
  <mime-type type="application/vnd.android.package-archive">
    <comment>Android package</comment>
    <glob pattern="*.apk"/>
    <glob pattern="*.APK"/>
  </mime-type>
</mime-info>
XML
    update-mime-database /usr/share/mime 2>/dev/null || true
    echo -e "${GREEN}System APK MIME registered${NC}"
}

main() {
    check_root
    echo -e "${CYAN}"
    echo "  ╔══════════════════════════════════════════╗"
    echo "  ║     ForxoOS - Android (Waydroid)         ║"
    echo "  ╚══════════════════════════════════════════╝"
    echo -e "${NC}"
    echo ""

    check_kernel
    install_waydroid
    init_waydroid
    install_apk_helper
    register_mime
    register_mime_system
    enable_service
    summary
}

main
