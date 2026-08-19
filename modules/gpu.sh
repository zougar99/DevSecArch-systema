#!/usr/bin/env bash
#===============================================================================
# GPU Drivers Module
#===============================================================================

install_gpu_drivers() {
    log "=== Installing GPU Drivers ==="

    case "$GPU" in
        nvidia)
            log "Installing NVIDIA drivers..."
            pacman -S --needed --noconfirm \
                nvidia-dkms \
                nvidia-utils \
                lib32-nvidia-utils \
                nvidia-settings \
                vulkan-tools \
                vulkan-validation-layers \
                lib32-vulkan-validation-layers \
                opencl-nvidia \
                lib32-opencl-nvidia \
                cuda \
                cuda-tools \
                cudnn
            
            # Enable DRM modesetting
            if ! grep -q "nvidia-drm.modeset=1" /etc/default/grub 2>/dev/null; then
                sed -i 's/GRUB_CMDLINE_LINUX_DEFAULT="/GRUB_CMDLINE_LINUX_DEFAULT="nvidia-drm.modeset=1 /' /etc/default/grub 2>/dev/null || true
                grub-mkconfig -o /boot/grub/grub.cfg 2>/dev/null || true
            fi
            
            # nvidia-persistenced
            systemctl enable nvidia-persistenced 2>/dev/null || true
            ;;
        
        amd)
            log "Installing AMD drivers..."
            pacman -S --needed --noconfirm \
                xf86-video-amdgpu \
                vulkan-radeon \
                lib32-vulkan-radeon \
                libva-mesa-driver \
                lib32-libva-mesa-driver \
                mesa \
                lib32-mesa \
                opencl-amd \
                rocm-opencl-runtime \
                rocm-hip-sdk
            ;;
        
        intel)
            log "Installing Intel drivers..."
            pacman -S --needed --noconfirm \
                xf86-video-intel \
                vulkan-intel \
                lib32-vulkan-intel \
                intel-media-driver \
                libva-intel-driver \
                intel-compute-runtime \
                opencl-intel-runtime
            ;;
        
        none)
            log "Installing generic display drivers..."
            pacman -S --needed --noconfirm \
                xf86-video-vesa \
                xf86-video-fbdev \
                mesa \
                lib32-mesa
            ;;
    esac

    log "GPU drivers installed successfully"
}

install_gpu_drivers
