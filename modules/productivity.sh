#!/usr/bin/env bash
#===============================================================================
# Productivity Tools Module
#===============================================================================

install_productivity_tools() {
    log "=== Installing Productivity Tools ==="

    # ── Office ─────────────────────────────────────────────────────────────
    log "[1/3] Office tools..."
    pacman -S --needed --noconfirm \
        libreoffice-fresh \
        thunderbird \
        evince okular

    # ── Notes & Knowledge ──────────────────────────────────────────────────
    log "[2/3] Notes tools..."
    pacman -S --needed --noconfirm \
        obsidian

    yay -S --needed --noconfirm logseq 2>/dev/null || true
    yay -S --needed --noconfirm notion-app 2>/dev/null || true

    # ── Utilities ──────────────────────────────────────────────────────────
    log "[3/3] Utilities..."
    pacman -S --needed --noconfirm \
        htop btop \
        neofetch fastfetch \
        flameshot \
        timeshift \
        file-roller \
        seahorse \
        gpick

    log "Productivity tools installed successfully"
}

install_productivity_tools
