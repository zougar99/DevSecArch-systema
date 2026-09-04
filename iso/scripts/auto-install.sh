#!/usr/bin/env bash
set -euo pipefail

echo ""
echo "  =========================================="
echo "   ForxoOS Auto-Installer v2.0.0"
echo "  =========================================="
echo ""

DISK="/dev/sda"
[[ -b "/dev/nvme0n1" ]] && DISK="/dev/nvme0n1"

echo "[1/8] Partitioning disk..."
parted -s "$DISK" mklabel gpt
parted -s "$DISK" mkpart primary fat32 1MiB 513MiB
parted -s "$DISK" set 1 esp on
parted -s "$DISK" mkpart primary ext4 513MiB 100%

if [[ "$DISK" == "/dev/nvme0n1" ]]; then
    mkfs.fat -F32 "${DISK}p1"
    mkfs.ext4 -F "${DISK}p2"
    BOOT_PART="${DISK}p1"
    ROOT_PART="${DISK}p2"
else
    mkfs.fat -F32 "${DISK}1"
    mkfs.ext4 -F "${DISK}2"
    BOOT_PART="${DISK}1"
    ROOT_PART="${DISK}2"
fi

mount "$ROOT_PART" /mnt
mkdir -p /mnt/boot
mount "$BOOT_PART" /mnt/boot
echo "  Done: $BOOT_PART + $ROOT_PART"

echo "[2/8] Installing base system..."
pacstrap /mnt base linux linux-firmware linux-headers nano vim sudo git curl wget networkmanager openssh reflector
echo "  Done"

echo "[3/8] Generating fstab..."
genfstab -U /mnt >> /mnt/etc/fstab
echo "  Done"

echo "[4/8] Configuring system..."
arch-chroot /mnt /bin/bash -c '
    echo "forxos" > /etc/hostname
    echo "127.0.0.1 localhost" > /etc/hosts
    echo "::1 localhost" >> /etc/hosts
    echo "127.0.1.1 forxos" >> /etc/hosts

    ln -sf /usr/share/zoneinfo/UTC /etc/localtime
    hwclock --systohc

    sed -i "s/#en_US.UTF-8/en_US.UTF-8/" /etc/locale.gen
    locale-gen
    echo "LANG=en_US.UTF-8" > /etc/locale.conf

    echo "root:root" | chpasswd

    useradd -m -G wheel -s /bin/bash devsec
    echo "devsec:root" | chpasswd
    echo "devsec ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/devsec
    chmod 440 /etc/sudoers.d/devsec
'

echo "[5/8] Installing bootloader..."
arch-chroot /mnt /bin/bash -c '
    pacman -S --noconfirm grub efibootmgr os-prober
    grub-install --target=x86_64-efi --efi-directory=/boot --bootloader-id=ForxoOS
    grub-install --target=i386-pc /dev/sda 2>/dev/null || true
    grub-mkconfig -o /boot/grub/grub.cfg
'
echo "  Done"

echo "[6/8] Installing desktop + tools..."
arch-chroot /mnt /bin/bash -c '
    pacman -S --noconfirm \
        deepin-desktop-base deepin-session deepin-shell deepin-control-center \
        deepin-file-manager deepin-terminal deepin-editor deepin-system-monitor \
        lightdm lightdm-deepin-greeter \
        pipewire pipewire-pulse pipewire-alsa wireplumber \
        alacritty zsh tmux \
        firefox \
        htop btop \
        qt6-base qt6-wayland cmake

    systemctl enable lightdm 2>/dev/null || true
    systemctl enable NetworkManager 2>/dev/null || true
    systemctl enable sshd 2>/dev/null || true
'
echo "  Done"

echo "[7/8] Installing dev + security tools..."
arch-chroot /mnt /bin/bash -c '
    pacman -S --noconfirm \
        python python-pip nodejs npm go rust gcc docker docker-compose \
        nmap wireshark-qt git

    usermod -aG docker devsec 2>/dev/null || true
    systemctl enable docker 2>/dev/null || true
'
echo "  Done"

echo "[8/8] Final setup..."
arch-chroot /mnt /bin/bash -c '
    systemctl enable NetworkManager
    systemctl enable sshd
'

echo ""
echo "  =========================================="
echo "   Installation Complete!"
echo "   Login: devsec / root"
echo "   Reboot to start ForxoOS"
echo "  =========================================="
echo ""
echo "  Type: reboot"
