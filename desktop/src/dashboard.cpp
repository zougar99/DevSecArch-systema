#include "dashboard.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QGroupBox>
#include <QChart>
#include <QValueAxis>
#include <QDateTime>
#include <QProcess>
#include <QFile>
#include <QTextStream>

Dashboard::Dashboard(QWidget *parent)
    : QWidget(parent)
{
    setupUI();

    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &Dashboard::updateStats);
    updateTimer->start(2000);

    updateStats();
}

Dashboard::~Dashboard()
{
}

void Dashboard::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(16);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // Title
    QLabel *title = new QLabel("System Dashboard");
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: #2a82da;");
    mainLayout->addWidget(title);

    // Grid layout for cards
    QGridLayout *grid = new QGridLayout();
    grid->setSpacing(16);

    createSystemInfoCard();
    createCPUCard();
    createMemoryCard();
    createDiskCard();
    createNetworkCard();
    createQuickActionsCard();

    grid->addWidget(cpuLabel->parentWidget(), 0, 0);
    grid->addWidget(memoryLabel->parentWidget(), 0, 1);
    grid->addWidget(diskLabel->parentWidget(), 0, 2);
    grid->addWidget(networkLabel->parentWidget(), 1, 0);
    grid->addWidget(uptimeLabel->parentWidget(), 1, 1);
    grid->addWidget(processLabel->parentWidget(), 1, 2);

    mainLayout->addLayout(grid);
    mainLayout->addStretch();
}

void Dashboard::createSystemInfoCard()
{
    QFrame *card = new QFrame();
    card->setFrameShape(QFrame::StyledPanel);
    card->setStyleSheet(
        "QFrame { background-color: #2d2d2d; border-radius: 10px; padding: 15px; }"
    );

    QVBoxLayout *layout = new QVBoxLayout(card);

    QLabel *titleLabel = new QLabel("System Info");
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2a82da;");

    uptimeLabel = new QLabel("Uptime: --:--:--");
    processLabel = new QLabel("Processes: --");

    layout->addWidget(titleLabel);
    layout->addWidget(uptimeLabel);
    layout->addWidget(processLabel);
}

void Dashboard::createCPUCard()
{
    QFrame *card = new QFrame();
    card->setFrameShape(QFrame::StyledPanel);
    card->setStyleSheet(
        "QFrame { background-color: #2d2d2d; border-radius: 10px; padding: 15px; }"
    );

    QVBoxLayout *layout = new QVBoxLayout(card);

    QLabel *titleLabel = new QLabel("CPU Usage");
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2a82da;");

    cpuBar = new QProgressBar();
    cpuBar->setRange(0, 100);
    cpuBar->setValue(0);
    cpuBar->setTextVisible(true);
    cpuBar->setStyleSheet(
        "QProgressBar { border: 2px solid #444; border-radius: 5px; text-align: center; height: 20px; }"
        "QProgressBar::chunk { background-color: #2a82da; border-radius: 3px; }"
    );

    layout->addWidget(titleLabel);
    layout->addWidget(cpuBar);
}

void Dashboard::createMemoryCard()
{
    QFrame *card = new QFrame();
    card->setFrameShape(QFrame::StyledPanel);
    card->setStyleSheet(
        "QFrame { background-color: #2d2d2d; border-radius: 10px; padding: 15px; }"
    );

    QVBoxLayout *layout = new QVBoxLayout(card);

    QLabel *titleLabel = new QLabel("Memory Usage");
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2a82da;");

    memoryBar = new QProgressBar();
    memoryBar->setRange(0, 100);
    memoryBar->setValue(0);
    memoryBar->setTextVisible(true);
    memoryBar->setStyleSheet(
        "QProgressBar { border: 2px solid #444; border-radius: 5px; text-align: center; height: 20px; }"
        "QProgressBar::chunk { background-color: #28a745; border-radius: 3px; }"
    );

    layout->addWidget(titleLabel);
    layout->addWidget(memoryBar);
}

