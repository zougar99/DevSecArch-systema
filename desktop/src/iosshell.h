#ifndef IOSSHELL_H
#define IOSSHELL_H

#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTimer>

class IOSStatusBar;
class IOSHome;
class IOSDock;
class IOSControlCenter;
class IOSLockScreen;
class IOSSettings;
class FileManager;
class TextEditor;
class Terminal;
class ForxoStore;
class Dashboard;

class IOSShell : public QWidget
{
    Q_OBJECT

public:
    explicit IOSShell(QWidget *parent = nullptr);

private slots:
    void handleAppRequest(const QString &name);
    void onUnlocked();
    void toggleControlCenter();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void setupUI();
    void setupLockScreen();

    // Lock screen (full-screen overlay)
    IOSLockScreen *lockScreen;
    bool unlocked;

    // Main shell
    QVBoxLayout *mainLayout;
    IOSStatusBar *statusBar;
    QStackedWidget *contentStack;
    IOSHome *home;
    IOSDock *dock;
    IOSControlCenter *controlCenter;

    // Apps
    Dashboard *dashboard;
    FileManager *fileManager;
    TextEditor *textEditor;
    Terminal *terminal;
    ForxoStore *store;
    IOSSettings *settings;

    QPushButton *ccToggleBtn;
};

#endif // IOSSHELL_H
