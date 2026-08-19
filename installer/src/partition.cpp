#include "partition.h"
#include "installer.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>

Partition::Partition(Installer *inst, QWidget *parent)
    : QWidget(parent)
    , installer(inst)
{
    setupUI();
}

void Partition::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *title = new QLabel("Disk Partitioning");
    title->setStyleSheet("font-size: 20px; font-weight: bold; color: white;");
    layout->addWidget(title);

    QLabel *desc = new QLabel("Select disk and partitioning method:");
    desc->setStyleSheet("font-size: 14px; color: #888;");
    layout->addWidget(desc);

    layout->addSpacing(15);

    // Disk selection
    QGroupBox *diskGroup = new QGroupBox("Select Disk");
    diskGroup->setStyleSheet(
        "QGroupBox { color: white; font-size: 14px; font-weight: bold; "
        "border: 1px solid #333; border-radius: 5px; margin-top: 10px; padding-top: 15px; }"
    );
    QVBoxLayout *diskLayout = new QVBoxLayout(diskGroup);

    diskList = new QListWidget();
    diskList->setStyleSheet(
        "QListWidget { background-color: #0d1117; color: white; border: 1px solid #333; }"
        "QListWidget::item { padding: 10px; }"
        "QListWidget::item:selected { background-color: #2a82da; }"
    );
    diskList->addItem("/dev/sda - 500 GB SSD");
    diskList->addItem("/dev/sdb - 1 TB HDD");
    diskList->setCurrentRow(0);
    diskLayout->addWidget(diskList);

    layout->addWidget(diskGroup);

    // Partitioning method
    QGroupBox *partGroup = new QGroupBox("Partitioning Method");
    partGroup->setStyleSheet(
        "QGroupBox { color: white; font-size: 14px; font-weight: bold; "
        "border: 1px solid #333; border-radius: 5px; margin-top: 10px; padding-top: 15px; }"
    );
    QVBoxLayout *partLayout = new QVBoxLayout(partGroup);

    autoRadio = new QRadioButton("Auto-partition (use entire disk)");
    autoRadio->setChecked(true);
    autoRadio->setStyleSheet("color: white; font-size: 14px; padding: 8px;");

    manualRadio = new QRadioButton("Manual partitioning");
    manualRadio->setStyleSheet("color: white; font-size: 14px; padding: 8px;");

    swapRadio = new QRadioButton("Auto-partition with swap");
    swapRadio->setStyleSheet("color: white; font-size: 14px; padding: 8px;");

    partLayout->addWidget(autoRadio);
    partLayout->addWidget(manualRadio);
    partLayout->addWidget(swapRadio);

    layout->addWidget(partGroup);
    layout->addStretch();
}
