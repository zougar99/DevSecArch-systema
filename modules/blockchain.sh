#!/usr/bin/env bash
#===============================================================================
# Blockchain Development Tools Module - Solidity, Ethereum, and Web3 Kit
#===============================================================================

install_blockchain_tools() {
    log "=== Installing Blockchain Development Tools ==="

    # ── Solidity Compiler ──────────────────────────────────────────────────
    log "[1/7] Solidity compiler..."
    pacman -S --needed --noconfirm \
        solc

    yay -S --needed --noconfirm solidity 2>/dev/null || true

    # ── Ganache & Truffle ──────────────────────────────────────────────────
    log "[2/7] Ganache and Truffle..."
    pacman -S --needed --noconfirm \
        nodejs npm

    yay -S --needed --noconfirm ganache-cli 2>/dev/null || true
    npm install -g truffle 2>/dev/null || true

    # ── Hardhat & Foundry ──────────────────────────────────────────────────
    log "[3/7] Hardhat and Foundry..."
    npm install -g hardhat 2>/dev/null || true
    npm install -g foundry 2>/dev/null || true

    yay -S --needed --noconfirm foundry 2>/dev/null || true

    # ── Go Ethereum ────────────────────────────────────────────────────────
    log "[4/7] Go Ethereum..."
    pacman -S --needed --noconfirm \
        go-ethereum

    yay -S --needed --noconfirm geth 2>/dev/null || true

    # ── IPFS & Filecoin ────────────────────────────────────────────────────
    log "[5/7] IPFS and Filecoin..."
    pacman -S --needed --noconfirm \
        ipfs

    yay -S --needed --noconfirm filecoin 2>/dev/null || true

    # ── Brownie & Additional Tools ─────────────────────────────────────────
    log "[6/7] Brownie and additional tools..."
    pacman -S --needed --noconfirm \
        python-pip

    yay -S --needed --noconfirm brownie 2>/dev/null || true

    # ── Remix Desktop ──────────────────────────────────────────────────────
    log "[7/7] Remix desktop..."
    yay -S --needed --noconfirm remix-desktop 2>/dev/null || true

    log "Blockchain development tools installed successfully"
}

install_blockchain_tools
