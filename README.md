# ForxoOS

> Custom Arch Linux with Deepin Desktop - Beautiful, Secure, Fast.

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

## What is ForxoOS?

ForxoOS is an **unofficial Arch Linux distribution** with **Deepin Desktop Environment**. Beautiful like Deepin, powerful like Arch.

**Not affiliated with Arch Linux or Deepin.**

### Features

- **Deepin Desktop (DDE)** - Beautiful, modern desktop environment
- **Deepin Installer** - Qt6 GUI installer (Language, Keyboard, Disk, User, Install)
- **Minimal ISO** - ~2GB, fast boot, clean install
- **Wine/Bottles** - Windows app compatibility (optional post-install)
- **500+ Tools** - Dev, Security, Gaming, Multimedia via ForxoOS Store
- **Multi-language** - English, Arabic, French + 13 more
- **ERASE Confirm** - Full disk wipe requires typed confirmation

## Quick Start

### Download ISO
Go to [Releases](https://github.com/zougar99/DevSecArch-systema/releases) and download the latest ISO.

### Install
1. Boot from USB (Secure Boot OFF)
2. Auto-login as `devsec`
3. Run ForxoOS Installer from desktop
4. Select "Erase entire disk" + type ERASE to confirm
5. Reboot when done

### Post-Install Tools
```bash
# Open ForxoOS Store from desktop, or:
forxoinstall
```

## Project Structure

```
ForxoOS/
├── iso/                    # ISO profile (archiso)
│   ├── profile/
│   │   ├── profiledef.sh
│   │   ├── packages.x86_64
│   │   └── airootfs/
│   └── build.sh
├── installer/              # Qt6 GUI Installer
├── desktop/                # Qt6 Desktop App + ForxoOS Store
├── modules/                # Optional post-install scripts
│   ├── wine-compat.sh      # Wine/Bottles/DXVK
│   ├── devtools.sh         # Development tools
│   ├── cybersec.sh         # Cybersecurity tools
│   └── ...
├── install.sh              # Post-install tool script
└── .github/workflows/      # CI/CD
```

## Windows App Compatibility

ForxoOS supports running some Windows `.exe` files via Wine/Bottles:

```bash
# Install Wine compatibility
sudo bash modules/wine-compat.sh

# Run .exe files
forxo-run-exe myapp.exe
# Or right-click .exe → Open with Wine/Bottles
```

**Note:** Not all .exe files work (drivers, anti-cheat, .NET desktop apps may fail).

## License

GPLv3 - Based on Arch Linux
