# ~/.zshrc - Root User Configuration

# History
HISTFILE=~/.zsh_history
HISTSIZE=50000
SAVEHIST=50000
setopt HIST_IGNORE_DUPS
setopt HIST_FIND_NO_DUPS
setopt HIST_SAVE_NO_DUPS
setopt SHARE_HISTORY
setopt INC_APPEND_HISTORY

# Key bindings
bindkey -e

# PATH
export PATH="$HOME/.cargo/bin:$HOME/go/bin:/usr/local/go/bin:$HOME/.local/bin:$PATH"

# Environment
export EDITOR='nvim'
export VISUAL='nvim'

# Aliases
alias cat='bat --style=auto --paging=never'
alias ls='eza --icons --group-directories-first'
alias ll='eza -la --icons --group-directories-first --git'
alias lt='eza -T --icons --level=2'
alias grep='rg'
alias find='fd'
alias update='pacman -Syu'
alias install='pacman -S'
alias remove='pacman -Rns'
alias search='pacman -Ss'
alias ports='ss -tulnp'

# Starship
eval "$(starship init zsh)"

# Zoxide
eval "$(zoxide init zsh)"
alias cd='z'
