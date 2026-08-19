#!/usr/bin/env bash
# shellcheck disable=SC2034

iso_name="DevSecArch"
iso_label="DEVSECARCH_2026"
iso_publisher="DevSecArch <https://github.com/zougar99/DevSecArch-systema>"
iso_application="DevSecArch Linux"
install_dir="arch"
bootmodes=("uefi.grub")
arch="x86_64"
pacman_conf="pacman.conf"
airootfs_image_type="squashfs"
airootfsCompressionOptions=("-comp" "gzip")
