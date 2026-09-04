#!/usr/bin/env bash
#===============================================================================
# ForxoOS - Main Installer
# Run this AFTER fresh Arch Linux install
#===============================================================================

set -euo pipefail

VERSION="1.0.0"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
MAGENTA='\033[0;35m'
NC='\033[0m'

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
LOG_FILE="${SCRIPT_DIR}/install.log"
MODULES_DIR="${SCRIPT_DIR}/modules"

log()    { echo -e "${GREEN}[+]${NC} $(date '+%H:%M:%S') $1" | tee -a "$LOG_FILE"; }
warn()   { echo -e "${YELLOW}[!]${NC} $(date '+%H:%M:%S') $1" | tee -a "$LOG_FILE"; }
err()    { echo -e "${RED}[x]${NC} $(date '+%H:%M:%S') $1" | tee -a "$LOG_FILE"; }
info()   { echo -e "${CYAN}[i]${NC} $(date '+%H:%M:%S') $1" | tee -a "$LOG_FILE"; }

banner() {
    echo -e "${MAGENTA}"
    echo "  _____              _____              _              "
    echo " |  __ \\            / ____|            | |             "
    echo " | |  | | _____   _| (___  _ __   __ _| | _____ _ __  "
    echo " | |  | |/ _ \\ \\ / /\\___ \\| '_ \\ / _\` | |/ / _ \\ '__| "
    echo " | |__| |  __/\\ V / ____) | | | | (_| |   <  __/ |    "
    echo " |_____/ \\___| \\_/ |_____/|_| |_|\\__,_|_|\\_\\___|_|    "
    echo -e "${NC}"
    echo -e "${CYAN}  ForxoOS Installer v${VERSION}${NC}"
    echo -e "${CYAN}  Deepin Desktop Linux${NC}"
    echo ""
}

check_root() {
    if [[ $EUID -ne 0 ]]; then
        err "Run as root: sudo ./install.sh"
        exit 1
    fi
}

check_arch() {
    if ! command -v pacman &>/dev/null; then
        err "This is not Arch Linux"
        exit 1
    fi
}

detect_hardware() {
    log "Detecting hardware..."
    
    if lspci 2>/dev/null | grep -qi nvidia; then
        GPU="nvidia"
    elif lspci 2>/dev/null | grep -qi amd; then
        GPU="amd"
    elif lspci 2>/dev/null | grep -qi intel; then
        GPU="intel"
    else
        GPU="none"
    fi
    
    if grep -qm1 "AuthenticAMD" /proc/cpuinfo 2>/dev/null; then
        CPU="amd"
    else
        CPU="intel"
    fi
    
    RAM_GB=$(free -g | awk '/^Mem:/{print $2}')
    
    info "GPU: $GPU | CPU: $CPU | RAM: ${RAM_GB}GB"
}

install_base() {
    log "Installing base packages..."
    
    pacman -Syu --noconfirm
    
    pacman -S --needed --noconfirm \
        base-devel git curl wget vim nano htop btop tmux \
        zsh fish man-pages sudo networkmanager network-manager-applet \
        wpa_supplicant iwd openssh rsync zip unzip p7zip rar unrar \
        reflector udp brightnessctl xdg-utils xdg-user-dirs \
        polkit gnome-keyring dialog
    
    systemctl enable --now NetworkManager 2>/dev/null || true
    
    log "Base packages installed"
}

# ── Module Functions ────────────────────────────────────────────────────────

install_desktops()   { log "Installing desktop environments...";   source "${MODULES_DIR}/desktops.sh"; }
install_gpu()        { log "Installing GPU drivers...";            source "${MODULES_DIR}/gpu.sh"; }
install_dev()        { log "Installing development tools...";      source "${MODULES_DIR}/devtools.sh"; }
install_cyber()      { log "Installing cybersecurity tools...";    source "${MODULES_DIR}/cybersec.sh"; }
install_wifi()       { log "Installing WiFi tools...";             source "${MODULES_DIR}/wifi.sh"; }
install_terminal()   { log "Installing terminal tools...";         source "${MODULES_DIR}/terminal.sh"; }
install_media()      { log "Installing media tools...";            source "${MODULES_DIR}/media.sh"; }
install_productivity(){ log "Installing productivity tools...";    source "${MODULES_DIR}/productivity.sh"; }
install_gaming()     { log "Installing gaming tools...";           source "${MODULES_DIR}/gaming.sh"; }
install_privacy()    { log "Installing privacy tools...";          source "${MODULES_DIR}/privacy.sh"; }
install_networking() { log "Installing networking tools...";       source "${MODULES_DIR}/networking.sh"; }
install_server()     { log "Installing server tools...";           source "${MODULES_DIR}/server.sh"; }
install_cloud()      { log "Installing cloud tools...";            source "${MODULES_DIR}/cloud.sh"; }
install_iot()        { log "Installing IoT tools...";              source "${MODULES_DIR}/iot.sh"; }
install_embedded()   { log "Installing embedded tools...";         source "${MODULES_DIR}/embedded.sh"; }
install_blockchain() { log "Installing blockchain tools...";       source "${MODULES_DIR}/blockchain.sh"; }
install_docker()     { log "Installing Docker tools...";           source "${MODULES_DIR}/docker-tools.sh"; }
install_wincompat()  { log "Installing Windows compatibility...";  source "${MODULES_DIR}/windows-compat.sh"; }
apply_config()       { log "Applying configurations...";           source "${MODULES_DIR}/configs.sh"; }

