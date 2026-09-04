#include "forxostore.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include <QMessageBox>
#include <QInputDialog>
#include <QScrollArea>

struct PackageInfo {
    QString name;
    QString description;
    QString pacmanName;
    QString category;
    bool installed;
};

static QList<PackageInfo> allPackages = {
    // Development
    {"Visual Studio Code", "Code editor by Microsoft", "code", "Development", false},
    {"Neovim", "Modern Vim-based editor", "neovim", "Development", false},
    {"Git", "Version control system", "git", "Development", false},
    {"Docker", "Container platform", "docker", "Development", false},
    {"Node.js", "JavaScript runtime", "nodejs", "Development", false},
    {"Python", "Python programming language", "python", "Development", false},
    {"Go", "Go programming language", "go", "Development", false},
    {"Rust", "Rust programming language", "rust", "Development", false},
    {"CMake", "Build system", "cmake", "Development", false},
    {"GCC", "GNU Compiler Collection", "gcc", "Development", false},

    // Cybersecurity
    {"Nmap", "Network scanner", "nmap", "Cybersecurity", false},
    {"Wireshark", "Network protocol analyzer", "wireshark-qt", "Cybersecurity", false},
    {"Metasploit", "Penetration testing framework", "metasploit", "Cybersecurity", false},
    {"John the Ripper", "Password cracker", "john", "Cybersecurity", false},
    {"Hashcat", "Advanced password recovery", "hashcat", "Cybersecurity", false},
    {"Aircrack-ng", "WiFi security auditing", "aircrack-ng", "Cybersecurity", false},
    {"Burp Suite", "Web vulnerability scanner", "burpsuite", "Cybersecurity", false},
    {"Ghidra", "Reverse engineering tool", "ghidra", "Cybersecurity", false},

    // Terminal Tools
    {"Zsh", "Z Shell", "zsh", "Terminal", false},
    {"Fuzzy Finder", "Fuzzy finder for CLI", "fzf", "Terminal", false},
    {"Bat", "Modern cat clone", "bat", "Terminal", false},
    {"Ripgrep", "Fast grep alternative", "ripgrep", "Terminal", false},
    {"Starship", "Cross-shell prompt", "starship", "Terminal", false},
    {"Btop", "Resource monitor", "btop", "Terminal", false},
    {"Tmux", "Terminal multiplexer", "tmux", "Terminal", false},

    // Multimedia
    {"VLC", "Media player", "vlc", "Multimedia", false},
    {"GIMP", "Image editor", "gimp", "Multimedia", false},
    {"Inkscape", "Vector graphics editor", "inkscape", "Multimedia", false},
    {"OBS Studio", "Screen recording", "obs-studio", "Multimedia", false},
    {"Audacity", "Audio editor", "audacity", "Multimedia", false},

    // Gaming
    {"Steam", "Gaming platform", "steam", "Gaming", false},
    {"Lutris", "Open gaming platform", "lutris", "Gaming", false},
    {"Wine", "Windows compatibility", "wine", "Gaming", false},
    {"Bottles", "Wine manager", "bottles", "Gaming", false},
    {"MangoHud", "FPS overlay", "mangohud", "Gaming", false},

    // System
    {"htop", "Interactive process viewer", "htop", "System", false},
    {"Neofetch", "System info", "neofetch", "System", false},
    {"Timeshift", "System restore", "timeshift", "System", false},
    {"GParted", "Partition editor", "gparted", "System", false},
};

ForxoStore::ForxoStore(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    process = new QProcess(this);
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, [this](int, QProcess::ExitStatus) {
        progressBar->setValue(100);
        statusLabel->setText("Operation complete!");
        refreshPackages();
    });
}

