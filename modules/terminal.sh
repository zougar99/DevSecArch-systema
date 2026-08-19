#!/usr/bin/env bash
#===============================================================================
# Terminal Enhancement Tools Module
#===============================================================================

install_terminal_tools() {
    log "=== Installing Terminal Enhancement Tools ==="

    # ── Shell Enhancement ──────────────────────────────────────────────────
    log "Installing shell enhancement tools..."
    pacman -S --needed --noconfirm \
        zsh \
        zsh-completions \
        zsh-autosuggestions \
        zsh-syntax-highlighting \
        zsh-history-substring-search \
        fzf \
        zoxide \
        bat \
        exa \
        lsd \
        fd \
        ripgrep \
        sd \
        procs \
        dust \
        duf \
        btop \
        bottom \
        hyperfine \
        tokei \
        hyperfine \
        hexyl \
        dog \
        doggo \
        xh

    # ── Terminal Multiplexers ───────────────────────────────────────────────
    log "Installing terminal multiplexers..."
    pacman -S --needed --noconfirm \
        tmux \
        screen

    # ── Modern CLI Tools ───────────────────────────────────────────────────
    log "Installing modern CLI tools..."
    pacman -S --needed --noconfirm \
        starship \
        atuin \
        just \
        watchexec \
        httpie \
        jq \
        yq \
        yq-go \
        gron \
        htmlq \
        jq-git \
        miller \
        choose \
        pastel \
        grex \
        sd \
        ruplacer \
        committed \
        git-delta \
        delta

    # ── File Managers ──────────────────────────────────────────────────────
    log "Installing file managers..."
    pacman -S --needed --noconfirm \
        ranger \
        nnn \
        mc \
        vifm \
        lf \
        thunar \
        dolphin \
        nautilus \
        pcmanfm

    # ── System Monitoring ──────────────────────────────────────────────────
    log "Installing system monitoring tools..."
    pacman -S --needed --noconfirm \
        htop \
        btop \
        bottom \
        glances \
        gotop \
        gping \
        nload \
        iftop \
        nethogs \
        iotop \
        dstat \
        glances \
        nvtop

    # ── Git Enhancement ────────────────────────────────────────────────────
    log "Installing git enhancement tools..."
    pacman -S --needed --noconfirm \
        lazygit \
        gitui \
        tig \
        git-delta \
        git-lfs \
        pre-commit

    # ── Productivity ───────────────────────────────────────────────────────
    log "Installing productivity tools..."
    pacman -S --needed --noconfirm \
        obsidian \
        notion-app \
        slack-desktop \
        discord \
        telegram-desktop \
        signal-desktop \
        thunderbird \
        firefox \
        chromium \
        keepassxc \
        syncthing \
        nextcloud-client \
        obs-studio \
        gimp \
        inkscape \
        blender \
        libreoffice-fresh \
        evince

    # ── Fonts ──────────────────────────────────────────────────────────────
    log "Installing fonts..."
    pacman -S --needed --noconfirm \
        ttf-font-awesome \
        ttf-jetbrains-mono \
        ttf-fira-code \
        ttf-hack \
        ttf-roboto \
        ttf-noto \
        ttf-dejavu \
        noto-fonts-cjk \
        noto-fonts-emoji \
        ttf-liberation \
        ttf-cascadia-code \
        ttf-cascadia-mono-nerd

    log "Terminal tools installed successfully"
}

install_terminal_tools
