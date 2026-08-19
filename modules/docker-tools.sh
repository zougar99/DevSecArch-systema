#!/usr/bin/env bash
#===============================================================================
# Docker & Container Tools Module - Containerization and Orchestration Kit
#===============================================================================

install_docker_tools() {
    log "=== Installing Docker & Container Tools ==="

    # ── Docker Core ────────────────────────────────────────────────────────
    log "[1/8] Docker core..."
    pacman -S --needed --noconfirm \
        docker \
        docker-compose

    yay -S --needed --noconfirm docker-buildx 2>/dev/null || true

    # ── Podman ─────────────────────────────────────────────────────────────
    log "[2/8] Podman..."
    pacman -S --needed --noconfirm \
        podman

    yay -S --needed --noconfirm podman-compose 2>/dev/null || true

    # ── Build Tools ────────────────────────────────────────────────────────
    log "[3/8] Build tools..."
    pacman -S --needed --noconfirm \
        buildah \
        skopeo

    # ── Container Utilities ────────────────────────────────────────────────
    log "[4/8] Container utilities..."
    yay -S --needed --noconfirm crane 2>/dev/null || true
    yay -S --needed --noconfirm dive 2>/dev/null || true
    yay -S --needed --noconfirm lazydocker 2>/dev/null || true

    # ── Container Runtime & Monitoring ─────────────────────────────────────
    log "[5/8] Container runtime and monitoring..."
    pacman -S --needed --noconfirm \
        containerd

    yay -S --needed --noconfirm docker-slim 2>/dev/null || true
    yay -S --needed --noconfirm ctop 2>/dev/null || true

    # ── Device & Terminal Tools ────────────────────────────────────────────
    log "[6/8] Device and terminal tools..."
    yay -S --needed --noconfirm cdi 2>/dev/null || true
    yay -S --needed --noconfirm gotty 2>/dev/null || true

    # ── Auto-Update ────────────────────────────────────────────────────────
    log "[7/8] Container auto-update..."
    yay -S --needed --noconfirm watchtower 2>/dev/null || true

    # ── Docker Compose V2 ──────────────────────────────────────────────────
    log "[8/8] Docker Compose V2..."
    pacman -S --needed --noconfirm \
        docker-compose-switch 2>/dev/null || true

    log "Docker & container tools installed successfully"
}

install_docker_tools
