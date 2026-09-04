#!/bin/bash
# ForxoOS - Dev Environment Launcher
# Shows project overview + build menu

clear
echo ""
echo "  ╔══════════════════════════════════════════╗"
echo "  ║         ForxoOS Dev Environment          ║"
echo "  ╚══════════════════════════════════════════╝"
echo ""
echo "  Project Structure:"
echo "  ─────────────────────────────────────────"
echo "  installer/    → Qt6 GUI Installer (9 pages)"
echo "  desktop/      → Qt6 Desktop App"
echo "  iso/          → Archiso ISO profile"
echo "  modules/      → Optional post-install scripts"
echo "  install.sh    → Post-install tool script"
echo ""
echo "  What to develop:"
echo "  ─────────────────────────────────────────"
echo "  1) Installer (Qt6) - 9 wizard pages"
echo "  2) Desktop App (Qt6) - Dashboard, Tools"
echo "  3) ISO Profile - packages, configs"
echo "  4) Modules - install scripts"
echo "  5) All"
echo ""
echo "  ─────────────────────────────────────────"
echo "  Select an option:"
echo ""
echo "  [1] Build & test installer"
echo "  [2] Build & test desktop app"
echo "  [3] View/edit ISO profile"
echo "  [4] View/edit modules"
echo "  [5] Build ISO (Linux only)"
echo "  [6] Exit"
echo ""
read -p "  Choice: " choice

case $choice in
  1)
    echo ""
    echo "  Building installer..."
    cd installer
    mkdir -p build && cd build
    cmake ..
    make -j$(nproc)
    echo "  Built! Run: ./ForxoOS-Installer"
    ;;
  2)
    echo ""
    echo "  Building desktop app..."
    cd desktop
    mkdir -p build && cd build
    cmake ..
    make -j$(nproc)
    echo "  Built! Run: ./ForxoOS-Desktop"
    ;;
  3)
    echo ""
    echo "  ISO Profile contents:"
    echo "  ──────────────────────"
    ls -la iso/profile/
    echo ""
    echo "  Packages:"
    cat iso/profile/packages.x86_64
    ;;
  4)
    echo ""
    echo "  Available modules:"
    echo "  ──────────────────"
    ls -1 modules/
    ;;
  5)
    echo ""
    echo "  Building ISO..."
    cd iso
    sudo ./build.sh
    ;;
  6)
    exit 0
    ;;
  *)
    echo "  Invalid option"
    ;;
esac
