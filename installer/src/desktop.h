#ifndef DESKTOP_H
#define DESKTOP_H

#include <QWidget>
#include <QRadioButton>
#include <QButtonGroup>

class Installer;

class Desktop : public QWidget
{
    Q_OBJECT

public:
    explicit Desktop(Installer *installer, QWidget *parent = nullptr);

private:
    void setupUI();
    Installer *installer;
    QButtonGroup *desktopGroup;
};

#endif // DESKTOP_H
