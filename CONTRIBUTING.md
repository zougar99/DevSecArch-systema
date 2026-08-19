# Contributing to DevSecArch

Thanks for your interest in contributing to DevSecArch! This document provides guidelines and information for contributors.

## What is DevSecArch?

DevSecArch is an open-source Arch Linux-based distribution designed for developers and cybersecurity professionals. It comes pre-configured with development tools, cybersecurity tools, WiFi tools, and multiple desktop environments.

## How to Contribute

### 1. Report Bugs

If you find a bug, please open an issue with:

- Clear description of the problem
- Steps to reproduce
- Expected vs actual behavior
- System info (`uname -a`, `lsb_release -a`)
- Logs if applicable

### 2. Suggest Features

Feature requests are welcome! Please open an issue with:

- Description of the feature
- Why it would be useful
- Use case examples

### 3. Submit Code

1. Fork the repository
2. Create a feature branch: `git checkout -b feature/my-feature`
3. Make your changes
4. Test on a real Arch system
5. Commit: `git commit -m "Add: description of change"`
6. Push: `git push origin feature/my-feature`
7. Open a Pull Request

### 4. Add New Tools

To add a new tool to a module:

1. Edit the appropriate module file in `modules/`
2. Add the package to the correct section
3. Test the installation
4. Submit a PR

### 5. Improve Documentation

- Fix typos
- Add examples
- Improve descriptions
- Add translations

## Development Setup

### Prerequisites

- An Arch Linux system (or VM)
- `git`, `base-devel`
- `archiso` (for ISO building)

### Local Development

```bash
# Clone the repo
git clone https://github.com/YOUR_USERNAME/arch-devsec-build.git
cd arch-devsec-build

# Test individual modules
sudo bash modules/devtools.sh

# Build test ISO
sudo ./build-iso.sh
```

## Project Structure

```
arch-devsec-build/
├── install.sh              # Main installer
├── build-iso.sh            # ISO builder
├── LICENSE                 # GPLv3
├── README.md               # Project documentation
├── CONTRIBUTING.md         # This file
├── modules/
│   ├── desktops.sh         # Desktop environments
│   ├── gpu.sh              # GPU drivers
│   ├── devtools.sh         # Development tools
│   ├── cybersec.sh         # Cybersecurity tools
│   ├── wifi.sh             # WiFi tools
│   ├── terminal.sh         # Terminal tools
│   └── configs.sh          # System configurations
├── configs/
│   └── (config files)
├── .github/
│   ├── ISSUE_TEMPLATE/
│   └── workflows/
└── docs/
    └── (documentation)
```

## Code Style

- Use `bash` for all scripts
- Follow existing code patterns
- Add comments for complex logic
- Use functions for modularity
- Handle errors gracefully

## Testing

Before submitting a PR:

1. Test on a clean Arch install
2. Test each module individually
3. Test the full installation
4. Test the ISO build
5. Verify all tools work

## Community

- GitHub Issues: For bugs and features
- Discussions: For questions and ideas
- Discord: Coming soon

## License

By contributing, you agree that your contributions will be licensed under the GPLv3 License.

## Questions?

Open an issue or start a discussion. We're happy to help!
