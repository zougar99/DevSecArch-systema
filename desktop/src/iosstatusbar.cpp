#include "iosstatusbar.h"
#include <QHBoxLayout>
#include <QDateTime>

IOSStatusBar::IOSStatusBar(QWidget *parent)
    : QWidget(parent)
{
    setFixedHeight(32);
    setStyleSheet(
        "IOSStatusBar { background-color: rgba(20,20,25,90%); border-bottom: 1px solid #333; }"
    );

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(16, 4, 16, 4);

    timeLabel = new QLabel();
    timeLabel->setStyleSheet("color: white; font-size: 13px; font-weight: bold;");

    // Right side: signal + wifi + battery
    rightLabel = new QLabel("📶   WiFi   🔋 100%");
    rightLabel->setStyleSheet("color: white; font-size: 13px; font-weight: bold;");

    layout->addWidget(timeLabel);
    layout->addStretch();
    layout->addWidget(rightLabel);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &IOSStatusBar::updateTime);
    timer->start(1000);
    updateTime();
}

void IOSStatusBar::updateTime()
{
    QString t = QDateTime::currentDateTime().toString("HH:mm");
    timeLabel->setText(t);
}
