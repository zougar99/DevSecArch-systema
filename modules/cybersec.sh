#!/usr/bin/env bash
#===============================================================================
# Cybersecurity Tools Module - Complete Pentest Kit
#===============================================================================

install_cyber_tools() {
    log "=== Installing Cybersecurity Tools ==="

    # ── Network Scanning & Recon ───────────────────────────────────────────
    log "[1/12] Network scanning tools..."
    pacman -S --needed --noconfirm \
        nmap masscan rustscan zenmap \
        arp-scan netdiscover fping hping ncat \
        angry-ip-scanner

    # ── Packet Analysis ────────────────────────────────────────────────────
    log "[2/12] Packet analysis tools..."
    pacman -S --needed --noconfirm \
        wireshark-qt tshark tcpdump \
        ettercap-text-only bettercap \
        ngrep

    # ── WiFi Attacks ───────────────────────────────────────────────────────
    log "[3/12] WiFi attack tools..."
    pacman -S --needed --noconfirm \
        aircrack-ng reaver bully wifite2 \
        kismet horst wavemon \
        hostapd dnsmasq macchanger mdk4 \
        linssid

    yay -S --needed --noconfirm pixiewps 2>/dev/null || true
    yay -S --needed --noconfirm bettercap 2>/dev/null || true

    # ── Password Cracking ──────────────────────────────────────────────────
    log "[4/12] Password cracking tools..."
    pacman -S --needed --noconfirm \
        john hashcat hydra medusa ncrack \
        cewl crunch wordlists

    yay -S --needed --noconfirm seclists 2>/dev/null || true
    yay -S --needed --noconfirm wordlists 2>/dev/null || true

    # ── Web Application Testing ────────────────────────────────────────────
    log "[5/12] Web application testing tools..."
    pacman -S --needed --noconfirm \
        nikto sqlmap whatweb dirb wfuzz \
        ffuf gobuster wapiti \
        nuclei subfinder httpx \
        wafw00f

    yay -S --needed --noconfirm burpsuite 2>/dev/null || true
    yay -S --needed --noconfirm zaproxy 2>/dev/null || true
    yay -S --needed --noconfirm wpscan 2>/dev/null || true

    # ── Exploitation Frameworks ────────────────────────────────────────────
    log "[6/12] Exploitation frameworks..."
    yay -S --needed --noconfirm metasploit 2>/dev/null || true
    yay -S --needed --noconfirm exploitdb 2>/dev/null || true
    yay -S --needed --noconfirm beef 2>/dev/null || true

    # ── Social Engineering ─────────────────────────────────────────────────
    log "[7/12] Social engineering tools..."
    pacman -S --needed --noconfirm \
        set \
        social-engineer-toolkit

    yay -S --needed --noconfirm goPhish 2>/dev/null || true

    # ── Forensics ──────────────────────────────────────────────────────────
    log "[8/12] Forensics tools..."
    pacman -S --needed --noconfirm \
        binwalk foremost \
        ghidra radare2 cutter \
        gdb strace ltrace \
        volatility3 sleuthkit autopsy

    yay -S --needed --noconfirm ghidra-bin 2>/dev/null || true
    yay -S --needed --noconfirm retdec 2>/dev/null || true

    # ── Reverse Engineering ────────────────────────────────────────────────
    log "[9/12] Reverse engineering tools..."
    pacman -S --needed --noconfirm \
        ghidra radare2 cutter \
        gdb peda \
        strings objdump readelf \
        hexdump xxd \
        upx

    yay -S --needed --noconfirm ghidra-bin 2>/dev/null || true
    yay -S --needed --noconfirm binary-ninja 2>/dev/null || true

    # ── Post-Exploitation ──────────────────────────────────────────────────
    log "[10/12] Post-exploitation tools..."
    pacman -S --needed --noconfirm \
        smbclient enum4linux evil-winrm \
        proxychains-ng \
        chntpw ntfs-3g

    yay -S --needed --noconfirm impacket 2>/dev/null || true
    yay -S --needed --noconfirm crackmapexec 2>/dev/null || true
    yay -S --needed --noconfirm responder 2>/dev/null || true
    yay -S --needed --noconfirm mimikatz 2>/dev/null || true

    # ── OSINT ──────────────────────────────────────────────────────────────
    log "[11/12] OSINT tools..."
    pacman -S --needed --noconfirm \
        theharvester whois

    yay -S --needed --noconfirm sherlock-bin 2>/dev/null || true
    yay -S --needed --noconfirm holehe 2>/dev/null || true
    yay -S --needed --noconfirm maltego 2>/dev/null || true

    # ── Anonymity & VPN ────────────────────────────────────────────────────
    log "[12/12] Anonymity tools..."
    pacman -S --needed --noconfirm \
        openvpn wireguard-tools tor torsocks \
        proxychains-ng iodine

    # ── Wordlists ──────────────────────────────────────────────────────────
    log "Downloading wordlists..."
    mkdir -p /usr/share/wordlists
    if [[ ! -d /usr/share/wordlists/SecLists ]]; then
        git clone --depth 1 https://github.com/danielmiessler/SecLists.git \
            /usr/share/wordlists/SecLists 2>/dev/null || true
    fi
    if [[ ! -d /usr/share/wordlists/rockyou ]]; then
        ln -sf /usr/share/wordlists/SecLists/Passwords/Common-Credentials/rockyou.txt \
            /usr/share/wordlists/rockyou.txt 2>/dev/null || true
    fi

    # ── Mobile Security ────────────────────────────────────────────────────
    log "Installing mobile security tools..."
    pacman -S --needed --noconfirm \
        adb \
        apktool 2>/dev/null || true

    yay -S --needed --noconfirm jadx 2>/dev/null || true
    yay -S --needed --noconfirm drozer 2>/dev/null || true

    # ── Cloud Security ─────────────────────────────────────────────────────
    log "Installing cloud security tools..."
    pacman -S --needed --noconfirm \
        trivy \
        grype

    yay -S --needed --noconfirm scout-suite 2>/dev/null || true
    yay -S --needed --noconfirm pacu 2>/dev/null || true

    log "Cybersecurity tools installed successfully"
}

install_cyber_tools
