#ifndef INSTALLER_H
#define INSTALLER_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QLabel>
#include <QFrame>

class Welcome;
class Language;
class Keyboard;
class Partition;
class UserInfo;
class Desktop;
class Summary;
class Installing;
class Complete;

class Installer : public QMainWindow
{
    Q_OBJECT

public:
    Installer(QWidget *parent = nullptr);
    ~Installer();

    void nextStep();
    void prevStep();
    void goToStep(int step);

    // Data
    QString language;
    QString keyboard;
    QString disk;
    QString partitionMode;
    QString hostname;
    QString username;
    QString password;
    QString rootPassword;
    QString desktop;
    QString timezone;

private:
    void setupUI();
    void updateButtons();

    QStackedWidget *stack;
    QPushButton *backBtn;
    QPushButton *nextBtn;
    QPushButton *cancelBtn;
    QLabel *stepLabel;
    QLabel *titleLabel;

    Welcome *welcomePage;
    Language *languagePage;
    Keyboard *keyboardPage;
    Partition *partitionPage;
    UserInfo *userinfoPage;
    Desktop *desktopPage;
    Summary *summaryPage;
    Installing *installingPage;
    Complete *completePage;

    int currentStep;
    int totalSteps;
};

#endif // INSTALLER_H
