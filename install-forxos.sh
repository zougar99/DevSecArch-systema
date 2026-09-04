#!/usr/bin/env bash
#===============================================================================
# ForxoOS - Full Automated Installer
# Run from Arch Linux LIVE: curl -sL ... | bash
# Erases target disk, installs Arch + Deepin DDE + ForxoOS desktop
#===============================================================================

set -euo pipefail

VERSION="2.0.0"
TARGET="/mnt"
DISK="${1:-/dev/sda}"
USERNAME="forxo"
PASSWORD="forxo"
ROOT_PASS="forxo"
HOSTNAME="forxos"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m'

log()  { echo -e "${GREEN}[+]${NC} $1"; }
warn() { echo -e "${YELLOW}[!]${NC} $1"; }
err()  { echo -e "${RED}[x]${NC} $1"; exit 1; }

banner() {
    echo -e "${CYAN}"
    echo "  ███████╗ ██████╗ ██████╗ ██╗  ██╗ ██████╗  ██████╗ ███████╗"
    echo "  ██╔════╝██╔═══██╗██╔══██╗╚██╗██╔╝██╔═══██╗██╔═══██╗██╔════╝"
    echo "  █████╗  ██║   ██║██████╔╝ ╚███╔╝ ██║   ██║██║   ██║███████╗"
    echo "  ██╔══╝  ██║   ██║██╔══██╗ ██╔██╗ ██║   ██║██║   ██║╚════██║"
    echo "  ██║     ╚██████╔╝██║  ██║██╔╝ ██╗╚██████╔╝╚██████╔╝███████║"
    echo "  ╚═╝      ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝  ╚═════╝ ╚══════╝"
    echo -e "${NC}"
    echo -e "${CYAN}  ForxoOS Installer v${VERSION} — Your machine. Your rules.${NC}"
    echo ""
}

check_root() {
    [[ $EUID -eq 0 ]] || err "Run as root: sudo ./install-forxos.sh"
}

detect_disk() {
    log "Available disks:"
    lsblk -dno NAME,SIZE,TYPE | grep disk
    echo ""
    if [[ ! -b "$DISK" ]]; then
        warn "Disk $DISK not found, using first disk"
        DISK="/dev/$(lsblk -dno NAME | head -1)"
    fi
    log "Target disk: $DISK ($(lsblk -dno SIZE $DISK | head -1))"
    echo ""
    echo -e "${RED}  *** THIS WILL ERASE ALL DATA ON $DISK ***${NC}"
    read -rp "  Type ERASE to confirm: " confirm
    [[ "$confirm" == "ERASE" ]] || { echo "Aborted."; exit 0; }
}

detect_efi() {
    if [[ -d /sys/firmware/efi ]]; then
        EFI_MODE="uefi"
        log "EFI mode detected"
    else
        EFI_MODE="bios"
        log "BIOS/legacy mode detected"
    fi
}

partition_disk() {
    log "Partitioning $DISK ($EFI_MODE)..."

    # Wipe disk
    wipefs -af "$DISK" &>/dev/null || true
    sgdisk --zap-all "$DISK" &>/dev/null || true
    sleep 1

    if [[ "$EFI_MODE" == "uefi" ]]; then
        parted -s "$DISK" -- \
            mklabel gpt \
            mkpart ESP fat32 1MiB 513MiB \
            set 1 esp on \
            mkpart primary ext4 513MiB 100%
    else
        parted -s "$DISK" -- \
            mklabel msdos \
            mkpart primary ext4 1MiB 513MiB \
            set 1 boot on \
            mkpart primary ext4 513MiB 100%
    fi

    sleep 2

    if [[ "$EFI_MODE" == "uefi" ]]; then
        ESP="${DISK}1"
        ROOT="${DISK}2"
        mkfs.fat -F32 "$ESP"
    else
        BOOT="${DISK}1"
        ROOT="${DISK}2"
        mkfs.ext4 -F "$BOOT"
    fi

    mkfs.ext4 -F "$ROOT"
    log "Partitions created"
}

