#!/usr/bin/env bash
#===============================================================================
# Server & Infrastructure Module - Self-Hosted & Infra Stack
#===============================================================================

install_server_tools() {
    log "=== Installing Server & Infrastructure Tools ==="

    # ── Web Servers ────────────────────────────────────────────────────────
    log "[1/6] Nginx, Apache, HAProxy..."
    pacman -S --needed --noconfirm \
        nginx apache haproxy keepalived

    systemctl enable nginx 2>/dev/null || true
    systemctl enable httpd 2>/dev/null || true

    # ── Databases ──────────────────────────────────────────────────────────
    log "[2/6] MySQL, PostgreSQL, Redis, MongoDB..."
    pacman -S --needed --noconfirm \
        mariadb postgresql redis

    yay -S --needed --noconfirm mongodb-bin 2>/dev/null || true

    systemctl enable mariadb 2>/dev/null || true
    systemctl enable postgresql 2>/dev/null || true
    systemctl enable redis 2>/dev/null || true

    # ── Containers ─────────────────────────────────────────────────────────
    log "[3/6] Docker, Docker Compose, Podman..."
    pacman -S --needed --noconfirm \
        docker docker-compose docker-buildx \
        podman podman-compose

    systemctl enable docker 2>/dev/null || true

    # ── Automation & IaC ───────────────────────────────────────────────────
    log "[4/6] Ansible, Terraform, Vault..."
    pacman -S --needed --noconfirm \
        ansible terraform

    yay -S --needed --noconfirm vault 2>/dev/null || true
    yay -S --needed --noconfirm consul-bin 2>/dev/null || true
    yay -S --needed --noconfirm nomad-bin 2>/dev/null || true

    # ── Monitoring & Observability ─────────────────────────────────────────
    log "[5/6] Prometheus, Grafana, ELK..."
    pacman -S --needed --noconfirm \
        prometheus prometheus-node-exporter alertmanager

    yay -S --needed --noconfirm grafana 2>/dev/null || true
    yay -S --needed --noconfirm elasticsearch 2>/dev/null || true
    yay -S --needed --noconfirm kibana 2>/dev/null || true
    yay -S --needed --noconfirm logstash 2>/dev/null || true

    systemctl enable prometheus 2>/dev/null || true
    systemctl enable grafana-server 2>/dev/null || true

    # ── SSL & Certificates ─────────────────────────────────────────────────
    log "[6/6] Certbot & Certificates..."
    pacman -S --needed --noconfirm \
        certbot certbot-nginx certbot-apache

    log "Server & infrastructure tools installed successfully"
}

install_server_tools
