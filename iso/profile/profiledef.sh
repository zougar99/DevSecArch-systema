#!/usr/bin/env bash
# shellcheck disable=SC2034

iso_name="DevSecArch"
iso_label="DEVSECARCH_2026"
iso_publisher="DevSecArch <https://github.com/zougar99/DevSecArch-ISO>"
iso_application="DevSecArch Linux"
install_dir="arch"
bootmodes=("bios.syslinux/legacy" "uefi-x64.systemd-boot")
arch="x86_64"
pacman_conf="pacman.conf"
airootfs_image_type="squashfs"
airootfsCompressionOptions=("-comp" "zstd" "-Xcompression-level" "19")