void ForxoStore::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // Header
    QLabel *title = new QLabel("ForxoOS Store");
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: #2a82da;");
    mainLayout->addWidget(title);

    QLabel *subtitle = new QLabel("Install applications with one click");
    subtitle->setStyleSheet("font-size: 14px; color: #888;");
    mainLayout->addWidget(subtitle);

    mainLayout->addSpacing(15);

    QHBoxLayout *contentLayout = new QHBoxLayout();

    // Categories
    QFrame *catFrame = new QFrame();
    catFrame->setStyleSheet("QFrame { background-color: #16213e; border-radius: 10px; }");
    QVBoxLayout *catLayout = new QVBoxLayout(catFrame);
    catLayout->setContentsMargins(10, 10, 10, 10);

    categoryList = new QListWidget();
    categoryList->setStyleSheet(
        "QListWidget { background: transparent; color: white; border: none; font-size: 14px; }"
        "QListWidget::item { padding: 10px; border-radius: 5px; }"
        "QListWidget::item:selected { background-color: #2a82da; }"
    );
    categoryList->addItems({"All", "Development", "Cybersecurity", "Terminal", "Multimedia", "Gaming", "System"});
    connect(categoryList, &QListWidget::currentTextChanged, this, &ForxoStore::showCategory);

    catLayout->addWidget(categoryList);
    contentLayout->addWidget(catFrame, 1);

    // Packages
    QFrame *pkgFrame = new QFrame();
    pkgFrame->setStyleSheet("QFrame { background-color: #16213e; border-radius: 10px; }");
    QVBoxLayout *pkgLayout = new QVBoxLayout(pkgFrame);
    pkgLayout->setContentsMargins(15, 15, 15, 15);

    packageList = new QListWidget();
    packageList->setStyleSheet(
        "QListWidget { background: transparent; color: white; border: none; font-size: 13px; }"
        "QListWidget::item { padding: 12px; border-bottom: 1px solid #333; }"
        "QListWidget::item:selected { background-color: #2a82da; }"
    );
    connect(packageList, &QListWidget::itemDoubleClicked, this, [this](QListWidgetItem *item) {
        installPackage();
    });

    pkgLayout->addWidget(packageList);

    // Buttons
    QHBoxLayout *btnLayout = new QHBoxLayout();
    QPushButton *installBtn = new QPushButton("Install");
    installBtn->setStyleSheet(
        "QPushButton { background-color: #2a82da; color: white; padding: 10px 20px; border-radius: 5px; }"
        "QPushButton:hover { background-color: #3a92ea; }"
    );
    connect(installBtn, &QPushButton::clicked, this, &ForxoStore::installPackage);

    QPushButton *removeBtn = new QPushButton("Remove");
    removeBtn->setStyleSheet(
        "QPushButton { background-color: #e74c3c; color: white; padding: 10px 20px; border-radius: 5px; }"
        "QPushButton:hover { background-color: #f74c3c; }"
    );
    connect(removeBtn, &QPushButton::clicked, this, &ForxoStore::removePackage);

    btnLayout->addStretch();
    btnLayout->addWidget(installBtn);
    btnLayout->addWidget(removeBtn);
    pkgLayout->addLayout(btnLayout);

    // Progress
    progressBar = new QProgressBar();
    progressBar->setRange(0, 0);
    progressBar->setVisible(false);
    progressBar->setStyleSheet(
        "QProgressBar { border: 2px solid #333; border-radius: 5px; height: 20px; }"
        "QProgressBar::chunk { background-color: #2a82da; }"
    );
    pkgLayout->addWidget(progressBar);

    statusLabel = new QLabel("Ready");
    statusLabel->setStyleSheet("color: #888; font-size: 12px;");
    pkgLayout->addWidget(statusLabel);

    contentLayout->addWidget(pkgFrame, 3);
    mainLayout->addLayout(contentLayout);

    // Load
    categoryList->setCurrentRow(0);
    loadPackages();
}

void ForxoStore::showCategory(const QString &category)
{
    currentCategory = category;
    loadPackages();
}

void ForxoStore::loadPackages()
{
    packageList->clear();
    for (const auto &pkg : allPackages) {
        if (currentCategory == "All" || pkg.category == currentCategory) {
            QString status = pkg.installed ? "[Installed]" : "[Available]";
            packageList->addItem(QString("%1 %2 - %3").arg(status, pkg.name, pkg.description));
        }
    }
}

void ForxoStore::installPackage()
{
    int row = packageList->currentRow();
    if (row < 0) return;

    QString text = packageList->item(row)->text();
    for (auto &pkg : allPackages) {
        if (text.contains(pkg.name)) {
            progressBar->setVisible(true);
            statusLabel->setText("Installing " + pkg.name + "...");
            runCommand("sudo pacman -S --needed --noconfirm " + pkg.pacmanName);
            return;
        }
    }
}

void ForxoStore::removePackage()
{
    int row = packageList->currentRow();
    if (row < 0) return;

    QString text = packageList->item(row)->text();
    for (auto &pkg : allPackages) {
        if (text.contains(pkg.name)) {
            progressBar->setVisible(true);
            statusLabel->setText("Removing " + pkg.name + "...");
            runCommand("sudo pacman -Rns --noconfirm " + pkg.pacmanName);
            return;
        }
    }
}

void ForxoStore::refreshPackages()
{
    loadPackages();
}

void ForxoStore::runCommand(const QString &cmd)
{
    process->start("bash", {"-c", cmd});
}
