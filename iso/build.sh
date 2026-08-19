#!/usr/bin/env bash
#===============================================================================
# DevSecArch ISO Builder
# Builds the custom DevSecArch Linux ISO using archiso
#===============================================================================

set -euo pipefail

VERSION="2.0.0"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROFILE_DIR="${SCRIPT_DIR}/profile"
WORK_DIR="${SCRIPT_DIR}/work"
OUTPUT_DIR="${SCRIPT_DIR}/out"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m'

banner() {
    echo -e "${CYAN}"
    echo "  _____              _____              _              "
    echo " |  __ \\            / ____|            | |             "
    echo " | |  | | _____   _| (___  _ __   __ _| | _____ _ __  "
    echo " | |  | |/ _ \\ \\ / /\\___ \\| '_ \\ / _\` | |/ / _ \\ '__| "
    echo " | |__| |  __/\\ V / ____) | | | | (_| |   <  __/ |    "
    echo " |_____/ \\___| \\_/ |_____/|_| |_|\\__,_|_|\\_\\___|_|    "
    echo -e "${NC}"
    echo -e "${CYAN}  ISO Builder v${VERSION}${NC}"
    echo ""
}

check_root() {
    if [[ $EUID -ne 0 ]]; then
        echo -e "${RED}Run as root: sudo ./build.sh${NC}"
        exit 1
    fi
}

check_deps() {
    echo -e "${CYAN}[i] Checking dependencies...${NC}"
    
    local deps=("archiso" "mkarchiso")
    local missing=()
    
    for dep in "${deps[@]}"; do
        if ! command -v "$dep" &>/dev/null; then
            missing+=("$dep")
        fi
    done
    
    if [[ ${#missing[@]} -gt 0 ]]; then
        echo -e "${YELLOW}[!] Installing archiso...${NC}"
        pacman -S --needed --noconfirm archiso
    fi
    
    echo -e "${GREEN}[+] Dependencies OK${NC}"
}

build_iso() {
    echo -e "${CYAN}[i] Building DevSecArch ISO v${VERSION}...${NC}"
    echo ""
    
    # Clean previous builds
    rm -rf "${WORK_DIR}" "${OUTPUT_DIR}"
    mkdir -p "${WORK_DIR}" "${OUTPUT_DIR}"
    
    # Build with archiso
    mkarchiso -v -w "${WORK_DIR}" -D "${OUTPUT_DIR}" "${PROFILE_DIR}"
    
    # Find ISO
    local iso_file
    iso_file=$(find "${OUTPUT_DIR}" -name "*.iso" -type f | head -1)
    
    if [[ -n "$iso_file" ]]; then
        local size
        size=$(du -h "$iso_file" | cut -f1)
        
        echo ""
        echo -e "${GREEN}========================================${NC}"
        echo -e "${GREEN}  ISO Built Successfully!${NC}"
        echo -e "${GREEN}  File: ${iso_file}${NC}"
        echo -e "${GREEN}  Size: ${size}${NC}"
        echo -e "${GREEN}========================================${NC}"
        echo ""
        echo -e "${CYAN}Next steps:${NC}"
        echo "  1. Flash to USB:"
        echo "     sudo dd if=${iso_file} of=/dev/sdX bs=4M status=progress"
        echo "     Or use Rufus/balenaEtcher on Windows"
        echo ""
        echo "  2. Boot from USB"
        echo "  3. Login: devsec / root"
        echo "  4. Run: archinstall or archinstall-gui"
        echo ""
    else
        echo -e "${RED}[x] ISO build failed!${NC}"
        exit 1
    fi
}

cleanup() {
    echo -e "${CYAN}[i] Cleaning up...${NC}"
    rm -rf "${WORK_DIR}" 2>/dev/null || true
}

main() {
    banner
    check_root
    check_deps
    
    echo -e "${CYAN}Build DevSecArch ISO v${VERSION}${NC}"
    echo ""
    read -p "Continue? [Y/n]: " confirm
    confirm=${confirm:-Y}
    
    if [[ "${confirm,,}" != "y" ]]; then
        echo "Aborted."
        exit 0
    fi
    
    build_iso
    cleanup
    
    echo -e "${GREEN}[+] Build complete!${NC}"
}

main "$@"
