#!/usr/bin/env bash
#===============================================================================
# ForxoOS - Windows Compatibility Module
# Installs Wine, Bottles, DXVK for running .exe files
#===============================================================================

set -euo pipefail

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m'

install_wine() {
    echo -e "${CYAN}Installing Wine + Bottles + DXVK...${NC}"
    echo ""

    # Enable multilib for 32-bit support
    if ! grep -q "^\[multilib\]" /etc/pacman.conf; then
        echo -e "${YELLOW}Enabling multilib repository...${NC}"
        sudo sed -i '/\[multilib\]/,/Include/s/^#//' /etc/pacman.conf
        sudo pacman -Sy
    fi

    # Wine + deps
    echo -e "${YELLOW}[1/4] Installing Wine...${NC}"
    sudo pacman -S --needed --noconfirm \
        wine wine-gecko wine-mono \
        winetricks \
        lib32-mesa lib32-vulkan-icd-loader lib32-libpulse

    # Bottles
    echo -e "${YELLOW}[2/4] Installing Bottles...${NC}"
    if yay -S --needed --noconfirm bottles 2>/dev/null || \
       paru -S --needed --noconfirm bottles 2>/dev/null; then
        echo -e "${GREEN}Bottles installed from AUR${NC}"
    else
        echo -e "${YELLOW}Bottles not available, installing flatpak version...${NC}"
        flatpak install -y flathub com.usebottles.bottles 2>/dev/null || \
            echo -e "${YELLOW}Install Bottles manually: https://usebottles.com${NC}"
    fi

    # DXVK
    echo -e "${YELLOW}[3/4] Installing DXVK...${NC}"
    sudo pacman -S --needed --noconfirm dxvk dxvk-bin 2>/dev/null || \
        echo -e "${YELLOW}DXVK installed via Wine GE later${NC}"

    # Vulkan
    echo -e "${YELLOW}[4/4] Installing Vulkan support...${NC}"
    sudo pacman -S --needed --noconfirm \
        vulkan-icd-loader vulkan-tools lib32-vulkan-icd-loader

    # Create forxo-run-exe helper
    install_run_exe_helper

    # Create .desktop entry for Wine
    install_mime_types

    echo ""
    echo -e "${GREEN}========================================${NC}"
    echo -e "${GREEN}  Windows Compatibility installed!${NC}"
    echo -e "${GREEN}========================================${NC}"
    echo ""
    echo -e "  Usage:"
    echo -e "    .exe file  → Right-click → Open with Bottles/Wine"
    echo -e "    forxo-run-exe <file.exe>"
    echo -e ""
    echo -e "  ${YELLOW}Note: Not all .exe files work (drivers, anti-cheat, .NET)${NC}"
    echo ""
}

install_run_exe_helper() {
    echo -e "${YELLOW}Creating forxo-run-exe helper...${NC}"

    sudo tee /usr/local/bin/forxo-run-exe > /dev/null << 'HELPER'
#!/bin/bash
#===============================================================================
# forxo-run-exe - Run .exe files via Wine/Bottles
#===============================================================================

EXE_FILE="$1"

if [ -z "$EXE_FILE" ]; then
    echo "Usage: forxo-run-exe <file.exe>"
    exit 1
fi

if [ ! -f "$EXE_FILE" ]; then
    echo "Error: File not found: $EXE_FILE"
    exit 1
fi

echo "╔══════════════════════════════════════════════╗"
echo "║  Running Windows app via Wine/Bottles        ║"
echo "║                                              ║"
echo "║  WARNING: This is NOT native Windows.        ║"
echo "║  Many .exe files may not work correctly.     ║"
echo "╚══════════════════════════════════════════════╝"
echo ""
echo "File: $EXE_FILE"
echo ""

# Try Bottles first (flatpak)
if flatpak list | grep -q "com.usebottles.bottles" 2>/dev/null; then
    echo "Launching via Bottles..."
    flatpak run com.usebottles.bottles --run "$EXE_FILE"
# Try system Wine
elif command -v wine &>/dev/null; then
    echo "Launching via Wine..."
    wine "$EXE_FILE"
else
    echo "Error: Neither Bottles nor Wine found!"
    echo "Install: sudo pacman -S wine"
    exit 1
fi
HELPER

    sudo chmod +x /usr/local/bin/forxo-run-exe
    echo -e "${GREEN}Created: /usr/local/bin/forxo-run-exe${NC}"
}

install_mime_types() {
    echo -e "${YELLOW}Creating .exe MIME types...${NC}"

    mkdir -p ~/.local/share/applications

    cat > ~/.local/share/applications/forxo-run-exe.desktop << 'DESKTOP'
[Desktop Entry]
Name=Run with Wine/Bottles
Comment=Run Windows application via Wine compatibility layer
Exec=forxo-run-exe %f
Icon=wine
Terminal=false
Type=Application
Categories=Utility;
MimeType=application/x-ms-dos-executable;application/x-executable;
NoDisplay=true
DESKTOP

    # Register MIME types
    xdg-mime default forxo-run-exe.desktop application/x-ms-dos-executable 2>/dev/null || true
    xdg-mime default forxo-run-exe.desktop application/x-executable 2>/dev/null || true

    echo -e "${GREEN}MIME types registered${NC}"
}

# Main
if [ "$EUID" -ne 0 ]; then
    echo -e "${RED}Run as root: sudo bash modules/wine-compat.sh${NC}"
    exit 1
fi

install_wine
