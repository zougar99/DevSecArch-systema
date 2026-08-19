#!/usr/bin/env bash
#===============================================================================
# Cloud & Kubernetes Tools Module - Multi-Cloud & K8s Stack
#===============================================================================

install_cloud_tools() {
    log "=== Installing Cloud & Kubernetes Tools ==="

    # ── Cloud CLIs ─────────────────────────────────────────────────────────
    log "[1/6] AWS, Azure, GCP CLIs..."
    pacman -S --needed --noconfirm \
        aws-cli

    yay -S --needed --noconfirm azure-cli 2>/dev/null || true
    yay -S --needed --noconfirm google-cloud-sdk 2>/dev/null || true

    # ── Infrastructure as Code ─────────────────────────────────────────────
    log "[2/6] Terraform, Pulumi, security scanners..."
    pacman -S --needed --noconfirm \
        terraform

    yay -S --needed --noconfirm pulumi-bin 2>/dev/null || true
    yay -S --needed --noconfirm tfsec 2>/dev/null || true
    yay -S --needed --noconfirm checkov 2>/dev/null || true
    yay -S --needed --noconfirm cfn-lint 2>/dev/null || true

    # ── Kubernetes Core ────────────────────────────────────────────────────
    log "[3/6] kubectl, Helm, K9s..."
    pacman -S --needed --noconfirm \
        kubectl helm

    yay -S --needed --noconfirm k9s-bin 2>/dev/null || true
    yay -S --needed --noconfirm stern 2>/dev/null || true
    yay -S --needed --noconfirm kubectx 2>/dev/null || true

    # ── GitOps & CD ────────────────────────────────────────────────────────
    log "[4/6] Flux, ArgoCD, cert-manager..."
    yay -S --needed --noconfirm flux-bin 2>/dev/null || true
    yay -S --needed --noconfirm argocd-bin 2>/dev/null || true

    # ── Container & Image Scanning ─────────────────────────────────────────
    log "[5/6] Dive, Trivy, Grype..."
    yay -S --needed --noconfirm dive 2>/dev/null || true
    yay -S --needed --noconfirm trivy 2>/dev/null || true
    yay -S --needed --noconfirm grype 2>/dev/null || true

    # ── Secrets & Encryption ───────────────────────────────────────────────
    log "[6/6] SOPS, Age, Vault..."
    pacman -S --needed --noconfirm \
        sops age

    yay -S --needed --noconfirm vault 2>/dev/null || true

    log "Cloud & Kubernetes tools installed successfully"
}

install_cloud_tools
