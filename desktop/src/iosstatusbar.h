#ifndef IOSSTATUSBAR_H
#define IOSSTATUSBAR_H

#include <QWidget>
#include <QLabel>
#include <QTimer>

class IOSStatusBar : public QWidget
{
    Q_OBJECT

public:
    explicit IOSStatusBar(QWidget *parent = nullptr);

private slots:
    void updateTime();

private:
    QLabel *timeLabel;
    QLabel *rightLabel;
    QTimer *timer;
};

#endif // IOSSTATUSBAR_H
