#!/usr/bin/env bash
#===============================================================================
# Privacy & Security Tools Module - Hardening & Encryption Stack
#===============================================================================

install_privacy_tools() {
    log "=== Installing Privacy & Security Tools ==="

    # ── Encryption & Keys ──────────────────────────────────────────────────
    log "[1/7] GPG, Veracrypt, KeePassXC..."
    pacman -S --needed --noconfirm \
        gnupg keepassxc veracrypt

    # ── Encrypted Messaging ────────────────────────────────────────────────
    log "[2/7] Signal & Thunderbird..."
    pacman -S --needed --noconfirm \
        thunderbird

    yay -S --needed --noconfirm signal-desktop 2>/dev/null || true

    # ── Tor & Anonymity ────────────────────────────────────────────────────
    log "[3/7] Tor Browser & OnionShare..."
    yay -S --needed --noconfirm torbrowser-launcher 2>/dev/null || true
    yay -S --needed --noconfirm onionshare 2>/dev/null || true
    yay -S --needed --noconfirm onionshare-cli 2>/dev/null || true

    pacman -S --needed --noconfirm \
        tor torsocks

    systemctl enable --now tor 2>/dev/null || true

    # ── Firewall & Network Security ────────────────────────────────────────
    log "[4/7] UFW, Firejail..."
    pacman -S --needed --noconfirm \
        ufw firejail

    systemctl enable ufw 2>/dev/null || true

    # ── Antivirus & Cleaning ───────────────────────────────────────────────
    log "[5/7] ClamAV, BleachBit, MAT2..."
    pacman -S --needed --noconfirm \
        clamav

    yay -S --needed --noconfirm bleachbit 2>/dev/null || true
    yay -S --needed --noconfirm mat2 2>/dev/null || true

    systemctl enable clamav-freshclam 2>/dev/null || true

    # ── Steganography ──────────────────────────────────────────────────────
    log "[6/7] Steghide..."
    pacman -S --needed --noconfirm \
        steghide

    # ── Hardware Tokens ────────────────────────────────────────────────────
    log "[7/7] Nitrokey tools..."
    pacman -S --needed --noconfirm \
        libnitrokey nk3-tools nk3-host-software

    yay -S --needed --noconfirm pynitrokey 2>/dev/null || true
    yay -S --needed --noconfirm nitrokey-app 2>/dev/null || true

    log "Privacy & security tools installed successfully"
}

install_privacy_tools
