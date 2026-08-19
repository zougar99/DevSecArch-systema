#!/usr/bin/env bash
#===============================================================================
# DevSecArch - Build Custom Arch Linux ISO
# Creates a bootable ISO with all dev + cyber tools pre-installed
#===============================================================================

set -euo pipefail

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
MAGENTA='\033[0;35m'
NC='\033[0m'

VERSION="1.0.0"
ISO_NAME="DevSecArch-${VERSION}"

log()    { echo -e "${GREEN}[+]${NC} $1"; }
warn()   { echo -e "${YELLOW}[!]${NC} $1"; }
err()    { echo -e "${RED}[x]${NC} $1"; }
info()   { echo -e "${CYAN}[i]${NC} $1"; }
banner() {
    echo -e "${MAGENTA}"
    echo "  _____              _____              _              "
    echo " |  __ \\            / ____|            | |             "
    echo " | |  | | _____   _| (___  _ __   __ _| | _____ _ __  "
    echo " | |  | |/ _ \\ \\ / /\\___ \\| '_ \\ / _\` | |/ / _ \\ '__| "
    echo " | |__| |  __/\\ V / ____) | | | | (_| |   <  __/ |    "
    echo " |_____/ \\___| \\_/ |_____/|_| |_|\\__,_|_|\\_\\___|_|    "
    echo -e "${NC}"
    echo -e "${CYAN}  DevSecArch ISO Builder v${VERSION}${NC}"
    echo ""
}

check_root() {
    if [[ $EUID -ne 0 ]]; then
        err "Run as root: sudo ./build-iso.sh"
        exit 1
    fi
}

check_arch() {
    if ! command -v pacman &>/dev/null; then
        err "This must be run on Arch Linux"
        exit 1
    fi
}

install_deps() {
    log "Installing build dependencies..."
    pacman -S --needed --noconfirm \
        archiso \
        squashfs-tools \
        dosfstools \
        mtools \
        libarchive-tools \
        git \
        base-devel
}

setup_workdir() {
    log "Setting up working directory..."
    
    WORK_DIR="/tmp/devsecarch-build"
    PROFILE_DIR="${WORK_DIR}/profile"
    
    # Clean previous builds
    rm -rf "$WORK_DIR"
    mkdir -p "$WORK_DIR"
    
    # Copy archiso releng profile
    cp -r /usr/share/archiso/configs/releng "$PROFILE_DIR"
    
    log "Working directory: $WORK_DIR"
}

