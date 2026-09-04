#!/usr/bin/env bash
#===============================================================================
# ForxoOS - Test Script
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
echo "  ForxoOS Installation Test"
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

# ── Desktop ────────────────────────────────────────────────────────────
echo -e "\n${YELLOW}Desktop Environments:${NC}"
check_package deepin-desktop-base
check_package deepin-session
check_package deepin-shell
check_package lightdm

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