show_menu() {
    clear
    banner
    
    echo -e "${CYAN}What would you like to install?${NC}"
    echo ""
    echo -e "  ${GREEN}1)${NC}  Everything (recommended)"
    echo -e "  ${GREEN}2)${NC}  Developer Setup (desktop + dev + terminal)"
    echo -e "  ${GREEN}3)${NC}  Security Setup (desktop + cyber + wifi)"
    echo -e "  ${GREEN}4)${NC}  Server Setup (desktop + server + docker)"
    echo -e "  ${GREEN}5)${NC}  Cloud Setup (desktop + cloud + k8s)"
    echo -e "  ${GREEN}6)${NC}  Minimal Setup (base + terminal only)"
    echo -e "  ${GREEN}7)${NC}  Custom (choose each component)"
    echo ""
    echo -e "  ${YELLOW}--- Individual Modules ---${NC}"
    echo -e "  ${YELLOW} 8)${NC}  Desktop Environments"
    echo -e "  ${YELLOW} 9)${NC}  Dev Tools"
    echo -e "  ${YELLOW}10)${NC}  Cybersecurity Tools"
    echo -e "  ${YELLOW}11)${NC}  WiFi Tools"
    echo -e "  ${YELLOW}12)${NC}  Terminal Tools"
    echo -e "  ${YELLOW}13)${NC}  Media Tools"
    echo -e "  ${YELLOW}14)${NC}  Productivity Tools"
    echo -e "  ${YELLOW}15)${NC}  Gaming Tools"
    echo -e "  ${YELLOW}16)${NC}  Privacy Tools"
    echo -e "  ${YELLOW}17)${NC}  Networking Tools"
    echo -e "  ${YELLOW}18)${NC}  Server Tools"
    echo -e "  ${YELLOW}19)${NC}  Cloud Tools"
    echo -e "  ${YELLOW}20)${NC}  IoT Tools"
    echo -e "  ${YELLOW}21)${NC}  Embedded Tools"
    echo -e "  ${YELLOW}22)${NC}  Blockchain Tools"
    echo -e "  ${YELLOW}23)${NC}  Docker/Container Tools"
    echo -e "  ${YELLOW}24)${NC}  Windows Compatibility (Wine + .exe + PDF)"
    echo ""
    echo -e "  ${RED} 0)${NC}  Exit"
    echo ""
    read -p "  Choice [1]: " choice
    echo "${choice:-1}"
}

custom_menu() {
    echo ""
    echo -e "${CYAN}Custom Installation - choose Y/n for each:${NC}"
    echo ""
    read -rp "  Install Desktop Environments? [Y/n]: " install_de
    read -rp "  Install Dev Tools? [Y/n]: " install_dt
    read -rp "  Install Cybersecurity Tools? [Y/n]: " install_ct
    read -rp "  Install WiFi Tools? [Y/n]: " install_wt
    read -rp "  Install Terminal Tools? [Y/n]: " install_tt
    read -rp "  Install Media Tools? [Y/n]: " install_mt
    read -rp "  Install Productivity Tools? [Y/n]: " install_pt
    read -rp "  Install Gaming Tools? [Y/n]: " install_gt
    read -rp "  Install Privacy Tools? [Y/n]: " install_pv
    read -rp "  Install Networking Tools? [Y/n]: " install_nw
    read -rp "  Install Server Tools? [Y/n]: " install_sr
    read -rp "  Install Cloud Tools? [Y/n]: " install_cl
    read -rp "  Install IoT Tools? [Y/n]: " install_io
    read -rp "  Install Embedded Tools? [Y/n]: " install_em
    read -rp "  Install Blockchain Tools? [Y/n]: " install_bc
    read -rp "  Install Docker Tools? [Y/n]: " install_dk
    read -rp "  Install Windows Compatibility (Wine/PDF)? [Y/n]: " install_wc
    read -rp "  Apply Configurations? [Y/n]: " install_cf
}

