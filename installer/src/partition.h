#ifndef PARTITION_H
#define PARTITION_H

#include <QWidget>
#include <QListWidget>
#include <QRadioButton>
#include <QLineEdit>

class Installer;

class Partition : public QWidget
{
    Q_OBJECT

public:
    explicit Partition(Installer *installer, QWidget *parent = nullptr);

private:
    void setupUI();
    Installer *installer;
    QListWidget *diskList;
    QRadioButton *autoRadio;
    QRadioButton *manualRadio;
    QRadioButton *swapRadio;
};

#endif // PARTITION_H
