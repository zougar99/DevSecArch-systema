# ~/.bashrc - DevSecArch Bash Configuration

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

# History
HISTSIZE=50000
HISTFILESIZE=100000
HISTCONTROL=ignoreboth:erasedups
shopt -s histappend

# Check window size after each command
shopt -s checkwinsize

# Enable globstar
shopt -s globstar

# PATH
export PATH="$HOME/.cargo/bin:$HOME/go/bin:/usr/local/go/bin:$HOME/.local/bin:$PATH"

# Environment
export EDITOR='nvim'
export VISUAL='nvim'
export BROWSER='firefox'
export PAGER='less'
export LESS='-R'
export GOPATH="$HOME/go"
export CARGO_HOME="$HOME/.cargo"
export XDG_CONFIG_HOME="$HOME/.config"
export XDG_DATA_HOME="$HOME/.local/share"

# fzf
export FZF_DEFAULT_COMMAND='fd --type f --hidden --follow --exclude .git'
export FZF_CTRL_T_COMMAND="$FZF_DEFAULT_COMMAND"
export FZF_ALT_C_COMMAND='fd --type d --hidden --follow --exclude .git'

# Aliases - Modern Tools
alias cat='bat --style=auto --paging=never'
alias ls='eza --icons --group-directories-first'
alias ll='eza -la --icons --group-directories-first --git'
alias lt='eza -T --icons --level=2'
alias grep='rg'
alias find='fd'
alias top='btop'
alias du='dust'
alias df='duf'
alias ps='procs'
alias sed='sd'
alias curl='curlie'

# Navigation
alias ..='cd ..'
alias ...='cd ../..'
alias ....='cd ../../..'
alias .....='cd ../../../..'
alias -- -='cd -'

# Git
alias g='git'
alias gs='git status -sb'
alias ga='git add'
alias gc='git commit'
alias gp='git push'
alias gl='git log --oneline --graph --decorate -20'
alias gd='git diff'
alias gb='git branch -vv'
alias gco='git checkout'
alias gsw='git switch'

# Docker
alias dk='docker'
alias dkps='docker ps'
alias dki='docker images'
alias dkrm='docker rm -f'
alias dkc='docker compose'

# System
alias update='sudo pacman -Syu'
alias install='sudo pacman -S'
alias remove='sudo pacman -Rns'
alias search='pacman -Ss'
alias mirrors='sudo reflector --latest 20 --protocol https --sort rate --save /etc/pacman.d/mirrorlist'
alias grub-update='sudo grub-mkconfig -o /boot/grub/grub.cfg'
alias ports='ss -tulnp'
alias myip='curl -s ifconfig.me'
alias linux='neofetch'

# Navigation
alias devsec='cd ~/Projects/devsec'
alias dots='cd ~/.config'

# Archinstall
alias archinstall-gui='sudo archinstall --gui'

# Starship Prompt
eval "$(starship init bash)"

# Zoxide
eval "$(zoxide init bash)"
alias cd='z'
