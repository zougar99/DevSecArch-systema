# DevSecArch

> Custom Arch Linux with Deepin Desktop - Developer + Security + Everything.

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

## What is DevSecArch?

DevSecArch is a **custom Arch Linux distribution** with **Deepin Desktop Environment**. Beautiful like Deepin, powerful like Arch.

### Features

- **Deepin Desktop (DDE)** - Beautiful, modern desktop
- **500+ Tools** - Developer, Security, Gaming, Server
- **Windows Compatibility** - Wine, Proton, run .exe
- **Gaming** - Steam, Lutris, Proton-GE, MangoHud
- **Cybersecurity** - 100+ pentest tools
- **Server/Cloud** - Docker, Kubernetes, Ansible
- **Auto-Install** - One-click setup
- **Arabic Support** - Full RTL + Arabic language

## Screenshots

> DevSecArch with Deepin Desktop

## Quick Start

### Download ISO
Go to [Releases](https://github.com/zougar99/DevSecArch-systema/releases) and download the latest ISO.

### Burn to USB
```bash
# Linux
sudo dd if=DevSecArch.iso of=/dev/sdX bs=4M status=progress

# Windows - Use Rufus or balenaEtcher
```

### Install
1. Boot from USB
2. Auto-login as `devsec`
3. Run installer from desktop

### Post-Install Tools
```bash
git clone https://github.com/zougar99/DevSecArch-systema.git
cd DevSecArch-systema
sudo ./install.sh
```

## Project Structure

```
DevSecArch-systema/
├── iso/                    # ISO profile (archiso)
│   ├── profile/
│   │   ├── profiledef.sh
│   │   ├── packages.x86_64
│   │   └── airootfs/
│   └── build.sh
├── modules/                # 19 install modules
├── installer/              # GUI Installer (Qt 6)
├── desktop/                # Desktop App (Qt 6)
├── install.sh              # Post-install script
└── .github/workflows/      # CI/CD - auto build ISO
```

## Modules

| Module | Description |
|--------|-------------|
| desktops.sh | GNOME, KDE, i3, Sway |
| gpu.sh | NVIDIA, AMD, Intel |
| devtools.sh | Python, Node, Go, Rust |
| cybersec.sh | 100+ security tools |
| wifi.sh | WiFi attack tools |
| terminal.sh | Zsh, fzf, bat, lazygit |
| media.sh | FFmpeg, OBS, GIMP |
| gaming.sh | Steam, Lutris, Proton |
| privacy.sh | Tor, VPN, UFW |
| server.sh | Nginx, PostgreSQL |
| cloud.sh | AWS/GCP, kubectl |
| docker-tools.sh | Docker, Podman |

## Requirements

- 4GB+ RAM
- 20GB+ disk space
- UEFI or BIOS

## License

GPLv3

## Credits

- [Arch Linux](https://archlinux.org)
- [Deepin](https://www.deepin.org)
- [Archiso](https://archlinux.org/packages/extra/any/archiso/)