mount_partitions() {
    log "Mounting partitions..."
    mount "$ROOT" "$TARGET"

    if [[ "$EFI_MODE" == "uefi" ]]; then
        mkdir -p "$TARGET/boot"
        mount "$ESP" "$TARGET/boot"
    else
        mkdir -p "$TARGET/boot"
        mount "$BOOT" "$TARGET/boot"
    fi

    log "Partitions mounted"
}

install_base() {
    log "Installing base system with pacstrap..."
    pacstrap "$TARGET" base linux linux-firmware \
        base-devel git curl wget vim nano htop btop tmux \
        zsh fish man-pages sudo networkmanager network-manager-applet \
        wpa_supplicant openssh rsync zip unzip p7zip \
        reflector xdg-utils xdg-user-dirs \
        polkit gnome-keyring bash-completion \
        --noconfirm

    log "Base system installed"
}

generate_fstab() {
    log "Generating fstab..."
    genfstab -U "$TARGET" >> "$TARGET/etc/fstab"
    log "fstab generated"
}

chroot_config() {
    log "Configuring system (chroot)..."

    arch-chroot "$TARGET" /bin/bash <<CHROOT_EOF
set -euo pipefail

# Timezone
ln -sf /usr/share/zoneinfo/Casablanca /etc/localtime
hwclock --systohc

# Locale
echo "en_US.UTF-8 UTF-8" >> /etc/locale.gen
echo "ar_MA.UTF-8 UTF-8" >> /etc/locale.gen
locale-gen
echo "LANG=en_US.UTF-8" > /etc/locale.conf

# Hostname
echo "$HOSTNAME" > /etc/hostname
echo "127.0.1.1 $HOSTNAME" >> /etc/hosts

# Root password
echo "root:$ROOT_PASS" | chpasswd

# User
useradd -m -G wheel,audio,video,storage,power -s /bin/bash "$USERNAME"
echo "$USERNAME:$PASSWORD" | chpasswd
echo "%wheel ALL=(ALL:ALL) NOPASSWD" >> /etc/sudoers.d/wheel

# Network
systemctl enable NetworkManager
systemctl enable sshd

# Initramfs
mkinitcpio -P

echo "Base config done"
CHROOT_EOF

    log "System configured"
}

install_desktop() {
    log "Installing Deepin DDE + Qt6 desktop..."

    arch-chroot "$TARGET" /bin/bash <<'DESKTOP_EOF'
set -euo pipefail

# Enable multilib for Wine
sed -i '/^\[multilib\]/,/Include/s/^#//' /etc/pacman.conf
pacman -Syu --noconfirm

# Deepin Desktop Environment (individual packages)
pacman -S --needed --noconfirm \
    deepin-dde \
    deepin-dde-daemon \
    deepin-dde-session-ui \
    deepin-dde-dock \
    deepin-dde-launcher \
    deepin-dde-file-manager \
    deepin-dde-control-center \
    deepin-dde-terminal \
    deepin-dde-wallpaper-engine \
    deepin-dde-network-utils \
    deepin-dde-appearance \
    deepin-dde-grand-search \
    deepin-image-viewer \
    deepin-music \
    deepin-movie \
    deepin-screenshot \
    deepin-editor \
    deepin-calculator \
    deepin-picker \
    deepin-polkit-agent \
    dde-api \
    dde-qt5-wayland \
    lightdm \
    lightdm-deepin-greeter

# Qt6 packages for ForxoOS desktop
pacman -S --needed --noconfirm \
    qt6-base qt6-declarative qt6-charts qt6-svg \
    qt6-networkauth qt6-speech qt6-imageformats \
    cmake extra-cmake-modules

# Wine + Windows compat (multilib)
pacman -S --needed --noconfirm \
    wine wine-gecko wine-mono winetricks \
    lib32-vulkan-icd-loader vulkan-tools mesa lib32-mesa

# Fonts
pacman -S --needed --noconfirm \
    noto-fonts noto-fonts-cjk noto-fonts-arab \
    ttf-jetbrains-mono ttf-dejavu ttf-liberation \
    ttf-sora ttf-outfit

# Enable display manager
systemctl enable lightdm

echo "Desktop installed"
DESKTOP_EOF

    log "Desktop installed"
}

