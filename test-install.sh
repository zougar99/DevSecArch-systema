#!/usr/bin/env bash
#===============================================================================
# DevSecArch - Test Script
# Verifies all tools are installed correctly
#===============================================================================

set -euo pipefail

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m'

PASS=0
FAIL=0
WARN=0

check_tool() {
    local tool="$1"
    local category="$2"
    
    if command -v "$tool" &>/dev/null || \
       pacman -Qi "$tool" &>/dev/null || \
       test -f "/usr/bin/$tool" 2>/dev/null; then
        echo -e "  ${GREEN}[PASS]${NC} $tool"
        ((PASS++))
    else
        echo -e "  ${RED}[FAIL]${NC} $tool"
        ((FAIL++))
    fi
}

check_package() {
    local pkg="$1"
    
    if pacman -Qi "$pkg" &>/dev/null; then
        echo -e "  ${GREEN}[PASS]${NC} $pkg"
        ((PASS++))
    else
        echo -e "  ${RED}[FAIL]${NC} $pkg"
        ((FAIL++))
    fi
}

echo -e "${CYAN}"
echo "  DevSecArch Installation Test"
echo "================================"
echo -e "${NC}"

# ── Base System ────────────────────────────────────────────────────────
echo -e "\n${YELLOW}Base System:${NC}"
check_package base
check_package linux
check_package sudo
check_package git
check_package curl
check_package wget
check_package zsh
check_package tmux

# ── Desktop ────────────────────────────────────────────────────────────
echo -e "\n${YELLOW}Desktop Environments:${NC}"
check_package gnome
check_package plasma-desktop
check_package i3-wm
check_package sway

# ── Editors ────────────────────────────────────────────────────────────
echo -e "\n${YELLOW}Editors:${NC}"
check_tool code
check_tool neovim
check_tool vim
check_tool helix

# ── Languages ──────────────────────────────────────────────────────────
echo -e "\n${YELLOW}Languages:${NC}"
check_tool python3
check_tool node
check_tool go
check_tool rustc
check_tool java
check_tool gcc
check_tool clang

# ── DevOps ─────────────────────────────────────────────────────────────
echo -e "\n${YELLOW}DevOps:${NC}"
check_tool docker
check_tool podman
check_tool kubectl
check_tool helm
check_tool terraform
check_tool ansible

# ── Cybersecurity ──────────────────────────────────────────────────────
echo -e "\n${YELLOW}Cybersecurity:${NC}"
check_tool nmap
check_tool wireshark
check_tool aircrack-ng
check_tool john
check_tool hashcat
check_tool hydra
check_tool nikto
check_tool sqlmap
check_tool ffuf
check_tool gobuster
check_tool bettercap
check_tool ghidra
check_tool radare2

# ── WiFi ───────────────────────────────────────────────────────────────
echo -e "\n${YELLOW}WiFi Tools:${NC}"
check_tool iw
check_tool aircrack-ng
check_tool reaver
check_tool kismet
check_tool macchanger
check_tool hostapd

# ── Terminal ───────────────────────────────────────────────────────────
echo -e "\n${YELLOW}Terminal Tools:${NC}"
check_tool fzf
check_tool bat
check_tool exa
check_tool fd
check_tool rg
check_tool starship
check_tool btop
check_tool lazygit

# ── Summary ────────────────────────────────────────────────────────────
echo ""
echo -e "${CYAN}================================${NC}"
echo -e "${CYAN}  Test Results${NC}"
echo -e "${CYAN}================================${NC}"
echo -e "  ${GREEN}Passed: $PASS${NC}"
echo -e "  ${RED}Failed: $FAIL${NC}"
echo -e "  ${YELLOW}Warned: $WARN${NC}"
echo ""

TOTAL=$((PASS + FAIL))
if [[ $TOTAL -gt 0 ]]; then
    SCORE=$((PASS * 100 / TOTAL))
    echo -e "  Score: ${SCORE}%"
fi

if [[ $FAIL -eq 0 ]]; then
    echo -e "\n  ${GREEN}All checks passed!${NC}"
else
    echo -e "\n  ${YELLOW}Some tools may need manual installation from AUR${NC}"
fi

echo ""
