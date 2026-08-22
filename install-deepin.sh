#!/bin/bash
# DevSecArch Tools - Install on Deepin/Ubuntu/Debian
# Usage: bash install-deepin.sh

set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m'

print_banner() {
    clear
    echo -e "${CYAN}"
    echo "  ╔══════════════════════════════════════════════╗"
    echo "  ║     DevSecArch Tools for Deepin/Debian      ║"
    echo "  ╚══════════════════════════════════════════════╝"
    echo -e "${NC}"
}

check_root() {
    if [ "$EUID" -ne 0 ]; then
        echo -e "${RED}[!] Run as root: sudo bash install-deepin.sh${NC}"
        exit 1
    fi
}

update_system() {
    echo -e "${YELLOW}[*] Updating system...${NC}"
    apt update && apt upgrade -y
    apt install -y curl wget git sudo software-properties-common apt-transport-https
}

install_terminal_tools() {
    echo -e "${YELLOW}[*] Installing terminal tools...${NC}"

    # Zsh
    apt install -y zsh zsh-autosuggestions zsh-syntax-highlighting
    chsh -s /bin/zsh

    # Modern CLI tools
    apt install -y htop btop tmux ranger ncdu bat ripgrep fzf fd-find

    # bat as batcat
    ln -sf /usr/bin/batcat /usr/bin/bat 2>/dev/null || true

    # fd
    ln -sf /usr/bin/fdfind /usr/bin/fd 2>/dev/null || true

    # lazygit
    LAZYGIT_VERSION=$(curl -s "https://api.github.com/repos/jesseDuffield/lazygit/releases/latest" | grep -Po '"tag_name": "v\K[^"]*')
    curl -Lo lazygit.tar.gz "https://github.com/jesseDuffield/lazygit/releases/latest/download/lazygit_${LAZYGIT_VERSION}_Linux_x86_64.tar.gz"
    tar xf lazygit.tar.gz lazygit
    install lazygit /usr/local/bin/
    rm lazygit lazygit.tar.gz

    # zoxide
    curl -sS https://raw.githubusercontent.com/ajeetdsouza/zoxide/main/install.sh | bash

    # eza (modern ls)
    apt install -y eza 2>/dev/null || {
        wget -qO /usr/local/bin/eza "https://github.com/eza-community/eza/releases/latest/download/eza_x86_64-unknown-linux-gnu.tar.gz"
    }

    echo -e "${GREEN}[+] Terminal tools installed!${NC}"
}

install_dev_tools() {
    echo -e "${YELLOW}[*] Installing dev tools...${NC}"

    # Python
    apt install -y python3 python3-pip python3-venv

    # Node.js
    curl -fsSL https://deb.nodesource.com/setup_22.x | bash -
    apt install -y nodejs

    # Go
    GO_VERSION="1.22.5"
    wget -q "https://go.dev/dl/go${GO_VERSION}.linux-amd64.tar.gz"
    tar -C /usr/local -xzf "go${GO_VERSION}.linux-amd64.tar.gz"
    echo 'export PATH=$PATH:/usr/local/go/bin:$HOME/go/bin' >> /etc/profile.d/go.sh
    rm "go${GO_VERSION}.linux-amd64.tar.gz"

    # Rust
    curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y

    # Docker
    install -m 0755 -d /etc/apt/keyrings
    curl -fsSL https://download.docker.com/linux/debian/gpg -o /etc/apt/keyrings/docker.asc
    chmod a+r /etc/apt/keyrings/docker.asc
    echo "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/debian $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | tee /etc/apt/sources.list.d/docker.list > /dev/null
    apt update
    apt install -y docker-ce docker-ce-cli containerd.io docker-buildx docker-compose-plugin

    echo -e "${GREEN}[+] Dev tools installed!${NC}"
}

install_cybersec_tools() {
    echo -e "${YELLOW}[*] Installing cybersecurity tools...${NC}"

    # Network tools
    apt install -y nmap wireshark tcpdump netcat-openbsd socat

    # Web tools
    apt install -y nikto sqlmap dirb gobuster

    # Password tools
    apt install -y john hashcat hydra crunch

    # Wireless
    apt install -y aircrack-ng reaver wifite

    # Forensics
    apt install -y binwalk foremost scalpel sleuthkit autopsy

    # Reverse engineering
    apt install -y ghidra radare2

    # Metasploit
    curl https://raw.githubusercontent.com/rapid7/metasploit-omnibus/master/config/templates/metasploit-framework-wrappers/msfupdate.erb > /tmp/msfinstall
    chmod 755 /tmp/msfinstall
    /tmp/msfinstall

    # Burp Suite
    apt install -y openjdk-17-jdk
    echo -e "${YELLOW}[*] Download Burp Suite from: https://portswigger.net/burp/communitydownload${NC}"

    # John the Ripper (JtR)
    apt install -y john

    # OWASP tools
    apt install -y zaproxy

    # THC-Hydra
    apt install -y hydra

    echo -e "${GREEN}[+] Cybersecurity tools installed!${NC}"
}

install_wifi_tools() {
    echo -e "${YELLOW}[*] Installing WiFi tools...${NC}"

    apt install -y wireless-tools wpasupplicant iw network-manager
    apt install -y aircrack-ng kismet wifite reaver bully pixiewps
    apt install -y fern-wifi-cracker

    echo -e "${GREEN}[+] WiFi tools installed!${NC}"
}

install_privacy_tools() {
    echo -e "${YELLOW}[*] Installing privacy tools...${NC}"

    # Tor
    apt install -y tor torbrowser-launcher

    # VPN
    apt install -y openvpn wireguard

    # Firewall
    apt install -y ufw gufw

    # Encryption
    apt install -y veracrypt

    # Password manager
    apt install -y keepassxc

    echo -e "${GREEN}[+] Privacy tools installed!${NC}"
}

