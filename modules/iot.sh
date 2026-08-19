#!/usr/bin/env bash
#===============================================================================
# IoT Development Tools Module - IoT, SDR, and Hardware Hacking Kit
#===============================================================================

install_iot_tools() {
    log "=== Installing IoT Development Tools ==="

    # ── MQTT Broker & Messaging ────────────────────────────────────────────
    log "[1/7] MQTT broker and messaging tools..."
    pacman -S --needed --noconfirm \
        mosquitto

    # ── Node-RED ───────────────────────────────────────────────────────────
    log "[2/7] Node-RED..."
    pacman -S --needed --noconfirm \
        nodejs npm

    yay -S --needed --noconfirm node-red 2>/dev/null || true

    # ── PlatformIO & Arduino ───────────────────────────────────────────────
    log "[3/7] PlatformIO and Arduino tools..."
    pacman -S --needed --noconfirm \
        platformio \
        arduino-cli

    yay -S --needed --noconfirm arduino-ide 2>/dev/null || true

    # ── ESP & JTAG Debugging ───────────────────────────────────────────────
    log "[4/7] ESP tools and JTAG debuggers..."
    pacman -S --needed --noconfirm \
        esptool \
        openocd \
        stlink

    yay -S --needed --noconfirm esptool-py 2>/dev/null || true

    # ── Serial Communication ───────────────────────────────────────────────
    log "[5/7] Serial communication tools..."
    pacman -S --needed --noconfirm \
        picocom \
        minicom

    # ── SDR (Software Defined Radio) ──────────────────────────────────────
    log "[6/7] Software Defined Radio tools..."
    pacman -S --needed --noconfirm \
        rtl-sdr \
        soapysdr \
        soapysdr-module-sdrplay 2>/dev/null || true

    yay -S --needed --noconfirm rtl-sdr 2>/dev/null || true
    yay -S --needed --noconfirm libiio 2>/dev/null || true
    yay -S --needed --noconfirm libm2k 2>/dev/null || true
    yay -S --needed --noconfirm gnuradio 2>/dev/null || true

    # ── IoT Utilities ──────────────────────────────────────────────────────
    log "[7/7] IoT utilities..."
    pacman -S --needed --noconfirm \
        mosquitto-clients

    yay -S --needed --noconfirm nodered 2>/dev/null || true

    log "IoT development tools installed successfully"
}

install_iot_tools
