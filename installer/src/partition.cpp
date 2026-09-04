#include "partition.h"
#include "installer.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QProcess>
#include <QDir>
#include <QMessageBox>
#include <QLineEdit>

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

    QLabel *desc = new QLabel("WARNING: This will ERASE the selected disk completely!");
    desc->setStyleSheet("font-size: 14px; color: #e74c3c; font-weight: bold;");
    layout->addWidget(desc);

    layout->addSpacing(15);

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

    // Dynamic disk detection
    QProcess proc;
    proc.start("lsblk", {"-d", "-n", "-o", "NAME,SIZE,MODEL,TYPE"});
    proc.waitForFinished(3000);
    QString output = proc.readAllStandardOutput();
    
    for (const QString &line : output.split('\n', Qt::SkipEmptyParts)) {
        QStringList parts = line.split(QRegularExpression("\\s+"));
        if (parts.size() >= 2 && parts.last() == "disk") {
            QString info = QString("/dev/%1 - %2").arg(parts[0], parts[1]);
            if (parts.size() >= 3) info += " " + parts[2];
            diskList->addItem(info);
        }
    }

    if (diskList->count() == 0) {
        diskList->addItem("/dev/sda - Unknown");
    }

    diskList->setCurrentRow(0);
    diskLayout->addWidget(diskList);

    connect(diskList, &QListWidget::currentTextChanged, this, [this](const QString &text) {
        installer->disk = text;
    });

    layout->addWidget(diskGroup);

    // Partitioning method
    QGroupBox *partGroup = new QGroupBox("Partitioning Method");
    partGroup->setStyleSheet(
        "QGroupBox { color: white; font-size: 14px; font-weight: bold; "
        "border: 1px solid #333; border-radius: 5px; margin-top: 10px; padding-top: 15px; }"
    );
    QVBoxLayout *partLayout = new QVBoxLayout(partGroup);

    autoRadio = new QRadioButton("Erase entire disk (GPT + EFI + Root)");
    autoRadio->setChecked(true);
    autoRadio->setStyleSheet("color: white; font-size: 14px; padding: 8px;");

    manualRadio = new QRadioButton("Manual partitioning (advanced)");
    manualRadio->setStyleSheet("color: white; font-size: 14px; padding: 8px;");

    swapRadio = new QRadioButton("Erase with swap partition");
    swapRadio->setStyleSheet("color: white; font-size: 14px; padding: 8px;");

    partLayout->addWidget(autoRadio);
    partLayout->addWidget(manualRadio);
    partLayout->addWidget(swapRadio);

    // ERASE confirmation
    QLabel *eraseLabel = new QLabel("Type ERASE to confirm full disk wipe:");
    eraseLabel->setStyleSheet("color: #e74c3c; font-size: 14px; font-weight: bold; padding-top: 15px;");
    partLayout->addWidget(eraseLabel);

    eraseInput = new QLineEdit();
    eraseInput->setPlaceholderText("Type ERASE here...");
    eraseInput->setStyleSheet(
        "QLineEdit { background-color: #0d1117; color: #e74c3c; border: 2px solid #e74c3c; "
        "padding: 10px; border-radius: 5px; font-size: 14px; font-weight: bold; }"
    );
    partLayout->addWidget(eraseInput);

    connect(autoRadio, &QRadioButton::toggled, this, [this](bool checked) {
        if (checked) installer->partitionMode = "auto";
    });
    connect(manualRadio, &QRadioButton::toggled, this, [this](bool checked) {
        if (checked) installer->partitionMode = "manual";
    });
    connect(swapRadio, &QRadioButton::toggled, this, [this](bool checked) {
        if (checked) installer->partitionMode = "swap";
    });
    connect(eraseInput, &QLineEdit::textChanged, this, [this](const QString &text) {
        installer->eraseConfirmed = (text == "ERASE");
    });

    installer->partitionMode = "auto";
    installer->eraseConfirmed = false;

    layout->addWidget(partGroup);
    layout->addStretch();
}
