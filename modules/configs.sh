#!/usr/bin/env bash
#===============================================================================
# Configurations Module - Apply all configs
#===============================================================================

apply_configs() {
    log "=== Applying Configurations ==="
    
    USER_HOME=$(eval echo "~$SUDO_USER")

    # ── ZSH + Oh My Zsh ────────────────────────────────────────────────────
    log "Installing Oh My Zsh..."
    if [[ ! -d "$USER_HOME/.oh-my-zsh" ]]; then
        sudo -u "$SUDO_USER" sh -c "
            RUNZSH=no KEEP_ZSHRC=yes \
            sh -c \"\$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)\"
        " 2>/dev/null || true
    fi

    # ── Starship Prompt ────────────────────────────────────────────────────
    log "Setting up Starship prompt..."
    if command -v starship &>/dev/null; then
        sudo -u "$SUDO_USER" bash -c "
            curl -sS https://starship.rs/install.sh | sh -s -- -y
        " 2>/dev/null || true
    fi

    # ── Zsh Plugins ────────────────────────────────────────────────────────
    log "Installing zsh plugins..."
    ZSH_CUSTOM="${USER_HOME}/.oh-my-zsh/custom"
    
    if [[ ! -d "$ZSH_CUSTOM/plugins/zsh-autosuggestions" ]]; then
        sudo -u "$SUDO_USER" git clone https://github.com/zsh-users/zsh-autosuggestions \
            "$ZSH_CUSTOM/plugins/zsh-autosuggestions" 2>/dev/null || true
    fi
    
    if [[ ! -d "$ZSH_CUSTOM/plugins/zsh-syntax-highlighting" ]]; then
        sudo -u "$SUDO_USER" git clone https://github.com/zsh-users/zsh-syntax-highlighting \
            "$ZSH_CUSTOM/plugins/zsh-syntax-highlighting" 2>/dev/null || true
    fi
    
    if [[ ! -d "$ZSH_CUSTOM/plugins/zsh-history-substring-search" ]]; then
        sudo -u "$SUDO_USER" git clone https://github.com/zsh-users/zsh-history-substring-search \
            "$ZSH_CUSTOM/plugins/zsh-history-substring-search" 2>/dev/null || true
    fi

    # ── .zshrc ──────────────────────────────────────────────────────────────
    log "Writing .zshrc..."
    sudo -u "$SUDO_USER" bash -c "cat > '$USER_HOME/.zshrc'" << 'ZSHRC'
# ── Theme ──────────────────────────────────────────────────────────────
ZSH_THEME=""

# ── Plugins ────────────────────────────────────────────────────────────
plugins=(
    git
    zsh-autosuggestions
    zsh-syntax-highlighting
    zsh-history-substring-search
    docker
    docker-compose
    kubectl
    python
    pip
    node
    npm
    rust
    golang
    cargo
    archlinux
    sudo
    command-not-found
    colored-man-pages
    extract
    fzf
    zoxide
    web-search
)

source $ZSH/oh-my-zsh.sh

# ── Aliases ────────────────────────────────────────────────────────────
alias ll='lsd -la'
alias la='lsd -a'
alias l='lsd'
alias cat='bat --style=auto'
alias find='fd'
alias grep='rg'
alias top='btop'
alias df='duf'
alias du='dust'
alias ping='gping'
alias ps='procs'
alias diff='delta'
alias grep='rg'
alias cd='z'

# ── Cyber Aliases ──────────────────────────────────────────────────────
alias scan='nmap -sV -sC -O'
alias fullscan='nmap -A -p- -T4'
alias wpscan='wpscan --api-token $WPSCAN_API'
alias sqlmap='python /opt/sqlmap/sqlmap.py'
alias msfconsole='msfconsole -q'
alias burp='java -jar /opt/BurpSuiteCommunity/burpsuite_community.jar &'
aliasResponder='responder -I eth0 -wrf'

# ── Docker Aliases ─────────────────────────────────────────────────────
alias dk='docker'
alias dkps='docker ps'
alias dksa='docker stop $(docker ps -q)'
alias dkrm='docker system prune -af'
alias dkcompose='docker-compose'

# ── Git Aliases ────────────────────────────────────────────────────────
alias g='git'
alias gs='git status'
alias ga='git add'
alias gc='git commit -m'
alias gp='git push'
alias gl='git log --oneline'
alias gd='git diff'
alias gb='git branch'
alias gco='git checkout'
alias lg='lazygit'

# ── System Aliases ─────────────────────────────────────────────────────
alias update='sudo pacman -Syu'
alias install='sudo pacman -S'
alias remove='sudo pacman -Rns'
alias search='pacman -Ss'
alias mirror='sudo reflector --latest 20 --protocol https --sort rate --save /etc/pacman.d/mirrorlist'
alias shutdown='sudo shutdown -h now'
alias reboot='sudo reboot'
alias mounted='lsblk -f'

# ── Env ────────────────────────────────────────────────────────────────
export EDITOR='nvim'
export VISUAL='nvim'
export TERM='xterm-256color'
export PATH="$HOME/.cargo/bin:$HOME/go/bin:$HOME/.local/bin:$PATH"
export LANG=en_US.UTF-8

# ── FZF ────────────────────────────────────────────────────────────────
export FZF_DEFAULT_COMMAND='fd --type f --hidden --follow --exclude .git'
export FZF_CTRL_T_COMMAND="$FZF_DEFAULT_COMMAND"
export FZF_ALT_C_COMMAND='fd --type d --hidden --follow --exclude .git'

# ── Zoxide ─────────────────────────────────────────────────────────────
eval "$(zoxide init zsh)"

# ── Starship ───────────────────────────────────────────────────────────
eval "$(starship init zsh)"
ZSHRC

    # ── Neovim Config ──────────────────────────────────────────────────────
    log "Setting up Neovim config..."
    sudo -u "$SUDO_USER" mkdir -p "$USER_HOME/.config/nvim"
    sudo -u "$SUDO_USER" bash -c "cat > '$USER_HOME/.config/nvim/init.vim'" << 'VIMRC'
set number
set relativenumber
set tabstop=4
set shiftwidth=4
set expandtab
set smartindent
set autoindent
set hidden
set nobackup
set nowritebackup
set noswapfile
set undofile
set incsearch
set hlsearch
set ignorecase
set smartcase
set termguicolors
set scrolloff=8
set signcolumn=yes
set mouse=a
set clipboard=unnamedplus
set updatetime=250
set timeoutlen=300
syntax on
VIMRC

    # ── Tmux Config ────────────────────────────────────────────────────────
    log "Setting up Tmux config..."
    sudo -u "$SUDO_USER" bash -c "cat > '$USER_HOME/.tmux.conf'" << 'TMUX'
set -g default-terminal "screen-256color"
set -g mouse on
set -g history-limit 50000
set -g base-index 1
setw -g pane-base-index 1
set -g renumber-windows on
set -g prefix C-a
unbind C-b
bind C-a send-prefix
bind | split-window -h
bind - split-window -v
bind r source-file ~/.tmux.conf
bind -n M-Left select-pane -L
bind -n M-Right select-pane -R
bind -n M-Up select-pane -U
bind -n M-Down select-pane -D
setw -g mode-keys vi
TMUX

    # ── Starship Config ────────────────────────────────────────────────────
    log "Setting up Starship config..."
    sudo -u "$SUDO_USER" mkdir -p "$USER_HOME/.config"
    sudo -u "$SUDO_USER" bash -c "cat > '$USER_HOME/.config/starship.toml'" << 'STARSHIP'
format = """
$username\
$hostname\
$directory\
$git_branch\
$git_status\
$python\
$nodejs\
$rust\
$docker_context\
$cmd_duration\
$line_break\
$character"""

[character]
success_symbol = "[❯](bold green)"
error_symbol = "[❯](bold red)"

[directory]
truncation_length = 3
style = "bold cyan"

[git_branch]
symbol = " "
style = "bold purple"

[git_status]
style = "bold red"

[python]
symbol = " "

[nodejs]
symbol = " "

[rust]
symbol = " "

[docker_context]
symbol = " "

[cmd_duration]
min_time = 2_000
style = "bold yellow"
STARSHIP

    # ── Git Config ──────────────────────────────────────────────────────
    log "Setting up Git config..."
    sudo -u "$SUDO_USER" bash -c "
        git config --global core.editor nvim
        git config --global init.defaultBranch main
        git config --global pull.rebase false
        git config --global fetch.prune true
        git config --global diff.colorMoved zebra
        git config --global alias.st 'status'
        git config --global alias.co 'checkout'
        git config --global alias.br 'branch'
        git config --global alias.ci 'commit'
        git config --global alias.lg 'log --oneline --graph --decorate'
        git config --global alias.unstage 'reset HEAD --'
        git config --global alias.last 'log -1 HEAD'
        git config --global alias.visual '!gitk'
    " 2>/dev/null || true

    # ── Firewall ──────────────────────────────────────────────────────────
    log "Configuring firewall..."
    ufw default deny incoming
    ufw default allow outgoing
    ufw allow ssh
    ufw allow 80/tcp
    ufw allow 443/tcp
    ufw enable

    # ── Systemd Services ──────────────────────────────────────────────────
    log "Enabling services..."
    systemctl enable docker 2>/dev/null || true
    systemctl enable podman 2>/dev/null || true
    systemctl enable bluetooth 2>/dev/null || true
    systemctl enable sshd 2>/dev/null || true

    # ── Set Default Shell to Zsh ──────────────────────────────────────────
    log "Setting default shell to Zsh..."
    chsh -s /usr/bin/zsh "$SUDO_USER" 2>/dev/null || true

    log "Configurations applied successfully"
}

apply_configs
