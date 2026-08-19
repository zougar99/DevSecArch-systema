#!/usr/bin/env bash
#===============================================================================
# Media Tools Module - Video, Audio, Graphics
#===============================================================================

install_media_tools() {
    log "=== Installing Media Tools ==="

    # ── Video Editing ──────────────────────────────────────────────────────
    log "[1/4] Video tools..."
    pacman -S --needed --noconfirm \
        ffmpeg obs-studio kdenlive \
        yt-dlp mediainfo HandBrake

    yay -S --needed --noconfirm shotcut 2>/dev/null || true
    yay -S --needed --noconfirm davinci-resolve 2>/dev/null || true

    # ── Audio ──────────────────────────────────────────────────────────────
    log "[2/4] Audio tools..."
    pacman -S --needed --noconfirm \
        audacity lmms \
        pavucontrol pulseaudio-utils \
        alsa-utils playerctl

    yay -S --needed --noconfirm Ardour 2>/dev/null || true

    # ── Graphics ───────────────────────────────────────────────────────────
    log "[3/4] Graphics tools..."
    pacman -S --needed --noconfirm \
        gimp inkscape imagemagick \
        darktable rawtherapee \
        blender

    yay -S --needed --noconfirm krita 2>/dev/null || true

    # ── Screenshots & Screen Recording ─────────────────────────────────────
    log "[4/4] Screenshot tools..."
    pacman -S --needed --noconfirm \
        flameshot spectacle grim slurp

    log "Media tools installed successfully"
}

install_media_tools
