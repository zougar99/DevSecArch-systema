#!/usr/bin/env bash
#===============================================================================
# Windows Compatibility Module - Wine, Proton, PDF, Everything
#===============================================================================

install_windows_compat() {
    log "=== Installing Windows Compatibility Tools ==="

    # ── Wine ───────────────────────────────────────────────────────────────
    log "[1/8] Wine..."
    pacman -S --needed --noconfirm \
        wine wine-gecko wine-mono \
        winetricks

    yay -S --needed --noconfirm wine-staging 2>/dev/null || true

    # ── Proton (Steam Play) ───────────────────────────────────────────────
    log "[2/8] Proton + Steam..."
    yay -S --needed --noconfirm steam 2>/dev/null || true

    # Proton-GE (better compatibility)
    yay -S --needed --noconfirm proton-ge-custom 2>/dev/null || true

    # ── PlayOnLinux / Bottles ──────────────────────────────────────────────
    log "[3/8] Wine frontends..."
    yay -S --needed --noconfirm bottles 2>/dev/null || true
    yay -S --needed --noconfirm playonlinux 2>/dev/null || true
    yay -S --needed --noconfirm crossover 2>/dev/null || true

    # ── QEMU/KVM (run full Windows if needed) ─────────────────────────────
    log "[4/8] QEMU/KVM virtual machines..."
    pacman -S --needed --noconfirm \
        qemu-full virt-manager \
        bridge-utils dnsmasq \
        ebtables libvirt

    systemctl enable libvirtd 2>/dev/null || true
    systemctl start libvirtd 2>/dev/null || true
    usermod -aG libvirt "$SUDO_USER" 2>/dev/null || true

    # ── PDF Readers ────────────────────────────────────────────────────────
    log "[5/8] PDF readers & editors..."
    pacman -S --needed --noconfirm \
        evince okular zathura \
        poppler poppler-glib \
        mupdf

    yay -S --needed --noconfirm foxit-reader 2>/dev/null || true
    yay -S --needed --noconfirm masterpdfeditor 2>/dev/null || true

    # ── Office Compatibility ───────────────────────────────────────────────
    log "[6/8] Office compatibility..."
    pacman -S --needed --noconfirm \
        libreoffice-fresh \
        thunderbird

    # Microsoft fonts for perfect rendering
    pacman -S --needed --noconfirm ttf-ms-fonts 2>/dev/null || true
    yay -S --needed --noconfirm ttf-ms-win10-auto 2>/dev/null || true
    yay -S --needed --noconfirm ttf-windows 2>/dev/null || true

    # ── Media Codecs (play everything) ─────────────────────────────────────
    log "[7/8] Media codecs..."
    pacman -S --needed --noconfirm \
        ffmpeg gst-plugins-good gst-plugins-bad \
        gst-plugins-ugly gst-libav \
        gst-plugin-pipewire \
        gstreamer \
        vlc mpv celluloid \
        playerctl

    # ── Graphics / Design (Photoshop alternatives) ─────────────────────────
    log "[8/8] Graphics & design tools..."
    pacman -S --needed --noconfirm \
        gimp inkscape blender \
        darktable rawtherapee

    yay -S --needed --noconfirm krita 2>/dev/null || true
    yay -S --needed --noconfirm davinci-resolve 2>/dev/null || true

    # ── Optional: Run .exe helper script ───────────────────────────────────
    log "Creating run-exe helper..."
    cat > /usr/local/bin/run-exe << 'RUNEOF'
#!/bin/bash
# Quick .exe runner - usage: run-exe file.exe
if [[ -z "$1" ]]; then
    echo "Usage: run-exe <file.exe>"
    exit 1
fi

if [[ ! -f "$1" ]]; then
    echo "File not found: $1"
    exit 1
fi

echo "Running with Wine..."
wine "$1"
RUNEOF
    chmod +x /usr/local/bin/run-exe

    # ── PDF viewer helper ──────────────────────────────────────────────────
    cat > /usr/local/bin/open-pdf << 'PDFFEOF'
#!/bin/bash
# Quick PDF opener
if [[ -z "$1" ]]; then
    echo "Usage: open-pdf <file.pdf>"
    exit 1
fi

if command -v zathura &>/dev/null; then
    zathura "$1" &
elif command -v okular &>/dev/null; then
    okular "$1" &
elif command -v evince &>/dev/null; then
    evince "$1" &
elif command -v mupdf &>/dev/null; then
    mupdf "$1" &
else
    xdg-open "$1"
fi
PDFFEOF
    chmod +x /usr/local/bin/open-pdf

    log "Windows compatibility tools installed successfully"
}

install_windows_compat
