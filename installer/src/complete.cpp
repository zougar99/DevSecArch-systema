#include "complete.h"
#include "installer.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

Complete::Complete(Installer *inst, QWidget *parent)
    : QWidget(parent)
    , installer(inst)
{
    setupUI();
}

void Complete::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);

    QLabel *icon = new QLabel(" Installation Complete! ");
    icon->setStyleSheet(
        "font-size: 48px; font-weight: bold; color: #28a745; "
        "background-color: #1a3d1f; padding: 30px; border-radius: 15px;"
    );
    icon->setAlignment(Qt::AlignCenter);

    layout->addStretch();
    layout->addWidget(icon);
    layout->addSpacing(30);

    QLabel *title = new QLabel("Arch Linux has been installed successfully!");
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: white;");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    layout->addSpacing(20);

    QLabel *desc = new QLabel(
        "Your system is ready to use.\n"
        "Please remove the installation media and reboot."
    );
    desc->setStyleSheet("font-size: 16px; color: #aaa;");
    desc->setAlignment(Qt::AlignCenter);
    layout->addWidget(desc);

    layout->addSpacing(30);

    QLabel *info = new QLabel(
        "Username: " + (installer->username.isEmpty() ? "user" : installer->username) + "\n"
        "Desktop: " + (installer->desktop.isEmpty() ? "GNOME" : installer->desktop)
    );
    info->setStyleSheet(
        "font-size: 14px; color: #2a82da; background-color: #16213e; "
        "padding: 15px; border-radius: 5px;"
    );
    info->setAlignment(Qt::AlignCenter);
    layout->addWidget(info);

    layout->addStretch();
}
