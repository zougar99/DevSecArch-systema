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
        "English (US)", "English (UK)", "Arabic", "French",
        "Spanish", "German", "Portuguese", "Russian",
        "Chinese", "Japanese", "Korean",
        "Italian", "Dutch", "Turkish", "Hindi", "Polish"
    };
    languageList->addItems(languages);
    languageList->setCurrentRow(0);

    connect(languageList, &QListWidget::currentTextChanged, this, [this](const QString &text) {
        installer->language = text;
        
        // Map language to locale
        if (text.contains("English (US)")) installer->locale = "en_US.UTF-8";
        else if (text.contains("English (UK)")) installer->locale = "en_GB.UTF-8";
        else if (text.contains("Arabic")) installer->locale = "ar_MA.UTF-8";
        else if (text.contains("French")) installer->locale = "fr_FR.UTF-8";
        else if (text.contains("Spanish")) installer->locale = "es_ES.UTF-8";
        else if (text.contains("German")) installer->locale = "de_DE.UTF-8";
        else if (text.contains("Portuguese")) installer->locale = "pt_PT.UTF-8";
        else if (text.contains("Russian")) installer->locale = "ru_RU.UTF-8";
        else if (text.contains("Chinese")) installer->locale = "zh_CN.UTF-8";
        else if (text.contains("Japanese")) installer->locale = "ja_JP.UTF-8";
        else if (text.contains("Korean")) installer->locale = "ko_KR.UTF-8";
        else if (text.contains("Italian")) installer->locale = "it_IT.UTF-8";
        else if (text.contains("Dutch")) installer->locale = "nl_NL.UTF-8";
        else if (text.contains("Turkish")) installer->locale = "tr_TR.UTF-8";
        else if (text.contains("Hindi")) installer->locale = "hi_IN.UTF-8";
        else if (text.contains("Polish")) installer->locale = "pl_PL.UTF-8";
        else installer->locale = "en_US.UTF-8";
    });

    installer->language = "English (US)";
    installer->locale = "en_US.UTF-8";

    layout->addWidget(languageList);
}
