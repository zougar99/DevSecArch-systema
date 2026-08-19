#include "language.h"
#include "installer.h"
#include <QVBoxLayout>
#include <QLabel>

Language::Language(Installer *inst, QWidget *parent)
    : QWidget(parent)
    , installer(inst)
{
    setupUI();
}

void Language::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *title = new QLabel("Select Language");
    title->setStyleSheet("font-size: 20px; font-weight: bold; color: white;");
    layout->addWidget(title);

    QLabel *desc = new QLabel("Choose your preferred language:");
    desc->setStyleSheet("font-size: 14px; color: #888;");
    layout->addWidget(desc);

    layout->addSpacing(20);

    languageList = new QListWidget();
    languageList->setStyleSheet(
        "QListWidget { background-color: #16213e; color: white; border: 1px solid #333; "
        "font-size: 14px; }"
        "QListWidget::item { padding: 12px; }"
        "QListWidget::item:selected { background-color: #2a82da; }"
        "QListWidget::item:hover { background-color: #1e3a5f; }"
    );

    QStringList languages = {
        "English", "Arabic", "French", "Spanish", "German",
        "Portuguese", "Russian", "Chinese", "Japanese", "Korean",
        "Italian", "Dutch", "Turkish", "Hindi", "Polish"
    };
    languageList->addItems(languages);
    languageList->setCurrentRow(0);

    layout->addWidget(languageList);
}
