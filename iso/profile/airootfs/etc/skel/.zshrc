# ForxoOS ZSH Config
export ZSH_THEME="agnoster"

# History
HISTSIZE=10000
SAVEHIST=10000
HISTFILE=~/.zsh_history

# Aliases
alias ls='ls --color=auto'
alias ll='ls -la'
alias la='ls -A'
alias grep='grep --color=auto'
alias update='sudo pacman -Syu'
alias install='sudo pacman -S'
alias remove='sudo pacman -Rns'

# ForxoOS shortcuts
alias forxoinstall='install.sh'
alias forxoupdate='sudo pacman -Syu'
alias forxostore='forxo-store'
alias run-exe='forxo-run-exe'

# Welcome
echo "Welcome to ForxoOS!"
