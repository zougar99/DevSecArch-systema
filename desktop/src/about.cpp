#include "about.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

About::About(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
}

About::~About()
{
}

void About::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);

    QLabel *title = new QLabel("DevSecArch Desktop");
    title->setStyleSheet("font-size: 28px; font-weight: bold; color: #2a82da;");
    title->setAlignment(Qt::AlignCenter);

    QLabel *version = new QLabel("Version 1.0.0");
    version->setStyleSheet("font-size: 16px; color: #888;");
    version->setAlignment(Qt::AlignCenter);

    QLabel *description = new QLabel(
        "Complete desktop environment for developers and cybersecurity professionals.\n"
        "Built with Qt 6 and designed for Arch Linux."
    );
    description->setStyleSheet("font-size: 14px; color: #aaa;");
    description->setAlignment(Qt::AlignCenter);

    QLabel *license = new QLabel("License: GPLv3");
    license->setStyleSheet("font-size: 12px; color: #666;");
    license->setAlignment(Qt::AlignCenter);

    QPushButton *githubBtn = new QPushButton("GitHub");
    githubBtn->setStyleSheet(
        "QPushButton { background-color: #2a82da; color: white; border: none; "
        "padding: 10px 30px; border-radius: 5px; font-size: 14px; }"
        "QPushButton:hover { background-color: #3a92ea; }"
    );

    layout->addWidget(title);
    layout->addWidget(version);
    layout->addSpacing(20);
    layout->addWidget(description);
    layout->addSpacing(10);
    layout->addWidget(license);
    layout->addSpacing(20);
    layout->addWidget(githubBtn, 0, Qt::AlignCenter);
    layout->addStretch();
}
