#!/usr/bin/env bash
#===============================================================================
# Desktop Environments Module
#===============================================================================

install_desktops() {
    log "=== Installing Desktop Environments ==="

    # ── GNOME ──────────────────────────────────────────────────────────────
    log "Installing GNOME..."
    pacman -S --needed --noconfirm \
        gnome \
        gnome-extra \
        gdm \
        gnome-tweaks \
        gnome-terminal \
        gnome-system-monitor \
        nautilus \
        gnome-text-editor \
        dconf-editor \
        file-roller
    
    # ── KDE Plasma ─────────────────────────────────────────────────────────
    log "Installing KDE Plasma..."
    pacman -S --needed --noconfirm \
        plasma \
        plasma-desktop \
        kde-applications \
        konsole \
        dolphin \
        kate \
        ark \
        spectacle \
        kdeconnect \
        sddm \
        packagekit-qt6 \
        plasma-nm \
        plasma-pa \
        plasma-workspace-wallpapers
    
    # ── i3 Window Manager ──────────────────────────────────────────────────
    log "Installing i3wm + tools..."
    pacman -S --needed --noconfirm \
        i3-wm \
        i3blocks \
        i3lock \
        i3status \
        dmenu \
        rofi \
        dunst \
        picom \
        feh \
        nitrogen \
        polybar \
        lxappearance \
        xfce4-terminal \
        thunar \
        thunar-archive-plugin \
        thunar-volman \
        ranger
    
    # ── Sway (Wayland tiling) ──────────────────────────────────────────────
    log "Installing Sway..."
    pacman -S --needed --noconfirm \
        sway \
        swaybg \
        swaylock \
        swayidle \
        wl-clipboard \
        waybar \
        wofi \
        mako \
        grim \
        slurp \
        kanshi \
        xdg-desktop-portal-wlr
    
    # ── COSMIC Desktop (Pop!_OS) ───────────────────────────────────────────
    log "Installing COSMIC Desktop..."
    if yay -S --needed --noconfirm cosmic-session 2>/dev/null || \
       paru -S --needed --noconfirm cosmic-session 2>/dev/null; then
        log "COSMIC installed via AUR"
    else
        warn "COSMIC not available in AUR, skipping"
    fi
    
    # ── Display Manager (LightDM is default for ForxoOS) ─────────────────
    log "Configure your preferred display manager (LightDM recommended)..."

    log "Desktop Environments installed successfully"
}

install_desktops
