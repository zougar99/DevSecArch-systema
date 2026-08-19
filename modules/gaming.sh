#!/usr/bin/env bash
#===============================================================================
# Gaming Tools Module - Gaming & Emulation Stack
#===============================================================================

install_gaming_tools() {
    log "=== Installing Gaming Tools ==="

    # ── Steam & Proton ─────────────────────────────────────────────────────
    log "[1/6] Steam & Proton..."
    pacman -S --needed --noconfirm \
        steam steam-native-runtime protontricks

    # ── Wine & DXVK ────────────────────────────────────────────────────────
    log "[2/6] Wine & DXVK..."
    pacman -S --needed --noconfirm \
        wine wine-gecko wine-mono gifsicle

    yay -S --needed --noconfirm dxvk-bin 2>/dev/null || true
    yay -S --needed --noconfirm dxvk-winelib-bin 2>/dev/null || true

    # ── Lutris & Launchers ─────────────────────────────────────────────────
    log "[3/6] Lutris & Launchers..."
    yay -S --needed --noconfirm lutris 2>/dev/null || true
    yay -S --needed --noconfirm legendary-bin 2>/dev/null || true
    yay -S --needed --noconfirm heroic-games-launcher-bin 2>/dev/null || true
    yay -S --needed --noconfirm launcher 2>/dev/null || true

    # ── Performance & Overlay ──────────────────────────────────────────────
    log "[4/6] MangoHud & Gamemode..."
    pacman -S --needed --noconfirm \
        mangohud lib32-mangohud gamemode lib32-gamemode \
        mesa lib32-mesa vulkan-intel lib32-vulkan-intel \
        vulkan-radeon lib32-vulkan-radeon libva-mesa-driver

    # ── Emulation ──────────────────────────────────────────────────────────
    log "[5/6] RetroArch & Emulators..."
    pacman -S --needed --noconfirm \
        retroarch

    yay -S --needed --noconfirm retroarch-assets-ozone 2>/dev/null || true
    yay -S --needed --noconfirm dolphin-emu 2>/dev/null || true
    yay -S --needed --noconfirm pcsx2-bin 2>/dev/null || true
    yay -S --needed --noconfirm rpcs3-bin 2>/dev/null || true
    yay -S --needed --noconfirm yuzu-bin 2>/dev/null || true
    yay -S --needed --noconfirm citra-bin 2>/dev/null || true
    yay -S --needed --noconfirm melonDS 2>/dev/null || true
    yay -S --needed --noconfirm mupen64plus 2>/dev/null || true
    yay -S --needed --noconfirm bsnes-hd 2>/dev/null || true
    yay -S --needed --noconfirm snes9x 2>/dev/null || true
    yay -S --needed --noconfirm fceux 2>/dev/null || true
    yay -S --needed --noconfirm mgba 2>/dev/null || true

    # ── Streaming & Communication ──────────────────────────────────────────
    log "[6/6] OBS & Discord..."
    pacman -S --needed --noconfirm \
        obs-studio discord

    yay -S --needed --noconfirm obs-vkcapture 2>/dev/null || true

    log "Gaming tools installed successfully"
}

install_gaming_tools
