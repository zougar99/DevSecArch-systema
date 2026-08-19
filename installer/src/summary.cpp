#include "summary.h"
#include "installer.h"
#include <QVBoxLayout>
#include <QLabel>

Summary::Summary(Installer *inst, QWidget *parent)
    : QWidget(parent)
    , installer(inst)
{
    setupUI();
}

void Summary::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *title = new QLabel("Installation Summary");
    title->setStyleSheet("font-size: 20px; font-weight: bold; color: white;");
    layout->addWidget(title);

    QLabel *desc = new QLabel("Review your settings before installation:");
    desc->setStyleSheet("font-size: 14px; color: #888;");
    layout->addWidget(desc);

    layout->addSpacing(20);

    summaryText = new QTextEdit();
    summaryText->setReadOnly(true);
    summaryText->setStyleSheet(
        "QTextEdit { background-color: #16213e; color: white; border: 1px solid #333; "
        "font-size: 14px; padding: 15px; }"
    );

    QString summary = QString(
        "<h2 style='color: #2a82da;'>Installation Configuration</h2>"
        "<hr style='border-color: #333;'>"
        "<p><b style='color: #2a82da;'>Language:</b> %1</p>"
        "<p><b style='color: #2a82da;'>Keyboard:</b> %2</p>"
        "<p><b style='color: #2a82da;'>Disk:</b> %3</p>"
        "<p><b style='color: #2a82da;'>Partitioning:</b> Auto-partition</p>"
        "<p><b style='color: #2a82da;'>Hostname:</b> %4</p>"
        "<p><b style='color: #2a82da;'>Username:</b> %5</p>"
        "<p><b style='color: #2a82da;'>Desktop:</b> %6</p>"
        "<hr style='border-color: #333;'>"
        "<p style='color: #e74c3c; font-weight: bold;'>"
        "WARNING: This will erase all data on the selected disk!</p>"
    ).arg(installer->language.isEmpty() ? "English" : installer->language)
     .arg(installer->keyboard.isEmpty() ? "English (US)" : installer->keyboard)
     .arg(installer->disk.isEmpty() ? "/dev/sda" : installer->disk)
     .arg(installer->hostname.isEmpty() ? "archlinux" : installer->hostname)
     .arg(installer->username.isEmpty() ? "user" : installer->username)
     .arg(installer->desktop.isEmpty() ? "GNOME" : installer->desktop);

    summaryText->setHtml(summary);
    layout->addWidget(summaryText);
}
