#!/usr/bin/env bash
# shellcheck disable=SC2034

iso_name="ForxoOS"
iso_version="2026.08.25"
iso_label="FORXOOS_2026"
iso_publisher="ForxoOS <https://github.com/zougar99/DevSecArch-systema>"
iso_application="ForxoOS - Deepin Desktop Linux"
install_dir="arch"
bootmodes=("bios.syslinux" "uefi.grub")
arch="x86_64"
pacman_conf="pacman.conf"
airootfs_image_type="squashfs"
airootfsCompressionOptions=("-comp" "gzip")
