#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QTimer>
#include <QSystemTrayIcon>

class Dashboard;
class FileManager;
class TextEditor;
class SecurityTools;
class Terminal;
class Settings;
class ForxoStore;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void about();
    void settings();
    void toggleSidebar();
    void fullscreen();
    void updateStatus();

private:
    void setupUI();
    void setupMenuBar();
    void setupToolBar();
    void setupStatusBar();
    void setupTabs();
    void setupConnections();

    QTabWidget *tabWidget;
    Dashboard *dashboard;
    FileManager *fileManager;
    TextEditor *textEditor;
    SecurityTools *securityTools;
    Terminal *terminal;
    Settings *settingsWidget;
    ForxoStore *store;

    QLabel *statusLabel;
    QLabel *clockLabel;
    QTimer *statusTimer;

    QSystemTrayIcon *trayIcon;
};

#endif // MAINWINDOW_H