main() {
    check_root
    check_arch
    detect_hardware
    
    > "$LOG_FILE"
    log "ForxoOS Installer v${VERSION} started"
    log "Hardware: GPU=$GPU CPU=$CPU RAM=${RAM_GB}GB"
    
    choice=$(show_menu)
    
    case $choice in
        1)
            install_base
            install_desktops
            install_gpu
            install_dev
            install_cyber
            install_wifi
            install_terminal
            install_media
            install_productivity
            install_gaming
            install_privacy
            install_networking
            install_server
            install_cloud
            install_iot
            install_embedded
            install_blockchain
            install_docker
            install_wincompat
            apply_config
            ;;
        2)
            install_base
            install_desktops
            install_gpu
            install_dev
            install_terminal
            install_media
            install_docker
            apply_config
            ;;
        3)
            install_base
            install_desktops
            install_gpu
            install_cyber
            install_wifi
            install_terminal
            install_privacy
            apply_config
            ;;
        4)
            install_base
            install_desktops
            install_gpu
            install_server
            install_docker
            install_terminal
            apply_config
            ;;
        5)
            install_base
            install_desktops
            install_gpu
            install_cloud
            install_server
            install_docker
            install_terminal
            apply_config
            ;;
        6)
            install_base
            install_terminal
            apply_config
            ;;
        7)
            custom_menu
            install_base
            [[ "${install_de:-y}" != "n" ]] && install_desktops && install_gpu
            [[ "${install_dt:-y}" != "n" ]] && install_dev
            [[ "${install_ct:-y}" != "n" ]] && install_cyber
            [[ "${install_wt:-y}" != "n" ]] && install_wifi
            [[ "${install_tt:-y}" != "n" ]] && install_terminal
            [[ "${install_mt:-y}" != "n" ]] && install_media
            [[ "${install_pt:-y}" != "n" ]] && install_productivity
            [[ "${install_gt:-y}" != "n" ]] && install_gaming
            [[ "${install_pv:-y}" != "n" ]] && install_privacy
            [[ "${install_nw:-y}" != "n" ]] && install_networking
            [[ "${install_sr:-y}" != "n" ]] && install_server
            [[ "${install_cl:-y}" != "n" ]] && install_cloud
            [[ "${install_io:-y}" != "n" ]] && install_iot
            [[ "${install_em:-y}" != "n" ]] && install_embedded
            [[ "${install_bc:-y}" != "n" ]] && install_blockchain
            [[ "${install_dk:-y}" != "n" ]] && install_docker
            [[ "${install_wc:-y}" != "n" ]] && install_wincompat
            [[ "${install_cf:-y}" != "n" ]] && apply_config
            ;;
        8)  install_base; install_desktops; install_gpu ;;
        9)  install_base; install_dev; install_terminal ;;
        10) install_base; install_cyber; install_wifi; install_terminal ;;
        11) install_base; install_wifi; install_terminal ;;
        12) install_base; install_terminal ;;
        13) install_base; install_media; install_terminal ;;
        14) install_base; install_productivity; install_terminal ;;
        15) install_base; install_gaming; install_desktops; install_gpu; install_terminal ;;
        16) install_base; install_privacy; install_terminal ;;
        17) install_base; install_networking; install_terminal ;;
        18) install_base; install_server; install_docker; install_terminal ;;
        19) install_base; install_cloud; install_terminal ;;
        20) install_base; install_iot; install_terminal ;;
        21) install_base; install_embedded; install_terminal ;;
        22) install_base; install_blockchain; install_terminal ;;
        23) install_base; install_docker; install_terminal ;;
        24) install_base; install_wincompat; install_desktops; install_gpu; install_terminal ;;
        0)
            info "Exiting..."
            exit 0
            ;;
        *)
            err "Invalid choice"
            exit 1
            ;;
    esac
    
    echo ""
    echo -e "${GREEN}========================================${NC}"
    echo -e "${GREEN}  Installation Complete!${NC}"
    echo -e "${GREEN}========================================${NC}"
    echo ""
    info "Log: $LOG_FILE"
    info "Reboot: sudo reboot"
    echo ""
}

main "$@"
