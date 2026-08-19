#!/usr/bin/env bash
#===============================================================================
# Development Tools Module - Complete Dev Stack
#===============================================================================

install_dev_tools() {
    log "=== Installing Development Tools ==="

    # ── Editors & IDEs ─────────────────────────────────────────────────────
    log "[1/10] Editors and IDEs..."
    pacman -S --needed --noconfirm \
        code neovim helix micro

    if command -v code &>/dev/null; then
        code --install-extension ms-python.python 2>/dev/null || true
        code --install-extension ms-python.vscode-pylance 2>/dev/null || true
        code --install-extension dbaeumer.vscode-eslint 2>/dev/null || true
        code --install-extension esbenp.prettier-vscode 2>/dev/null || true
        code --install-extension rust-lang.rust-analyzer 2>/dev/null || true
        code --install-extension golang.go 2>/dev/null || true
        code --install-extension ms-azuretools.vscode-docker 2>/dev/null || true
        code --install-extension github.vscode-pull-request-github 2>/dev/null || true
        code --install-extension redhat.java 2>/dev/null || true
        code --install-extension ms-python.debugpy 2>/dev/null || true
        code --install-extension ms-python.isort 2>/dev/null || true
        code --install-extension vscodevim.vim 2>/dev/null || true
        code --install-extension ms-vscode.cpptools 2>/dev/null || true
        code --install-extension vadimcn.vscode-lldb 2>/dev/null || true
    fi

    # ── Git ────────────────────────────────────────────────────────────────
    log "[2/10] Git tools..."
    pacman -S --needed --noconfirm \
        git git-delta lazygit tig gitui git-lfs

    # ── Languages ──────────────────────────────────────────────────────────
    log "[3/10] Programming languages..."
    
    # Python
    pacman -S --needed --noconfirm \
        python python-pip python-virtualenv python-pipenv python-poetry \
        python-black python-flake8 python-mypy python-pytest \
        python-numpy python-scipy python-pandas python-matplotlib \
        jupyterlab ipython

    # Node.js
    pacman -S --needed --noconfirm \
        nodejs npm yarn pnpm bun deno

    # Java
    pacman -S --needed --noconfirm \
        jdk-openjdk jdk-openjdk17 jdk-openjdk21 \
        maven gradle ant

    # Go
    pacman -S --needed --noconfirm \
        go

    # Rust
    pacman -S --needed --noconfirm \
        rust cargo rustup

    # C/C++
    pacman -S --needed --noconfirm \
        gcc gcc-fortran clang clang-tools-extra cmake make ninja gdb valgrind

    # Other
    pacman -S --needed --noconfirm \
        ruby php lua swift kotlin

    # ── Mobile Development ─────────────────────────────────────────────────
    log "[4/10] Mobile development..."
    pacman -S --needed --noconfirm \
        android-sdk android-tools

    # Flutter
    yay -S --needed --noconfirm flutter 2>/dev/null || true
    yay -S --needed --noconfirm dart 2>/dev/null || true

    # React Native
    npm install -g react-native-cli 2>/dev/null || true

    # ── AI/ML ──────────────────────────────────────────────────────────────
    log "[5/10] AI/ML tools..."
    pacman -S --needed --noconfirm \
        python-tensorflow python-pytorch python-scikit-learn \
        python-opencv python-pillow python-nltk python-spacy

    # ── Containers ─────────────────────────────────────────────────────────
    log "[6/10] Docker & DevOps..."
    pacman -S --needed --noconfirm \
        docker docker-compose docker-buildx \
        podman podman-compose \
        kubectl helm terraform ansible vagrant packer \
        vault consul nomad

    systemctl enable docker 2>/dev/null || true
    systemctl enable podman 2>/dev/null || true

    # ── Databases ──────────────────────────────────────────────────────────
    log "[7/10] Databases..."
    pacman -S --needed --noconfirm \
        postgresql mariadb redis sqlite dbeaver \
        mongodb-bin 2>/dev/null || true

    systemctl enable postgresql 2>/dev/null || true
    systemctl enable mariadb 2>/dev/null || true
    systemctl enable redis 2>/dev/null || true

    # ── Web Development ────────────────────────────────────────────────────
    log "[8/10] Web development..."
    pacman -S --needed --noconfirm \
        nginx mkcert certbot httpie

    # ── Qt Development ────────────────────────────────────────────────────
    log "[9/10] Qt SDK..."
    pacman -S --needed --noconfirm \
        qt6-base qt6-declarative qt6-multimedia qt6-tools \
        qt6-5compat qt6-wayland qt6-shadertools qt6-svg \
        qt6-imageformats qt6-webengine qt6-webchannel \
        qt6-positioning qt6-serialport qt6-3d qt6-charts \
        qt6-datavis3d qt6-labs-animation qt6-labs-blueprint \
        qt6-labs-folderlistmodel qt6-labs-graphicaleffects \
        qt6-labs-platform qt6-labs-qmlmodels qt6-labs-settings \
        qt6-labs-sharedimage qt6-labs-wavefrontmesh \
        qt6-quick3d qt6-quicktimeline qt6-state-machine \
        qt6-virtualkeyboard qt6-websockets \
        qtcreator cmake extra-cmake-modules ninja pkgconf

    # ── Build Tools ────────────────────────────────────────────────────────
    log "[10/10] Build essentials..."
    pacman -S --needed --noconfirm \
        base-devel boost openssl zlib curl readline sqlite \
        libffi libyaml libxml2 protobuf grpc

    log "Development tools installed successfully"
}

install_dev_tools