customize_packages() {
    log "Customizing package list..."
    
    PACKAGES="${PROFILE_DIR}/packages.x86_64"
    
    cat > "$PACKAGES" << 'PACKAGES_LIST'
# ── Base System ────────────────────────────────────────────────────────
base
linux
linux-firmware
linux-headers
nano
vim
networkmanager
network-manager-applet
wpa_supplicant
iwd
openssh
sudo
git
curl
wget
rsync
reflector
pacman-contrib
man-pages
man-db
terminus-font
noto-fonts
ttf-dejavu
ttf-liberation
which

# ── Desktop Environments ──────────────────────────────────────────────
# GNOME
gnome
gnome-extra
gdm
gnome-tweaks
gnome-terminal
gnome-system-monitor
nautilus
file-roller

# KDE Plasma
plasma-desktop
kde-applications
konsole
dolphin
kate
ark
spectacle
kdeconnect
sddm
plasma-nm
plasma-pa

# i3 Window Manager
i3-wm
i3blocks
i3lock
i3status
dmenu
rofi
dunst
picom
feh
nitrogen
polybar
thunar
ranger

# Sway (Wayland)
sway
swaybg
swaylock
swayidle
wl-clipboard
waybar
wofi
mako
grim
slurp

# ── GPU Drivers ────────────────────────────────────────────────────────
# Mesa (all GPUs)
mesa
lib32-mesa
vulkan-tools
vulkan-validation-layers
lib32-vulkan-validation-layers

# Intel
xf86-video-intel
vulkan-intel
lib32-vulkan-intel

# AMD
xf86-video-amdgpu
vulkan-radeon
lib32-vulkan-radeon

# ── Development Tools ──────────────────────────────────────────────────
base-devel
python
python-pip
python-virtualenv
python-black
python-flake8
python-mypy
python-pytest
python-numpy
python-scipy
python-pandas
jupyterlab
ipython

nodejs
npm
yarn
pnpm
bun

go
rust
cargo

jdk-openjdk
maven
gradle

gcc
gcc-fortran
clang
clang-tools-extra
cmake
make
ninja
gdb
valgrind
strace

ruby
php
lua

# AI/ML
python-tensorflow
python-pytorch
python-scikit-learn
python-matplotlib
python-opencv
python-pillow

# ── Editors & IDEs ─────────────────────────────────────────────────────
code
neovim
helix

# ── DevOps & Containers ────────────────────────────────────────────────
docker
docker-compose
docker-buildx
podman
podman-compose
kubectl
helm
terraform
ansible
vagrant
packer

# ── Databases ──────────────────────────────────────────────────────────
postgresql
mariadb
redis
sqlite
dbeaver

# ── Web Development ────────────────────────────────────────────────────
nginx
mkcert
httpie

# ── Cybersecurity - Recon ──────────────────────────────────────────────
nmap
masscan
rustscan
zenmap
arp-scan
netdiscover
fping
hping

# ── Cybersecurity - Packet Analysis ────────────────────────────────────
wireshark-qt
tshark
tcpdump
ettercap-text-only
bettercap

# ── Cybersecurity - WiFi Attacks ──────────────────────────────────────
aircrack-ng
reaver
bully
wifite2
kismet
horst
wavemon
hostapd
dnsmasq
macchanger
mdk4

# ── Cybersecurity - Password Cracking ──────────────────────────────────
john
hashcat
hydra
medusa
ncrack
cewl
crunch

# ── Cybersecurity - Web App Testing ────────────────────────────────────
nikto
sqlmap
whatweb
dirb
wfuzz
ffuf
gobuster
wapiti
nuclei
subfinder
httpx

# ── Cybersecurity - Exploitation ───────────────────────────────────────
metasploit

# ── Cybersecurity - Forensics ──────────────────────────────────────────
binwalk
foremost
ghidra
radare2
cutter

# ── Cybersecurity - Post-Exploitation ──────────────────────────────────
responder
smbclient
enum4linux
evil-winrm
proxychains-ng

# ── Cybersecurity - Anonymity ──────────────────────────────────────────
openvpn
wireguard-tools
tor
torsocks

# ── WiFi & Network Tools ───────────────────────────────────────────────
iw
iwctl
rfkill
bluez
bluez-utils
blueman
iproute2
iptables
nftables
net-tools
dnsutils
bind-tools
whois
traceroute
mtr

# ── Terminal Enhancement ───────────────────────────────────────────────
zsh
zsh-completions
fzf
zoxide
bat
exa
lsd
fd
ripgrep
starship
tmux
btop
htop
lazygit
git-delta
delta

# ── Productivity ───────────────────────────────────────────────────────
obsidian
firefox
chromium
discord
telegram-desktop
keepassxc
syncthing
obs-studio
gimp
libreoffice-fresh
evince

# ── Fonts ──────────────────────────────────────────────────────────────
ttf-font-awesome
ttf-jetbrains-mono
ttf-fira-code
ttf-hack
ttf-noto
noto-fonts-emoji
ttf-cascadia-code

# ── Qt Development ─────────────────────────────────────────────────────
qt6-base
qt6-declarative
qt6-multimedia
qt6-tools
qt6-5compat
qt6-wayland
qt6-shadertools
qt6-svg
qt6-imageformats
qt6-webengine
qt6-webchannel
qt6-positioning
qt6-serialport
qt6-3d
qt6-charts
qt6-datavis3d
qt6-labs-animation
qt6-labs-blueprint
qt6-labs-folderlistmodel
qt6-labs-graphicaleffects
qt6-labs-platform
qt6-labs-qmlmodels
qt6-labs-settings
qt6-labs-sharedimage
qt6-labs-wavefrontmesh
qt6-quick3d
qt6-quicktimeline
qt6-state-machine
qt6-virtualkeyboard
qt6-websockets
qtcreator
cmake
extra-cmake-modules
ninja
pkgconf

# ── AUR Helper ─────────────────────────────────────────────────────────
yay
paru
PACKAGES_LIST

    log "Package list customized ($(wc -l < "$PACKAGES") packages)"
}

