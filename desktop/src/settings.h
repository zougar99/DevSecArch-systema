#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QTabWidget>

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private:
    void setupUI();
    void createGeneralTab();
    void createAppearanceTab();
    void createKeyboardTab();

    QTabWidget *settingsTabs;
};

#endif // SETTINGS_H