void Dashboard::createDiskCard()
{
    QFrame *card = new QFrame();
    card->setFrameShape(QFrame::StyledPanel);
    card->setStyleSheet(
        "QFrame { background-color: #2d2d2d; border-radius: 10px; padding: 15px; }"
    );

    QVBoxLayout *layout = new QVBoxLayout(card);

    QLabel *titleLabel = new QLabel("Disk Usage");
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2a82da;");

    diskBar = new QProgressBar();
    diskBar->setRange(0, 100);
    diskBar->setValue(0);
    diskBar->setTextVisible(true);
    diskBar->setStyleSheet(
        "QProgressBar { border: 2px solid #444; border-radius: 5px; text-align: center; height: 20px; }"
        "QProgressBar::chunk { background-color: #ffc107; border-radius: 3px; }"
    );

    layout->addWidget(titleLabel);
    layout->addWidget(diskBar);
}

void Dashboard::createNetworkCard()
{
    QFrame *card = new QFrame();
    card->setFrameShape(QFrame::StyledPanel);
    card->setStyleSheet(
        "QFrame { background-color: #2d2d2d; border-radius: 10px; padding: 15px; }"
    );

    QVBoxLayout *layout = new QVBoxLayout(card);

    QLabel *titleLabel = new QLabel("Network");
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2a82da;");

    networkLabel = new QLabel("Status: Connected");

    layout->addWidget(titleLabel);
    layout->addWidget(networkLabel);
}

void Dashboard::createQuickActionsCard()
{
    QFrame *card = new QFrame();
    card->setFrameShape(QFrame::StyledPanel);
    card->setStyleSheet(
        "QFrame { background-color: #2d2d2d; border-radius: 10px; padding: 15px; }"
    );

    QVBoxLayout *layout = new QVBoxLayout(card);

    QLabel *titleLabel = new QLabel("Quick Actions");
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2a82da;");

    QPushButton *updateBtn = new QPushButton("System Update");
    QPushButton *scanBtn = new QPushButton("Security Scan");
    QPushButton *backupBtn = new QPushButton("Backup");

    QString btnStyle = "QPushButton { background-color: #2a82da; color: white; border: none; "
                       "padding: 10px 20px; border-radius: 5px; font-size: 12px; }"
                       "QPushButton:hover { background-color: #3a92ea; }";

    updateBtn->setStyleSheet(btnStyle);
    scanBtn->setStyleSheet(btnStyle.replace("#2a82da", "#28a745").replace("#3a92ea", "#38b74f"));
    backupBtn->setStyleSheet(btnStyle.replace("#2a82da", "#ffc107").replace("#3a92ea", "#ffcd38"));

    layout->addWidget(titleLabel);
    layout->addWidget(updateBtn);
    layout->addWidget(scanBtn);
    layout->addWidget(backupBtn);
}

void Dashboard::updateStats()
{
    // CPU usage
    QFile statFile("/proc/stat");
    if (statFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&statFile);
        QString line = in.readLine();
        statFile.close();

        QStringList values = line.split(" ");
        if (values.size() >= 5) {
            long idle = values[4].toLong();
            long total = 0;
            for (int i = 1; i < values.size(); i++) {
                total += values[i].toLong();
            }
            int usage = (total > 0) ? ((total - idle) * 100 / total) : 0;
            cpuBar->setValue(usage);
        }
    }

    // Memory usage
    QFile memFile("/proc/meminfo");
    if (memFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&memFile);
        long total = 0, available = 0;

        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line.startsWith("MemTotal:")) {
                total = line.split(" ")[1].toLong();
            } else if (line.startsWith("MemAvailable:")) {
                available = line.split(" ")[1].toLong();
            }
        }
        memFile.close();

        if (total > 0) {
            int usage = ((total - available) * 100) / total;
            memoryBar->setValue(usage);
        }
    }

    // Disk usage
    QStorageInfo storage = QStorageInfo::root();
    int diskUsage = 100 - (storage.bytesAvailable() * 100 / storage.bytesTotal());
    diskBar->setValue(diskUsage);

    // Uptime
    QFile uptimeFile("/proc/uptime");
    if (uptimeFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&uptimeFile);
        double uptime = in.readLine().split(" ")[0].toDouble();
        uptimeFile.close();

        int hours = (int)(uptime / 3600);
        int minutes = ((int)(uptime / 60)) % 60;
        int seconds = (int)uptime % 60;

        uptimeLabel->setText(QString("Uptime: %1:%2:%3")
            .arg(hours).arg(minutes).arg(seconds));
    }

    // Process count
    QFile loadAvg("/proc/loadavg");
    if (loadAvg.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&loadAvg);
        QString line = in.readLine();
        loadAvg.close();
        processLabel->setText("Load Avg: " + line.split(" ").mid(0, 3).join(", "));
    }
}
