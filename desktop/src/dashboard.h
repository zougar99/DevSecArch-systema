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
#include <QVBoxLayout>

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
    void createQuickActionsCard();

    QLabel *cpuLabel;
    QLabel *memoryLabel;
    QLabel *diskLabel;
    QLabel *networkLabel;
    QLabel *uptimeLabel;
    QLabel *processLabel;

    QProgressBar *cpuBar;
    QProgressBar *memoryBar;
    QProgressBar *diskBar;

    QChartView *cpuChart;
    QLineSeries *cpuSeries;

    QTimer *updateTimer;
};

#endif // DASHBOARD_H
