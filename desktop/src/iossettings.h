#ifndef IOSSETTINGS_H
#define IOSSETTINGS_H

#include <QWidget>
#include <QListWidget>
#include <QStackedWidget>

class IOSSettings : public QWidget
{
    Q_OBJECT

public:
    explicit IOSSettings(QWidget *parent = nullptr);

private:
    void setupUI();
    QWidget *createGeneralPage();
    QWidget *createAboutPage();
    QWidget *createDisplayPage();

    QListWidget *menu;
    QStackedWidget *stack;
};

#endif // IOSSETTINGS_H