install_forxoos() {
    log "Installing ForxoOS components..."

    arch-chroot "$TARGET" /bin/bash <<'FORXO_EOF'
set -euo pipefail

cd /opt

# Clone repo
if [[ ! -d DevSecArch-systema ]]; then
    git clone https://github.com/zougar99/DevSecArch-systema.git
fi
cd DevSecArch-systema

# Build desktop app
cd desktop
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)
cp build/ForxoOS-Desktop /usr/local/bin/
chmod +x /usr/local/bin/ForxoOS-Desktop
cd ..

# Build installer
cd installer
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)
cp build/ForxoOS-Installer /usr/local/bin/
chmod +x /usr/local/bin/ForxoOS-Installer
cd ../..

# Install assets
cp -r DevSecArch-systema/desktop/resources/icons/forxoos-logo.svg /usr/share/pixmaps/forxoos.svg
cp -r DevSecArch-systema/desktop/resources/icons/forxoos-wordmark.svg /usr/share/pixmaps/
cp -r DevSecArch-systema/desktop/resources/wallpaper/forxoos-wallpaper.svg /usr/share/wallpapers/forxoos/
cp -r DevSecArch-systema/desktop/resources/theme.qss /usr/share/forxoos/

# Install os-release
cp DevSecArch-systema/iso/profile/airootfs/etc/os-release /etc/os-release
cp DevSecArch-systema/iso/profile/airootfs/etc/motd /etc/motd
cp DevSecArch-systema/iso/profile/airootfs/etc/issue /etc/issue

# .bashrc / .zshrc aliases
cat >> /home/$SUDO_USER/.bashrc <<'ALIAS'

# ForxoOS aliases
alias forxoinstall='sudo /opt/DevSecArch-systema/install.sh'
alias forxoupdate='sudo pacman -Syu'
alias forxostore='/usr/local/bin/ForxoOS-Desktop'
alias run-exe='wine'
ALIAS

# Desktop entry
mkdir -p /usr/share/applications
cat > /usr/share/applications/forxoos.desktop <<'DESKTOP'
[Desktop Entry]
Type=Application
Name=ForxoOS
Comment=ForxoOS iOS Desktop Shell
Exec=/usr/local/bin/ForxoOS-Desktop
Icon=/usr/share/pixmaps/forxoos.svg
Terminal=false
Categories=System;Utility;
DESKTOP

cat > /usr/share/applications/forxoinstaller.desktop <<'INSTALLER'
[Desktop Entry]
Type=Application
Name=ForxoOS Installer
Comment=Install ForxoOS Linux
Exec=/usr/local/bin/ForxoOS-Installer
Icon=/usr/share/pixmaps/forxoos.svg
Terminal=false
Categories=System;
INSTALLER

# Fix ownership
chown -R $SUDO_USER:$SUDO_USER /home/$SUDO_USER/.bashrc
chown -R $SUDO_USER:$SUDO_USER /home/$SUDO_USER/.zshrc 2>/dev/null || true

echo "ForxoOS components installed"
FORXO_EOF

    log "ForxoOS components installed"
}

cleanup() {
    log "Cleaning up..."
    umount -R "$TARGET" 2>/dev/null || true
    log "Done! Reboot to use ForxoOS."
}

main() {
    banner
    check_root
    detect_disk
    detect_efi
    partition_disk
    mount_partitions
    install_base
    generate_fstab
    chroot_config
    install_desktop
    install_forxoos

    echo ""
    echo -e "${GREEN}============================================${NC}"
    echo -e "${GREEN}  ForxoOS v${VERSION} Installed Successfully!${NC}"
    echo -e "${GREEN}============================================${NC}"
    echo ""
    echo -e "  User:     ${CYAN}${USERNAME}${NC}"
    echo -e "  Password: ${CYAN}${PASSWORD}${NC}"
    echo -e "  Root:     ${CYAN}root / ${ROOT_PASS}${NC}"
    echo ""
    echo -e "  Reboot:   ${CYAN}sudo reboot${NC}"
    echo ""

    read -rp "Reboot now? [Y/n]: " rb
    if [[ "${rb:-Y}" =~ ^[Yy]$ ]]; then
        cleanup
        reboot
    else
        cleanup
    fi
}

main "$@"
