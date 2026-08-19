#include "welcome.h"
#include "installer.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

Welcome::Welcome(Installer *inst, QWidget *parent)
    : QWidget(parent)
    , installer(inst)
{
    setupUI();
}

void Welcome::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);

    QLabel *icon = new QLabel(" Arch Linux ");
    icon->setStyleSheet(
        "font-size: 48px; font-weight: bold; color: #2a82da; "
        "background-color: #16213e; padding: 30px; border-radius: 15px;"
    );
    icon->setAlignment(Qt::AlignCenter);

    QLabel *title = new QLabel("Welcome to Arch Linux Installer");
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: white;");
    title->setAlignment(Qt::AlignCenter);

    QLabel *desc = new QLabel(
        "This installer will guide you through the installation process.\n"
        "You will be able to configure your system step by step."
    );
    desc->setStyleSheet("font-size: 14px; color: #aaa; line-height: 1.5;");
    desc->setAlignment(Qt::AlignCenter);

    QLabel *warning = new QLabel(
        "WARNING: This will erase all data on the selected disk!"
    );
    warning->setStyleSheet(
        "font-size: 14px; color: #e74c3c; font-weight: bold; "
        "background-color: #2d1215; padding: 15px; border-radius: 5px;"
    );
    warning->setAlignment(Qt::AlignCenter);

    layout->addStretch();
    layout->addWidget(icon);
    layout->addSpacing(30);
    layout->addWidget(title);
    layout->addSpacing(15);
    layout->addWidget(desc);
    layout->addSpacing(30);
    layout->addWidget(warning);
    layout->addStretch();
}
