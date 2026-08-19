#!/usr/bin/env bash
#===============================================================================
# Network Administration Tools Module - Net Tools Stack
#===============================================================================

install_networking_tools() {
    log "=== Installing Network Administration Tools ==="

    # ── Packet Analysis ────────────────────────────────────────────────────
    log "[1/6] Wireshark, nmap, tcpdump..."
    pacman -S --needed --noconfirm \
        wireshark-qt wireshark-cli nmap tcpdump ngrep

    usermod -aG wireshark "$USER" 2>/dev/null || true

    # ── Core Utilities ─────────────────────────────────────────────────────
    log "[2/6] net-tools, iproute2, traceroute..."
    pacman -S --needed --noconfirm \
        net-tools iproute2 traceroute mtr inetutils \
        bind whois ethtool bridge-utils socat

    # ── VPN & Tunneling ────────────────────────────────────────────────────
    log "[3/6] OpenVPN, WireGuard, ZeroTier..."
    pacman -S --needed --noconfirm \
        openvpn wireguard-tools

    yay -S --needed --noconfirm zerotier-one 2>/dev/null || true
    yay -S --needed --noconfirm tailscale 2>/dev/null || true

    # ── Monitoring & Bandwidth ─────────────────────────────────────────────
    log "[4/6] nethogs, iftop, bmon, slurm..."
    pacman -S --needed --noconfirm \
        nethogs iftop bmon

    yay -S --needed --noconfirm slurm 2>/dev/null || true

    # ── Proxy & Testing ────────────────────────────────────────────────────
    log "[5/6] proxychains-ng, iperf3, speedtest..."
    pacman -S --needed --noconfirm \
        proxychains-ng iperf3

    yay -S --needed --noconfirm speedtest-cli 2>/dev/null || true

    # ── DNS & Diagnostics ──────────────────────────────────────────────────
    log "[6/6] dig, nslookup, DNS utils..."
    pacman -S --needed --noconfirm \
        bind dnsutils ldns

    log "Network administration tools installed successfully"
}

install_networking_tools
