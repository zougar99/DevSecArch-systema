#include "settings.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QPushButton>

Settings::Settings(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
}

Settings::~Settings()
{
}

void Settings::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *title = new QLabel("Settings");
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: #2a82da;");
    mainLayout->addWidget(title);

    settingsTabs = new QTabWidget();
    createGeneralTab();
    createAppearanceTab();
    createKeyboardTab();

    mainLayout->addWidget(settingsTabs);
}

void Settings::createGeneralTab()
{
    QWidget *tab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(tab);

    QGroupBox *generalGroup = new QGroupBox("General Settings");
    QVBoxLayout *groupLayout = new QVBoxLayout(generalGroup);

    QCheckBox *autoSave = new QCheckBox("Auto-save files");
    autoSave->setChecked(true);
    groupLayout->addWidget(autoSave);

    QCheckBox *showLineNumbers = new QCheckBox("Show line numbers");
    showLineNumbers->setChecked(true);
    groupLayout->addWidget(showLineNumbers);

    QCheckBox *wordWrap = new QCheckBox("Word wrap");
    groupLayout->addWidget(wordWrap);

    layout->addWidget(generalGroup);
    layout->addStretch();

    settingsTabs->addTab(tab, "General");
}

void Settings::createAppearanceTab()
{
    QWidget *tab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(tab);

    QGroupBox *themeGroup = new QGroupBox("Theme");
    QVBoxLayout *themeLayout = new QVBoxLayout(themeGroup);

    QHBoxLayout *themeRow = new QHBoxLayout();
    QLabel *themeLabel = new QLabel("Color Theme:");
    QComboBox *themeCombo = new QComboBox();
    themeCombo->addItems({"Dark", "Light", "System", "Monokai", "Dracula", "Nord"});
    themeRow->addWidget(themeLabel);
    themeRow->addWidget(themeCombo);
    themeLayout->addLayout(themeRow);

    QHBoxLayout *fontRow = new QHBoxLayout();
    QLabel *fontLabel = new QLabel("Font Size:");
    QComboBox *fontCombo = new QComboBox();
    fontCombo->addItems({"10", "12", "14", "16", "18", "20"});
    fontCombo->setCurrentText("14");
    fontRow->addWidget(fontLabel);
    fontRow->addWidget(fontCombo);
    themeLayout->addLayout(fontRow);

    layout->addWidget(themeGroup);
    layout->addStretch();

    settingsTabs->addTab(tab, "Appearance");
}

void Settings::createKeyboardTab()
{
    QWidget *tab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(tab);

    QLabel *title = new QLabel("Keyboard Shortcuts");
    title->setStyleSheet("font-size: 16px; font-weight: bold;");
    layout->addWidget(title);

    // Shortcuts list
    QGridLayout *shortcuts = new QGridLayout();

    QStringList keys = {
        "Ctrl+N", "New File",
        "Ctrl+O", "Open File",
        "Ctrl+S", "Save File",
        "Ctrl+Z", "Undo",
        "Ctrl+Y", "Redo",
        "Ctrl+F", "Find",
        "Ctrl+H", "Replace",
        "F11", "Fullscreen",
        "Ctrl+Q", "Quit"
    };

    for (int i = 0; i < keys.size(); i += 2) {
        QLabel *keyLabel = new QLabel(keys[i]);
        keyLabel->setStyleSheet("font-family: monospace; background-color: #353535; padding: 5px; border-radius: 3px;");
        QLabel *descLabel = new QLabel(keys[i + 1]);
        shortcuts->addWidget(keyLabel, i / 2, 0);
        shortcuts->addWidget(descLabel, i / 2, 1);
    }

    layout->addLayout(shortcuts);
    layout->addStretch();

    settingsTabs->addTab(tab, "Keyboard");
}
