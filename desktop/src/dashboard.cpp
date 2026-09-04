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
#include <QStorageInfo>
#include <QListWidget>
#include <QPushButton>

#include <QLinearGradient>
#include <QPen>
#include <QChartView>
#include <QLineSeries>

Dashboard::Dashboard(QWidget *parent)
    : QWidget(parent)
    , prevNet{0, 0}
    , hasPrevNet(false)
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

QColor Dashboard::usageColor(int percent)
{
    if (percent < 50) return QColor("#2ecc71");
    if (percent < 80) return QColor("#f39c12");
    return QColor("#e74c3c");
}

QString Dashboard::formatSize(double bytes)
{
    const char *units[] = {"B", "KB", "MB", "GB", "TB"};
    int i = 0;
    while (bytes >= 1024 && i < 4) {
        bytes /= 1024;
        i++;
    }
    return QString("%1 %2").arg(bytes, 0, 'f', 1).arg(units[i]);
}

void Dashboard::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(16);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    QLabel *title = new QLabel("ForxoOS Dashboard");
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: #2a82da;");
    mainLayout->addWidget(title);

    QGridLayout *grid = new QGridLayout();
    grid->setSpacing(16);

    createSystemInfoCard();
    createCPUCard();
    createMemoryCard();
    createGPUCard();
    createDiskCard();
    createNetworkCard();
    createQuickActionsCard();

    grid->addWidget(cpuLabel->parentWidget(), 0, 0);
    grid->addWidget(memoryLabel->parentWidget(), 0, 1);
    grid->addWidget(diskLabel->parentWidget(), 0, 2);
    grid->addWidget(gpuInfoLabel->parentWidget(), 1, 0);
    grid->addWidget(networkLabel->parentWidget(), 1, 1);
    grid->addWidget(hostnameLabel->parentWidget(), 1, 2);

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

    hostnameLabel = new QLabel("Hostname: --");
    hostnameLabel->setStyleSheet("color: #ccc;");
    kernelLabel = new QLabel("Kernel: --");
    kernelLabel->setStyleSheet("color: #ccc;");
    uptimeLabel = new QLabel("Uptime: --:--:--");
    uptimeLabel->setStyleSheet("color: #ccc;");
    processLabel = new QLabel("Processes: --");
    processLabel->setStyleSheet("color: #ccc;");

    layout->addWidget(titleLabel);
    layout->addWidget(hostnameLabel);
    layout->addWidget(kernelLabel);
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

    cpuLabel = new QLabel("0%");
    cpuLabel->setStyleSheet("font-size: 28px; font-weight: bold; color: #2ecc71;");

    cpuBar = new QProgressBar();
    cpuBar->setRange(0, 100);
    cpuBar->setValue(0);
    cpuBar->setTextVisible(false);
    cpuBar->setStyleSheet(
        "QProgressBar { background: #333; border-radius: 5px; height: 12px; }"
        "QProgressBar::chunk { background-color: #2a82da; border-radius: 5px; }"
    );

    layout->addWidget(titleLabel);
    layout->addWidget(cpuLabel);
    layout->addWidget(cpuBar);

    // CPU chart
    QChart *chart = new QChart();
    chart->setBackgroundVisible(false);
    chart->legend()->hide();
    cpuSeries = new QLineSeries();
    chart->addSeries(cpuSeries);
    chart->createDefaultAxes();
    chart->axisY()->setRange(0, 100);

    QChartView *chartView = new QChartView(chart);
    chartView->setMinimumHeight(120);
    chartView->setStyleSheet("background: transparent;");
    layout->addWidget(chartView);
}

void Dashboard::createMemoryCard()
{
    QFrame *card = new QFrame();
    card->setFrameShape(QFrame::StyledPanel);
    card->setStyleSheet(
        "QFrame { background-color: #2d2d2d; border-radius: 10px; padding: 15px; }"
    );

    QVBoxLayout *layout = new QVBoxLayout(card);

    QLabel *titleLabel = new QLabel("Memory (RAM)");
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2a82da;");

    memoryLabel = new QLabel("0%");
    memoryLabel->setStyleSheet("font-size: 22px; font-weight: bold; color: #2ecc71;");

    memoryBar = new QProgressBar();
    memoryBar->setRange(0, 100);
    memoryBar->setValue(0);
    memoryBar->setTextVisible(false);
    memoryBar->setStyleSheet(
        "QProgressBar { background: #333; border-radius: 5px; height: 12px; }"
        "QProgressBar::chunk { background-color: #2ecc71; border-radius: 5px; }"
    );

    layout->addWidget(titleLabel);
    layout->addWidget(memoryLabel);
    layout->addWidget(memoryBar);

    QLabel *memDetailLabel = new QLabel("Used: -- / --");
    memDetailLabel->setStyleSheet("color: #888; font-size: 12px;");
    layout->addWidget(memDetailLabel);

    // Store as member for updates
    memDetail = memDetailLabel;
}

