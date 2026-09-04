#include "keyboard.h"
#include "installer.h"
#include <QVBoxLayout>
#include <QLabel>

Keyboard::Keyboard(Installer *inst, QWidget *parent)
    : QWidget(parent)
    , installer(inst)
{
    setupUI();
}

void Keyboard::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *title = new QLabel("Select Keyboard Layout");
    title->setStyleSheet("font-size: 20px; font-weight: bold; color: white;");
    layout->addWidget(title);

    QLabel *desc = new QLabel("Choose your keyboard layout:");
    desc->setStyleSheet("font-size: 14px; color: #888;");
    layout->addWidget(desc);

    layout->addSpacing(20);

    keyboardList = new QListWidget();
    keyboardList->setStyleSheet(
        "QListWidget { background-color: #16213e; color: white; border: 1px solid #333; "
        "font-size: 14px; }"
        "QListWidget::item { padding: 12px; }"
        "QListWidget::item:selected { background-color: #2a82da; }"
        "QListWidget::item:hover { background-color: #1e3a5f; }"
    );

    QStringList keyboards = {
        "English (US)", "English (UK)", "Arabic", "French",
        "German", "Spanish", "Portuguese", "Russian",
        "Japanese", "Korean", "Italian", "Dutch",
        "Turkish", "Hindi", "Polish", "Swedish"
    };
    keyboardList->addItems(keyboards);
    keyboardList->setCurrentRow(0);

    connect(keyboardList, &QListWidget::currentTextChanged, this, [this](const QString &text) {
        installer->keyboard = text;
    });

    installer->keyboard = "English (US)";

    layout->addWidget(keyboardList);
}