customize_airootfs() {
    log "Customizing live system..."
    
    AIROOTFS="${PROFILE_DIR}/airootfs"
    
    # ── Hostname ────────────────────────────────────────────────────────
    echo "devsecarch" > "${AIROOTFS}/etc/hostname"
    
    # ── Enable services ─────────────────────────────────────────────────
    mkdir -p "${AIROOTFS}/etc/systemd/system/multi-user.target.wants"
    
    for svc in NetworkManager sshd gdm docker bluetooth; do
        if [[ -f "/usr/lib/systemd/system/${svc}.service" ]]; then
            ln -sf "/usr/lib/systemd/system/${svc}.service" \
                "${AIROOTFS}/etc/systemd/system/multi-user.target.wants/${svc}.service" 2>/dev/null || true
        fi
    done
    
    # ── Root password ───────────────────────────────────────────────────
    mkdir -p "${AIROOTFS}/etc"
    echo "root:root" | chpasswd -R "${AIROOTFS}"
    
    # ── Live user ───────────────────────────────────────────────────────
    mkdir -p "${AIROOTFS}/etc"
    
    cat > "${AIROOTFS}/etc/passwd.additions" << 'PASSWD'
devsec:x:1000:1000::/home/devsec:/bin/zsh
PASSWD
    
    cat > "${AIROOTFS}/etc/shadow.additions" << 'SHADOW'
devsec:$6$rounds=656000$placeholder:18241:0:99999:7:::
SHADOW
    
    cat > "${AIROOTFS}/etc/group.additions" << 'GROUP'
devsec:x:1000:
docker:x:998:devsec
wheel:x:999:devsec
GROUP
    
    # ── Sudoers ──────────────────────────────────────────────────────────
    mkdir -p "${AIROOTFS}/etc/sudoers.d"
    cat > "${AIROOTFS}/etc/sudoers.d/devsec" << 'SUDOERS'
devsec ALL=(ALL) NOPASSWD: ALL
SUDOERS
    chmod 440 "${AIROOTFS}/etc/sudoers.d/devsec"
    
    # ── Zsh config ──────────────────────────────────────────────────────
    mkdir -p "${AIROOTFS}/etc/skel"
    cat > "${AIROOTFS}/etc/skel/.zshrc" << 'ZSHRC'
# Oh My Zsh
export ZSH="$HOME/.oh-my-zsh"
ZSH_THEME=""
plugins=(git zsh-autosuggestions zsh-syntax-highlighting docker fzf zoxide)
source $ZSH/oh-my-zsh.sh 2>/dev/null || true
eval "$(starship init zsh)" 2>/dev/null || true
eval "$(zoxide init zsh)" 2>/dev/null || true
export PATH="$HOME/.cargo/bin:$HOME/go/bin:$PATH"
alias ll='lsd -la'
alias cat='bat'
alias find='fd'
alias grep='rg'
ZSHRC
    
    # ── Git config ──────────────────────────────────────────────────────
    cat > "${AIROOTFS}/etc/skel/.gitconfig" << 'GITCONFIG'
[user]
    name = DevSecArch User
    email = user@devsecarch.local
[init]
    defaultBranch = main
[alias]
    st = status
    co = checkout
    br = branch
    ci = commit
    lg = log --oneline --graph --decorate
[core]
    editor = nvim
GITCONFIG
    
    # ── Welcome banner ──────────────────────────────────────────────────
    cat > "${AIROOTFS}/etc/motd" << 'MOTD'

  _____              _____              _              
 |  __ \            / ____|            | |             
 | |  | | _____   _| (___  _ __   __ _| | _____ _ __  
 | |  | |/ _ \ \ / /\___ \| '_ \ / _` | |/ / _ \ '__| 
 | |__| |  __/\ V / ____) | | | | (_| |   <  __/ |    
 |_____/ \___| \_/ |_____/|_| |_|\__,_|_|\_\___|_|    

    Welcome to DevSecArch v1.0.0
    Developer + Security Linux Distribution
    
    Quick start:
      - Type 'neofetch' to see system info
      - Type 'code .' to open VS Code
      - Type 'docker ps' to see containers
      - Type 'nmap -sV <target>' to scan
    
MOTD
    
    # ── Issue template ──────────────────────────────────────────────────
    mkdir -p "${AIROOTFS}/etc/skel/.config"
    
    # ── GUI Installer ──────────────────────────────────────────────────────
    log "Setting up GUI installer..."
    
    # Copy installer source
    mkdir -p "${AIROOTFS}/opt/archinstall-gui/src"
    cp -r "${SCRIPT_DIR}/installer/src/"* "${AIROOTFS}/opt/archinstall-gui/src/"
    cp "${SCRIPT_DIR}/installer/CMakeLists.txt" "${AIROOTFS}/opt/archinstall-gui/"
    
    # Create build script for the installer
    cat > "${AIROOTFS}/opt/archinstall-gui/build.sh" << 'BUILD'
#!/bin/bash
cd /opt/archinstall-gui
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
chmod +x ArchInstall-GUI
BUILD
    chmod +x "${AIROOTFS}/opt/archinstall-gui/build.sh"
    
    # Build installer now (during ISO creation)
    (cd "${AIROOTFS}/opt/archinstall-gui" && bash build.sh) 2>/dev/null || true
    
    # Create autostart for GNOME
    mkdir -p "${AIROOTFS}/home/devsec/.config/autostart"
    cat > "${AIROOTFS}/home/devsec/.config/autostart/archinstall-gui.desktop" << 'AUTOSTART'
[Desktop Entry]
Type=Application
Name=Arch Linux Installer
Comment=Graphical installer for Arch Linux
Exec=/opt/archinstall-gui/build/ArchInstall-GUI
Hidden=false
NoDisplay=false
X-GNOME-Autostart-enabled=true
StartupNotify=true
AUTOSTART
    
    # Also create system-wide autostart
    mkdir -p "${AIROOTFS}/etc/xdg/autostart"
    cp "${AIROOTFS}/home/devsec/.config/autostart/archinstall-gui.desktop" \
       "${AIROOTFS}/etc/xdg/autostart/archinstall-gui.desktop" 2>/dev/null || true
    
    # Create launcher script
    cat > "${AIROOTFS}/usr/local/bin/archinstall-gui" << 'LAUNCHER'
#!/bin/bash
# Launch ArchInstall-GUI
exec /opt/archinstall-gui/build/ArchInstall-GUI
LAUNCHER
    chmod +x "${AIROOTFS}/usr/local/bin/archinstall-gui"
    
    # Create desktop entry for launcher
    mkdir -p "${AIROOTFS}/usr/share/applications"
    cat > "${AIROOTFS}/usr/share/applications/archinstall-gui.desktop" << 'DESKTOP'
[Desktop Entry]
Type=Application
Name=Arch Linux Installer
Comment=Install Arch Linux with graphical interface
Exec=/usr/local/bin/archinstall-gui
Icon=system-software-install
Terminal=false
Categories=System;
DESKTOP
    
    # Set wallpaper with install instructions
    mkdir -p "${AIROOTFS}/usr/share/backgrounds"
    
    log "GUI installer configured"
    
    log "Live system customized"
}

build_iso() {
    log "Building ISO..."
    
    cd "$PROFILE_DIR"
    
    # Build with archiso
    mkarchiso -v -w "${WORK_DIR}/work" -D "${WORK_DIR}/out" "$PROFILE_DIR"
    
    # Find ISO
    ISO_FILE=$(find "${WORK_DIR}/out" -name "*.iso" -type f | head -1)
    
    if [[ -n "$ISO_FILE" ]]; then
        # Copy to Desktop
        DESKTOP="/tmp/${ISO_NAME}-$(date +%Y%m%d).iso"
        cp "$ISO_FILE" "$DESKTOP"
        
        # Get size
        SIZE=$(du -h "$DESKTOP" | cut -f1)
        
        log "ISO built successfully!"
        echo ""
        echo -e "${GREEN}========================================${NC}"
        echo -e "${GREEN}  ISO: ${ISO_NAME}${NC}"
        echo -e "${GREEN}  Size: ${SIZE}${NC}"
        echo -e "${GREEN}  Location: ${DESKTOP}${NC}"
        echo -e "${GREEN}========================================${NC}"
        echo ""
        echo -e "${CYAN}Next steps:${NC}"
        echo "  1. Flash to USB:"
        echo "     sudo dd if=${DESKTOP} of=/dev/sdX bs=4M status=progress"
        echo "     Or use Rufus/balenaEtcher on Windows"
        echo ""
        echo "  2. Boot from USB"
        echo ""
        echo "  3. Default credentials:"
        echo "     User: devsec"
        echo "     Pass: root"
        echo ""
        echo -e "${YELLOW}Note: Copy arch-devsec-build/ to USB for post-install setup${NC}"
        echo ""
    else
        err "ISO build failed"
        exit 1
    fi
}

cleanup() {
    log "Cleaning up..."
    rm -rf "${WORK_DIR}/work" 2>/dev/null || true
}

main() {
    banner
    check_root
    check_arch
    
    echo -e "${CYAN}Build DevSecArch ISO v${VERSION}${NC}"
    echo ""
    read -p "Continue? [Y/n]: " confirm
    confirm=${confirm:-Y}
    
    if [[ "${confirm,,}" != "y" ]]; then
        echo "Aborted."
        exit 0
    fi
    
    install_deps
    setup_workdir
    customize_packages
    customize_airootfs
    build_iso
    cleanup
    
    log "Build complete!"
}

main "$@"