install_productivity() {
    echo -e "${YELLOW}[*] Installing productivity tools...${NC}"

    # Office
    apt install -y libreoffice libreoffice-l10n-ar

    # PDF
    apt install -y evince okular

    # Note taking
    apt install -y obsidian

    # Browser
    apt install -y firefox-esr

    # Media
    apt install -y vlc gimp inkscape audacity

    echo -e "${GREEN}[+] Productivity tools installed!${NC}"
}

install_gaming() {
    echo -e "${YELLOW}[*] Installing gaming tools...${NC}"

    # Steam
    dpkg --add-architecture i386
    apt update
    apt install -y steam-installer steam-devices

    # Wine
    apt install -y wine wine64 wine32

    # Lutris
    apt install -y lutris

    # MangoHud
    apt install -y mangohud

    echo -e "${GREEN}[+] Gaming tools installed!${NC}"
}

install_server_tools() {
    echo -e "${YELLOW}[*] Installing server tools...${NC}"

    # Web server
    apt install -y nginx apache2

    # Database
    apt install -y postgresql mysql-server redis-server

    # PHP
    apt install -y php php-fpm php-mysql

    # Node
    apt install -y nodejs npm

    echo -e "${GREEN}[+] Server tools installed!${NC}"
}

install_cloud_tools() {
    echo -e "${YELLOW}[*] Installing cloud tools...${NC}"

    # AWS
    curl "https://awscli.amazonaws.com/awscli-exe-linux-x86_64.zip" -o "awscliv2.zip"
    apt install -y unzip
    unzip awscliv2.zip
    ./aws/install
    rm -rf aws awscliv2.zip

    # Docker
    apt install -y docker.io docker-compose

    # Terraform
    apt install -y terraform 2>/dev/null || {
        wget -qO /usr/local/bin/terraform "https://releases.hashicorp.com/terraform/1.8.0/terraform_1.8.0_linux_amd64.zip"
    }

    # kubectl
    curl -LO "https://dl.k8s.io/release/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubectl"
    install -o root -g root -m 0755 kubectl /usr/local/bin/kubectl

    echo -e "${GREEN}[+] Cloud tools installed!${NC}"
}

install_docker_tools() {
    echo -e "${YELLOW}[*] Installing Docker tools...${NC}"

    # Docker Compose
    apt install -y docker-compose

    # Podman
    apt install -y podman podman-compose

    # Portainer
    docker volume create portainer_data
    docker run -d -p 9000:9000 --name portainer --restart=always -v /var/run/docker.sock:/var/run/docker.sock -v portainer_data:/data portainer/portainer-ce:latest

    echo -e "${GREEN}[+] Docker tools installed!${NC}"
}

install_desktop_apps() {
    echo -e "${YELLOW}[*] Installing desktop apps...${NC}"

    # VS Code
    wget -qO- https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > packages.microsoft.gpg
    install -o root -g root -m 644 packages.microsoft.gpg /etc/apt/trusted.gpg.d/
    echo "deb [arch=amd64 signed-by=/etc/apt/trusted.gpg.d/packages.microsoft.gpg] https://packages.microsoft.com/repos/code stable main" > /etc/apt/sources.list.d/vscode.list
    apt update
    apt install -y code

    # Discord
    apt install -y discord

    # Slack
    apt install -y slack-desktop

    # Telegram
    apt install -y telegram-desktop

    # File manager extras
    apt install -y nemo file-roller

    echo -e "${GREEN}[+] Desktop apps installed!${NC}"
}

show_menu() {
    echo ""
    echo -e "${CYAN}Select packages to install:${NC}"
    echo "  [1]  Terminal tools (zsh, htop, fzf, etc.)"
    echo "  [2]  Dev tools (Python, Node, Go, Rust, Docker)"
    echo "  [3]  Cybersecurity tools (nmap, john, etc.)"
    echo "  [4]  WiFi tools (aircrack, wifite, etc.)"
    echo "  [5]  Privacy tools (Tor, VPN, UFW)"
    echo "  [6]  Productivity (Office, Browser, Media)"
    echo "  [7]  Gaming (Steam, Wine, Lutris)"
    echo "  [8]  Server tools (Nginx, PostgreSQL)"
    echo "  [9]  Cloud tools (AWS, Docker, kubectl)"
    echo "  [10] Docker tools (Compose, Podman, Portainer)"
    echo "  [11] Desktop apps (VS Code, Discord, Slack)"
    echo ""
    echo "  [A]  Install ALL"
    echo "  [Q]  Quit"
    echo ""
    read -p "  Choice: " choice
}

main() {
    print_banner
    check_root
    update_system

    while true; do
        show_menu
        case $choice in
            1) install_terminal_tools ;;
            2) install_dev_tools ;;
            3) install_cybersec_tools ;;
            4) install_wifi_tools ;;
            5) install_privacy_tools ;;
            6) install_productivity ;;
            7) install_gaming ;;
            8) install_server_tools ;;
            9) install_cloud_tools ;;
            10) install_docker_tools ;;
            11) install_desktop_apps ;;
            A|a)
                install_terminal_tools
                install_dev_tools
                install_cybersec_tools
                install_wifi_tools
                install_privacy_tools
                install_productivity
                install_gaming
                install_server_tools
                install_cloud_tools
                install_docker_tools
                install_desktop_apps
                ;;
            Q|q) echo -e "${GREEN}Done!${NC}"; exit 0 ;;
            *) echo -e "${RED}Invalid option${NC}" ;;
        esac
        echo ""
        echo -e "${GREEN}[+] Press Enter to continue...${NC}"
        read
    done
}

main
