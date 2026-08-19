# DevSecArch

> Custom Arch Linux distribution - Developer + Security + Everything.

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg)](CONTRIBUTING.md)

## What is DevSecArch?

DevSecArch is a **complete custom Arch Linux distribution** in one repository. It includes everything you need:

- **Custom ISO Builder** - Build your own Arch Linux ISO
- **19 Module Categories** - 500+ pre-installed packages
- **GUI Installer** - Windows-like installation experience (Qt 6)
- **Desktop App** - Qt 6 system management application
- **Windows Compatibility** - Wine, Proton, run .exe on Linux
- **Gaming** - Steam, Lutris, Proton-GE, MangoHud
- **Gaming** - Steam, Lutris, Proton-GE, MangoHud
- **Cybersecurity** - 100+ pentest tools
- **Server/Cloud** - Docker, Kubernetes, Ansible, Terraform

## Project Structure

```
DevSecArch/
├── install.sh                  # Post-install script (24 menu options)
├── build-iso.sh                # Build custom ISO
├── test-install.sh             # Verify installation
├── modules/                    # 19 install modules
│   ├── desktops.sh             # GNOME, KDE, i3, Sway, COSMIC
│   ├── gpu.sh                  # NVIDIA, AMD, Intel
│   ├── devtools.sh             # Python, Node, Go, Rust, Qt 6
│   ├── cybersec.sh             # 100+ security tools
│   ├── wifi.sh                 # WiFi attack tools
│   ├── terminal.sh             # Zsh, fzf, bat, lazygit
│   ├── media.sh                # FFmpeg, OBS, GIMP, Blender
│   ├── productivity.sh         # LibreOffice, Obsidian
│   ├── gaming.sh               # Steam, Lutris, Proton
│   ├── privacy.sh              # Signal, Tor, UFW, KeePassXC
│   ├── networking.sh           # Wireshark, VPN, monitoring
│   ├── server.sh               # Nginx, PostgreSQL, Prometheus
│   ├── cloud.sh                # AWS/Azure/GCP, kubectl
│   ├── iot.sh                  # MQTT, Arduino, PlatformIO
│   ├── embedded.sh             # ARM GCC, OpenOCD
│   ├── blockchain.sh           # Solidity, Hardhat
│   ├── docker-tools.sh         # Docker, Podman, Dive
│   ├── windows-compat.sh       # Wine, Proton, PDF, Office
│   └── configs.sh              # System configurations
├── installer/                  # GUI Installer (Qt 6)
│   ├── CMakeLists.txt
│   └── src/                    # 9 wizard pages
├── desktop/                    # Desktop App (Qt 6)
│   ├── CMakeLists.txt
│   └── src/                    # FileManager, Terminal, etc.
├── iso/                        # ISO Profile (archiso)
│   ├── build.sh                # ISO builder
│   ├── profile/
│   │   ├── profiledef.sh       # Archiso profile
│   │   ├── pacman.conf         # Pacman config
│   │   ├── packages.x86_64     # Package list
│   │   ├── grub/grub.cfg       # Boot menu
│   │   └── airootfs/           # Live system configs
│   └── scripts/
├── configs/                    # Config files
└── .github/workflows/          # CI/CD
```

## Quick Start

### Build ISO (on Arch Linux)
```bash
git clone https://github.com/zougar99/DevSecArch.git
cd DevSecArch/iso
sudo ./build.sh
```

### Post-Install (after fresh Arch install)
```bash
git clone https://github.com/zougar99/DevSecArch.git
cd DevSecArch
sudo ./install.sh
```

### Build GUI Installer
```bash
cd installer
mkdir build && cd build
cmake ..
make
sudo ./ArchInstall-GUI
```

### Build Desktop App
```bash
cd desktop
mkdir build && cd build
cmake ..
make
./DevSecArch-Desktop
```

## Menu Options (install.sh)

| Option | Description |
|---|---|
| 1 | Everything (recommended) |
| 2 | Developer Setup |
| 3 | Security Setup |
| 4 | Server Setup |
| 5 | Cloud Setup |
| 6 | Minimal Setup |
| 7 | Custom (choose each) |
| 8-24 | Individual modules |

## Default Credentials

- User: `devsec`
- Password: `root`

## Requirements

- Arch Linux (fresh install or existing system)
- Internet connection
- 32GB+ RAM recommended
- 100GB+ free disk space

## License

GPLv3 - See [LICENSE](LICENSE) for details.
