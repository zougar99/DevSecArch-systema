#ifndef WELCOME_H
#define WELCOME_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class Installer;

class Welcome : public QWidget
{
    Q_OBJECT

public:
    explicit Welcome(Installer *installer, QWidget *parent = nullptr);

private:
    void setupUI();
    Installer *installer;
};

#endif // WELCOME_H
