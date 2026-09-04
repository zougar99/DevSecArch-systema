#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QTimer>
#include <QChartView>
#include <QLineSeries>
#include <QStorageInfo>
#include <QColor>
#include <QString>

struct NetStats {
    qulonglong rxBytes;
    qulonglong txBytes;
};

class Dashboard : public QWidget
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();

private slots:
    void updateStats();

private:
    void setupUI();
    void createSystemInfoCard();
    void createCPUCard();
    void createMemoryCard();
    void createDiskCard();
    void createNetworkCard();
    void createGPUCard();
    void createQuickActionsCard();

    QString formatSize(double bytes);
    QColor usageColor(int percent);

    QLabel *cpuLabel;
    QLabel *memoryLabel;
    QLabel *diskLabel;
    QLabel *networkLabel;
    QLabel *gpuInfoLabel;
    QLabel *hostnameLabel;
    QLabel *kernelLabel;
    QLabel *uptimeLabel;
    QLabel *processLabel;

    QProgressBar *cpuBar;
    QProgressBar *memoryBar;
    QProgressBar *diskBar;

    QChartView *cpuChart;
    QLineSeries *cpuSeries;

    QLabel *memDetail;
    QLabel *diskDetail;

    QTimer *updateTimer;

    NetStats prevNet;
    bool hasPrevNet;
};

#endif // DASHBOARD_H
