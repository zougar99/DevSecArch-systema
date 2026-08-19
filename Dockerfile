FROM archlinux:latest

RUN pacman -Syu --noconfirm && \
    pacman -S --noconfirm \
    base-devel git sudo \
    qt6-base qt6-wayland qt6-declarative \
    cmake gcc \
    gedit zsh tmux htop \
    && pacman -Scc --noconfirm

# Create devsec user
RUN useradd -m -G wheel -s /bin/zsh devsec && \
    echo "devsec ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers

# Copy project
COPY . /home/devsec/DevSecArch-systema
RUN chown -R devsec:devsec /home/devsec

USER devsec
WORKDIR /home/devsec/DevSecArch-systema

CMD ["/bin/zsh"]
