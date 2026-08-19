#!/usr/bin/env bash
#===============================================================================
# WiFi & Wireless Tools Module
#===============================================================================

install_wifi_tools() {
    log "=== Installing WiFi & Wireless Tools ==="

    # ── Core WiFi Tools ────────────────────────────────────────────────────
    log "Installing core WiFi tools..."
    pacman -S --needed --noconfirm \
        wireless_tools \
        wpa_supplicant \
        wpa_actiond \
        iwd \
        networkmanager \
        network-manager-applet \
        nm-connection-editor \
        nmtui

    # ── WiFi Scanning & Analysis ───────────────────────────────────────────
    log "Installing WiFi scanning tools..."
    pacman -S --needed --noconfirm \
        aircrack-ng \
        kismet \
        horst \
        wavemon \
        iw \
        iwctl \
        rfkill \
        wavemon \
        linssid \
        linpac

    # ── WiFi Attack Tools ──────────────────────────────────────────────────
    log "Installing WiFi attack tools..."
    pacman -S --needed --noconfirm \
        aircrack-ng \
        reaver \
        bully \
        wifite2 \
        hostapd \
        dnsmasq \
        macchanger \
        mdk4 \
        mdk3
    
    # AUR WiFi tools
    if yay -S --needed --noconfirm pixiewps 2>/dev/null || \
       paru -S --needed --noconfirm pixiewps 2>/dev/null; then
        log "pixiewps installed from AUR"
    fi

    if yay -S --needed --noconfirm bettercap 2>/dev/null || \
       paru -S --needed --noconfirm bettercap 2>/dev/null; then
        log "bettercap installed from AUR"
    fi

    # ── Bluetooth ──────────────────────────────────────────────────────────
    log "Installing Bluetooth tools..."
    pacman -S --needed --noconfirm \
        bluez \
        bluez-utils \
        bluez-tools \
        blueman \
        pulseaudio-bluetooth \
        pipewire-pulse

    systemctl enable bluetooth

    # ── Network Tools ──────────────────────────────────────────────────────
    log "Installing network utilities..."
    pacman -S --needed --noconfirm \
        iproute2 \
        iptables \
        iptables-nft \
        nftables \
        bridge-utils \
        net-tools \
        dnsutils \
        bind-tools \
        whois \
        traceroute \
        mtr \
        inetutils \
        openssh \
        sshfs \
        autossh

    # ── VPN Tools ──────────────────────────────────────────────────────────
    log "Installing VPN tools..."
    pacman -S --needed --noconfirm \
        openvpn \
        wireguard-tools \
        openconnect \
        strongswan

    # ── Network Scanning ──────────────────────────────────────────────────
    log "Installing network scanning tools..."
    pacman -S --needed --noconfirm \
        nmap \
        masscan \
        arp-scan \
        netdiscover \
        fping \
        hping \
        iperf3

    # ── Packet Capture ────────────────────────────────────────────────────
    log "Installing packet capture tools..."
    pacman -S --needed --noconfirm \
        tcpdump \
        wireshark-qt \
        tshark \
        ngrep

    # ── WiFi Firmware ──────────────────────────────────────────────────────
    log "Installing WiFi firmware..."
    pacman -S --needed --noconfirm \
        linux-firmware \
        firmware-linux-nonfree \
        firmware-iwlwifi \
        firmware-atheros \
        firmware-ralink \
        firmware-realtek

    log "WiFi & Wireless tools installed successfully"
}

install_wifi_tools
