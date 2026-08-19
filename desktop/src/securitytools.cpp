#include "securitytools.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QProcess>
#include <QFrame>

SecurityTools::SecurityTools(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
}

SecurityTools::~SecurityTools()
{
}

void SecurityTools::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // Title
    QFrame *header = new QFrame();
    header->setStyleSheet("QFrame { background-color: #252525; padding: 10px; }");
    QHBoxLayout *headerLayout = new QHBoxLayout(header);

    QLabel *title = new QLabel("Security Tools");
    title->setStyleSheet("font-size: 20px; font-weight: bold; color: #2a82da;");
    headerLayout->addWidget(title);
    headerLayout->addStretch();

    mainLayout->addWidget(header);

    // Tab widget
    toolTabs = new QTabWidget();
    createNmapTab();
    createWifiTab();
    createPentestTab();
    createForensicsTab();

    mainLayout->addWidget(toolTabs);
}

void SecurityTools::createNmapTab()
{
    QWidget *tab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(tab);

    // Input section
    QFrame *inputFrame = new QFrame();
    inputFrame->setStyleSheet("QFrame { background-color: #2d2d2d; border-radius: 8px; padding: 10px; }");
    QGridLayout *inputLayout = new QGridLayout(inputFrame);

    QLabel *targetLabel = new QLabel("Target:");
    targetLabel->setStyleSheet("color: white; font-weight: bold;");

    targetInput = new QLineEdit();
    targetInput->setPlaceholderText("Enter IP or hostname (e.g., 192.168.1.1)");
    targetInput->setStyleSheet(
        "QLineEdit { background-color: #353535; color: white; border: 1px solid #444; "
        "padding: 10px; border-radius: 5px; font-size: 14px; }"
    );

    QLabel *typeLabel = new QLabel("Scan Type:");
    typeLabel->setStyleSheet("color: white; font-weight: bold;");

    scanType = new QComboBox();
    scanType->addItems({"Quick Scan", "Full Scan", "Stealth Scan", "UDP Scan", "Service Detection"});
    scanType->setStyleSheet(
        "QComboBox { background-color: #353535; color: white; border: 1px solid #444; "
        "padding: 10px; border-radius: 5px; }"
    );

    scanBtn = new QPushButton("Start Scan");
    scanBtn->setStyleSheet(
        "QPushButton { background-color: #dc3545; color: white; border: none; "
        "padding: 10px 30px; border-radius: 5px; font-size: 14px; font-weight: bold; }"
        "QPushButton:hover { background-color: #e34253; }"
    );

    inputLayout->addWidget(targetLabel, 0, 0);
    inputLayout->addWidget(targetInput, 0, 1);
    inputLayout->addWidget(typeLabel, 0, 2);
    inputLayout->addWidget(scanType, 0, 3);
    inputLayout->addWidget(scanBtn, 0, 4);

    layout->addWidget(inputFrame);

    // Progress
    progressBar = new QProgressBar();
    progressBar->setRange(0, 0);
    progressBar->setVisible(false);
    layout->addWidget(progressBar);

    // Output
    output = new QTextEdit();
    output->setReadOnly(true);
    output->setStyleSheet(
        "QTextEdit { background-color: #1e1e1e; color: #00ff00; border: none; "
        "font-family: 'Cascadia Code', monospace; font-size: 12px; }"
    );
    layout->addWidget(output);

    // Quick tools
    QFrame *toolsFrame = new QFrame();
    toolsFrame->setStyleSheet("QFrame { background-color: #2d2d2d; border-radius: 8px; padding: 10px; }");
    QHBoxLayout *toolsLayout = new QHBoxLayout(toolsFrame);

    toolsList = new QListWidget();
    toolsList->setFlow(QListView::LeftToRight);
    toolsList->setMaximumHeight(60);

    QStringList tools = {"Nmap", "Wireshark", "Aircrack-ng", "John", "Hydra", "SQLmap", "Nikto", "Gobuster"};
    toolsList->addItems(tools);

    toolsLayout->addWidget(toolsList);
    layout->addWidget(toolsFrame);

    // Connections
    connect(scanBtn, &QPushButton::clicked, this, &SecurityTools::runNmap);

    toolTabs->addTab(tab, "Network Scanner");
}