void Dashboard::createGPUCard()
{
    QFrame *card = new QFrame();
    card->setFrameShape(QFrame::StyledPanel);
    card->setStyleSheet(
        "QFrame { background-color: #2d2d2d; border-radius: 10px; padding: 15px; }"
    );

    QVBoxLayout *layout = new QVBoxLayout(card);

    QLabel *titleLabel = new QLabel("Graphics (GPU)");
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2a82da;");

    gpuInfoLabel = new QLabel("Detecting GPU...");
    gpuInfoLabel->setStyleSheet("color: #ccc;");

    layout->addWidget(titleLabel);
    layout->addWidget(gpuInfoLabel);
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

    diskLabel = new QLabel("0%");
    diskLabel->setStyleSheet("font-size: 22px; font-weight: bold; color: #2ecc71;");

    diskBar = new QProgressBar();
    diskBar->setRange(0, 100);
    diskBar->setValue(0);
    diskBar->setTextVisible(false);
    diskBar->setStyleSheet(
        "QProgressBar { background: #333; border-radius: 5px; height: 12px; }"
        "QProgressBar::chunk { background-color: #f39c12; border-radius: 5px; }"
    );

    diskDetail = new QLabel("Used: -- / --");
    diskDetail->setStyleSheet("color: #888; font-size: 12px;");

    layout->addWidget(titleLabel);
    layout->addWidget(diskLabel);
    layout->addWidget(diskBar);
    layout->addWidget(diskDetail);
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

    networkLabel = new QLabel("---");
    networkLabel->setStyleSheet("color: #ccc;");

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
    // CPU usage (from /proc/stat, delta between reads)
    static QMap<QString, qulonglong> prevCpuTimes;
    QFile statFile("/proc/stat");
    if (statFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&statFile);
        QString line;
        while (!(line = in.readLine()).isNull()) {
            if (line.startsWith("cpu ")) break;
        }
        statFile.close();

        QStringList values = line.split(QRegularExpression("\\s+"));
        values.removeFirst(); // remove "cpu"

        qulonglong idle = 0, total = 0;
        for (int i = 0; i < values.size(); i++) {
            qulonglong v = values[i].toULongLong();
            total += v;
            if (i >= 3) idle += v; // idle + iowait
        }

        qulonglong prevTotal = prevCpuTimes.value("total", 0);
        qulonglong prevIdle = prevCpuTimes.value("idle", 0);

        int usage = 0;
        if (prevTotal > 0) {
            qulonglong dTotal = total - prevTotal;
            qulonglong dIdle = idle - prevIdle;
            usage = (dTotal > 0) ? (int)((dTotal - dIdle) * 100 / dTotal) : 0;
            if (usage < 0) usage = 0;
            if (usage > 100) usage = 100;
        }

        prevCpuTimes["total"] = total;
        prevCpuTimes["idle"] = idle;

        cpuBar->setValue(usage);
        cpuLabel->setText(QString("%1%").arg(usage));
        cpuLabel->setStyleSheet(QString("font-size: 28px; font-weight: bold; color: %1;")
                                .arg(usageColor(usage).name()));

        // Update chart
        cpuSeries->append(QDateTime::currentMSecsSinceEpoch(), usage);
        if (cpuSeries->count() > 60) cpuSeries->removePoints(0, cpuSeries->count() - 60);
    }

    // Memory usage
    QFile memFile("/proc/meminfo");
    if (memFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&memFile);
        double total = 0, available = 0;

        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line.startsWith("MemTotal:")) {
                total = line.split(QRegularExpression("\\s+"))[1].toDouble();
            } else if (line.startsWith("MemAvailable:")) {
                available = line.split(QRegularExpression("\\s+"))[1].toDouble();
            }
        }
        memFile.close();

        if (total > 0) {
            double usedKb = total - available;
            int usage = (int)(usedKb * 100 / total);
            memoryBar->setValue(usage);
            memoryLabel->setText(QString("%1%").arg(usage));
            memoryLabel->setStyleSheet(QString("font-size: 22px; font-weight: bold; color: %1;")
                                       .arg(usageColor(usage).name()));
            memoryBar->setStyleSheet(QString("QProgressBar { background: #333; border-radius: 5px; height: 12px; }"
                                             "QProgressBar::chunk { background-color: %1; border-radius: 5px; }")
                                     .arg(usageColor(usage).name()));
            memDetail->setText(QString("Used: %1 / %2")
                .arg(formatSize(usedKb * 1024))
                .arg(formatSize(total * 1024)));
        }
    }

    // GPU detection (via lspci)
    static bool gpuDetected = false;
    if (!gpuDetected) {
        QProcess proc;
        proc.start("lspci", {});
        proc.waitForFinished(2000);
        QString output = proc.readAllStandardOutput();

        for (const QString &line : output.split('\n')) {
            if (line.contains("VGA") || line.contains("3D") || line.contains("Display")) {
                // Extract device name after ": "
                int idx = line.indexOf(": ");
                if (idx >= 0) {
                    QString name = line.mid(idx + 2).trimmed();
                    gpuInfoLabel->setText(name);
                    gpuDetected = true;
                    break;
                }
            }
        }
        if (!gpuDetected) gpuInfoLabel->setText("GPU not detected");
    }

    // Disk usage
    QStorageInfo storage = QStorageInfo::root();
    if (storage.bytesTotal() > 0) {
        int diskUsage = (int)((storage.bytesTotal() - storage.bytesAvailable()) * 100 / storage.bytesTotal());
        diskBar->setValue(diskUsage);
        diskLabel->setText(QString("%1%").arg(diskUsage));
        diskLabel->setStyleSheet(QString("font-size: 22px; font-weight: bold; color: %1;")
                                 .arg(usageColor(diskUsage).name()));
        diskDetail->setText(QString("Used: %1 / %2")
            .arg(formatSize(storage.bytesTotal() - storage.bytesAvailable()))
            .arg(formatSize(storage.bytesTotal())));
    }

    // Network speed
    QMap<QString, qulonglong> cur;
    QFile netFile("/proc/net/dev");
    if (netFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&netFile);
        in.readLine(); // header
        in.readLine(); // header
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (line.isEmpty()) continue;
            QStringList parts = line.split(QRegularExpression("\\s+"));
            if (parts.size() >= 10) {
                QString iface = parts[0].replace(":", "");
                if (iface == "lo" || iface.startsWith("docker") || iface.startsWith("veth")) continue;
                cur[iface + "_rx"] = parts[1].toULongLong();
                cur[iface + "_tx"] = parts[9].toULongLong();
            }
        }
        netFile.close();
    }

    qulonglong rx = 0, tx = 0;
    QStringList ifaces;
    QString rxName, txName;
    for (auto it = cur.begin(); it != cur.end(); ++it) {
        QString key = it.key();
        if (key.endsWith("_rx")) {
            if (it.value() > rx) { rx = it.value(); rxName = key.left(key.size() - 3); }
        } else if (key.endsWith("_tx")) {
            if (it.value() > tx) { tx = it.value(); txName = key.left(key.size() - 3); }
        }
        QString base = key;
        if (base.endsWith("_rx")) base = base.left(base.size() - 3);
        if (!ifaces.contains(base)) ifaces << base;
    }

    double rxSpeed = 0, txSpeed = 0;
    if (hasPrevNet) {
        qulonglong dRx = (rx > prevNet.rxBytes) ? (rx - prevNet.rxBytes) : 0;
        qulonglong dTx = (tx > prevNet.txBytes) ? (tx - prevNet.txBytes) : 0;
        rxSpeed = dRx / 2.0;
        txSpeed = dTx / 2.0;
    }

    prevNet.rxBytes = rx;
    prevNet.txBytes = tx;
    hasPrevNet = true;

    networkLabel->setText(QString("↓ %1/s  ↑ %2/s\nInterfaces: %3")
        .arg(formatSize(rxSpeed), formatSize(txSpeed), ifaces.join(", ")));

    // Uptime
    QFile uptimeFile("/proc/uptime");
    if (uptimeFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&uptimeFile);
        double uptime = in.readLine().split(" ")[0].toDouble();
        uptimeFile.close();

        int days = (int)(uptime / 86400);
        int hours = ((int)(uptime / 3600)) % 24;
        int minutes = ((int)(uptime / 60)) % 60;
        int seconds = (int)uptime % 60;

        QString up = QString("%1d %2:%3:%4").arg(days).arg(hours, 2, 10, QLatin1Char('0'))
                        .arg(minutes, 2, 10, QLatin1Char('0')).arg(seconds, 2, 10, QLatin1Char('0'));
        uptimeLabel->setText("Uptime: " + up);
    }

    // Hostname
    QFile hostFile("/etc/hostname");
    if (hostFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&hostFile);
        hostnameLabel->setText("Hostname: " + in.readLine().trimmed());
        hostFile.close();
    }

    // Kernel
    QFile osRelease("/etc/os-release");
    if (osRelease.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&osRelease);
        QString osName;
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line.startsWith("PRETTY_NAME=")) {
                osName = line.mid(12).replace("\"", "");
                break;
            }
        }
        osRelease.close();
        if (!osName.isEmpty()) kernelLabel->setText("OS: " + osName);
    }

    // Process count
    QProcess proc;
    proc.start("bash", {"-c", "ps -e --no-headers | wc -l"});
    proc.waitForFinished(2000);
    processLabel->setText("Processes: " + proc.readAllStandardOutput().trimmed());
}
