#!/usr/bin/env bash
# shellcheck disable=SC2034

iso_name="DevSecArch"
iso_version="2026.08.23"
iso_label="DEVSECARCH_2026"
iso_publisher="DevSecArch <https://github.com/zougar99/DevSecArch-systema>"
iso_application="DevSecArch Linux - Deepin Desktop"
install_dir="arch"
bootmodes=("bios.syslinux" "uefi.grub")
arch="x86_64"
pacman_conf="pacman.conf"
airootfs_image_type="squashfs"
airootfsCompressionOptions=("-comp" "xz" "-Xbcj" "x86")