void SecurityTools::createWifiTab()
{
    QWidget *tab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(tab);

    QLabel *title = new QLabel("WiFi Tools");
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #2a82da;");
    layout->addWidget(title);

    QGridLayout *grid = new QGridLayout();

    // WiFi tools cards
    QString cardStyle = "QFrame { background-color: #2d2d2d; border-radius: 8px; padding: 15px; }";
    QString btnStyle = "QPushButton { background-color: #2a82da; color: white; border: none; "
                       "padding: 10px 20px; border-radius: 5px; font-size: 12px; }"
                       "QPushButton:hover { background-color: #3a92ea; }";

    // Aircrack-ng
    QFrame *aircrackCard = new QFrame();
    aircrackCard->setStyleSheet(cardStyle);
    QVBoxLayout *aircrackLayout = new QVBoxLayout(aircrackCard);
    aircrackLayout->addWidget(new QLabel("Aircrack-ng"));
    QPushButton *aircrackBtn = new QPushButton("Launch");
    aircrackBtn->setStyleSheet(btnStyle);
    aircrackLayout->addWidget(aircrackBtn);
    grid->addWidget(aircrackCard, 0, 0);

    // Reaver
    QFrame *reaverCard = new QFrame();
    reaverCard->setStyleSheet(cardStyle);
    QVBoxLayout *reaverLayout = new QVBoxLayout(reaverCard);
    reaverLayout->addWidget(new QLabel("Reaver"));
    QPushButton *reaverBtn = new QPushButton("Launch");
    reaverBtn->setStyleSheet(btnStyle);
    reaverLayout->addWidget(reaverBtn);
    grid->addWidget(reaverCard, 0, 1);

    // Wifite2
    QFrame *wifiteCard = new QFrame();
    wifiteCard->setStyleSheet(cardStyle);
    QVBoxLayout *wifiteLayout = new QVBoxLayout(wifiteCard);
    wifiteLayout->addWidget(new QLabel("Wifite2"));
    QPushButton *wifiteBtn = new QPushButton("Launch");
    wifiteBtn->setStyleSheet(btnStyle);
    wifiteLayout->addWidget(wifiteBtn);
    grid->addWidget(wifiteCard, 0, 2);

    // Kismet
    QFrame *kismetCard = new QFrame();
    kismetCard->setStyleSheet(cardStyle);
    QVBoxLayout *kismetLayout = new QVBoxLayout(kismetCard);
    kismetLayout->addWidget(new QLabel("Kismet"));
    QPushButton *kismetBtn = new QPushButton("Launch");
    kismetBtn->setStyleSheet(btnStyle);
    kismetLayout->addWidget(kismetBtn);
    grid->addWidget(kismetCard, 1, 0);

    // Bettercap
    QFrame *bettercapCard = new QFrame();
    bettercapCard->setStyleSheet(cardStyle);
    QVBoxLayout *bettercapLayout = new QVBoxLayout(bettercapCard);
    bettercapLayout->addWidget(new QLabel("Bettercap"));
    QPushButton *bettercapBtn = new QPushButton("Launch");
    bettercapBtn->setStyleSheet(btnStyle);
    bettercapLayout->addWidget(bettercapBtn);
    grid->addWidget(bettercapCard, 1, 1);

    layout->addLayout(grid);
    layout->addStretch();

    toolTabs->addTab(tab, "WiFi Tools");
}

void SecurityTools::createPentestTab()
{
    QWidget *tab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(tab);

    QLabel *title = new QLabel("Penetration Testing");
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #2a82da;");
    layout->addWidget(title);

    QGridLayout *grid = new QGridLayout();
    QString cardStyle = "QFrame { background-color: #2d2d2d; border-radius: 8px; padding: 15px; }";
    QString btnStyle = "QPushButton { background-color: #28a745; color: white; border: none; "
                       "padding: 10px 20px; border-radius: 5px; font-size: 12px; }"
                       "QPushButton:hover { background-color: #38b74f; }";

    QStringList tools = {"Metasploit", "Burp Suite", "SQLmap", "Nikto", "Gobuster", "Hydra", "John", "Hashcat"};
    for (int i = 0; i < tools.size(); i++) {
        QFrame *card = new QFrame();
        card->setStyleSheet(cardStyle);
        QVBoxLayout *cardLayout = new QVBoxLayout(card);
        cardLayout->addWidget(new QLabel(tools[i]));
        QPushButton *btn = new QPushButton("Launch");
        btn->setStyleSheet(btnStyle);
        cardLayout->addWidget(btn);
        grid->addWidget(card, i / 3, i % 3);
    }

    layout->addLayout(grid);
    layout->addStretch();

    toolTabs->addTab(tab, "Pentest");
}

void SecurityTools::createForensicsTab()
{
    QWidget *tab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(tab);

    QLabel *title = new QLabel("Forensics & RE");
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #2a82da;");
    layout->addWidget(title);

    QGridLayout *grid = new QGridLayout();
    QString cardStyle = "QFrame { background-color: #2d2d2d; border-radius: 8px; padding: 15px; }";
    QString btnStyle = "QPushButton { background-color: #ffc107; color: black; border: none; "
                       "padding: 10px 20px; border-radius: 5px; font-size: 12px; }"
                       "QPushButton:hover { background-color: #ffcd38; }";

    QStringList tools = {"Ghidra", "Radare2", "Binwalk", "Foremost", "Wireshark", "tcpdump"};
    for (int i = 0; i < tools.size(); i++) {
        QFrame *card = new QFrame();
        card->setStyleSheet(cardStyle);
        QVBoxLayout *cardLayout = new QVBoxLayout(card);
        cardLayout->addWidget(new QLabel(tools[i]));
        QPushButton *btn = new QPushButton("Launch");
        btn->setStyleSheet(btnStyle);
        cardLayout->addWidget(btn);
        grid->addWidget(card, i / 3, i % 3);
    }

    layout->addLayout(grid);
    layout->addStretch();

    toolTabs->addTab(tab, "Forensics");
}

void SecurityTools::runNmap()
{
    QString target = targetInput->text();
    if (target.isEmpty()) {
        output->setText("Please enter a target");
        return;
    }

    progressBar->setVisible(true);
    output->clear();
    output->append("Starting scan on: " + target);
    output->append("================================");

    QString scanFlag;
    switch (scanType->currentIndex()) {
        case 0: scanFlag = "-sV -T4"; break;
        case 1: scanFlag = "-A -p- -T4"; break;
        case 2: scanFlag = "-sS -T2"; break;
        case 3: scanFlag = "-sU -T4"; break;
        case 4: scanFlag = "-sV -sC"; break;
    }

    QProcess *process = new QProcess(this);
    connect(process, &QProcess::readyReadStandardOutput, this, [this, process]() {
        output->append(process->readAllStandardOutput());
    });
    connect(process, &QProcess::readyReadStandardError, this, [this, process]() {
        output->append(process->readAllStandardError());
    });
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        this, [this](int, QProcess::ExitStatus) {
        progressBar->setVisible(false);
        output->append("\nScan complete!");
    });

    process->start("nmap", {scanFlag, target});
}

void SecurityTools::runScan()
{
    runNmap();
}

void SecurityTools::updateOutput()
{
}
