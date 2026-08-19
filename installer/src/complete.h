#ifndef COMPLETE_H
#define COMPLETE_H

#include <QWidget>
#include <QPushButton>

class Installer;

class Complete : public QWidget
{
    Q_OBJECT

public:
    explicit Complete(Installer *installer, QWidget *parent = nullptr);

private:
    void setupUI();
    Installer *installer;
};

#endif // COMPLETE_H
