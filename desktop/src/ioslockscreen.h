#ifndef IOSLOCKSCREEN_H
#define IOSLOCKSCREEN_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QTimer>
#include <QPushButton>

class IOSLockScreen : public QWidget
{
    Q_OBJECT

public:
    explicit IOSLockScreen(QWidget *parent = nullptr);

signals:
    void unlocked();

private slots:
    void updateClock();
    void tryUnlock();
    void showUI();

private:
    void setupUI();

    QLabel *clockLabel;
    QLabel *dateLabel;
    QLineEdit *passEdit;
    QLabel *hintLabel;
    QVBoxLayout *mainLayout;
    QWidget *content;
    QTimer *clockTimer;
};

#endif // IOSLOCKSCREEN_H
