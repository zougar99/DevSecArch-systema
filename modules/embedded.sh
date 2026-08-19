#!/usr/bin/env bash
#===============================================================================
# Embedded Development Tools Module - Cross-Compilation and Debugging Kit
#===============================================================================

install_embedded_tools() {
    log "=== Installing Embedded Development Tools ==="

    # ── ARM Toolchain ──────────────────────────────────────────────────────
    log "[1/7] ARM cross-compilation toolchain..."
    pacman -S --needed --noconfirm \
        arm-none-eabi-gcc \
        arm-none-eabi-binutils \
        arm-none-eabi-newlib

    yay -S --needed --noconfirm gcc-arm-none-eabi 2>/dev/null || true
    yay -S --needed --noconfirm binutils-arm-none-eabi 2>/dev/null || true

    # ── AVR Toolchain ──────────────────────────────────────────────────────
    log "[2/7] AVR toolchain..."
    pacman -S --needed --noconfirm \
        avr-gcc \
        avr-binutils \
        avr-libc \
        avrdude

    yay -S --needed --noconfirm simulide 2>/dev/null || true
    yay -S --needed --noconfirm fritzing 2>/dev/null || true

    # ── Debuggers & Programmers ────────────────────────────────────────────
    log "[3/7] Debuggers and programmers..."
    pacman -S --needed --noconfirm \
        openocd \
        stlink \
        picocom \
        minicom

    yay -S --needed --noconfirm st-flash 2>/dev/null || true
    yay -S --needed --noconfirm probe-rs 2>/dev/null || true
    yay -S --needed --noconfirm gdb-multiarch 2>/dev/null || true

    # ── Build Systems ──────────────────────────────────────────────────────
    log "[4/7] Build systems..."
    pacman -S --needed --noconfirm \
        cmake \
        ninja

    yay -S --needed --noconfirm cmake-gui 2>/dev/null || true

    # ── QEMU User-Mode Emulation ──────────────────────────────────────────
    log "[5/7] QEMU user-mode emulation..."
    pacman -S --needed --noconfirm \
        qemu-user-static

    # ── Additional Debugging Tools ─────────────────────────────────────────
    log "[6/7] Additional debugging tools..."
    pacman -S --needed --noconfirm \
        gdb \
        strace \
        ltrace \
        picocom \
        minicom

    # ── Flashing & Simulation ──────────────────────────────────────────────
    log "[7/7] Flashing and simulation tools..."
    yay -S --needed --noconfirm stlink-git 2>/dev/null || true
    yay -S --needed --noconfirm openocd 2>/dev/null || true

    log "Embedded development tools installed successfully"
}

install_embedded_tools
