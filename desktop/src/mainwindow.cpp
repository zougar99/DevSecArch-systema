#include "mainwindow.h"
#include "dashboard.h"
#include "filemanager.h"
#include "texteditor.h"
#include "securitytools.h"
#include "terminal.h"
#include "settings.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QListWidget>
#include <QStackedWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QDateTime>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("DevSecArch Desktop v1.0.0");
    setMinimumSize(1200, 800);
    resize(1400, 900);

    setupUI();
    setupMenuBar();
    setupToolBar();
    setupStatusBar();
    setupTabs();
    setupConnections();

    statusTimer->start(1000);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    tabWidget = new QTabWidget(this);
    tabWidget->setTabPosition(QTabWidget::North);
    tabWidget->setMovable(true);
    tabWidget->setTabsClosable(true);

    mainLayout->addWidget(tabWidget);
}

void MainWindow::setupMenuBar()
{
    QMenu *fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction("&New", this, &MainWindow::newFile, QKeySequence::New);
    fileMenu->addAction("&Open", this, &MainWindow::openFile, QKeySequence::Open);
    fileMenu->addAction("&Save", this, &MainWindow::saveFile, QKeySequence::Save);
    fileMenu->addSeparator();
    fileMenu->addAction("E&xit", qApp, &QApplication::quit, QKeySequence::Quit);

    QMenu *editMenu = menuBar()->addMenu("&Edit");
    editMenu->addAction("&Undo");
    editMenu->addAction("&Redo");
    editMenu->addSeparator();
    editMenu->addAction("Cu&t");
    editMenu->addAction("&Copy");
    editMenu->addAction("&Paste");

    QMenu *viewMenu = menuBar()->addMenu("&View");
    viewMenu->addAction("&Toggle Sidebar", this, &MainWindow::toggleSidebar);
    viewMenu->addAction("&Fullscreen", this, &MainWindow::fullscreen, QKeySequence::FullScreen);

    QMenu *toolsMenu = menuBar()->addMenu("&Tools");
    toolsMenu->addAction("&Settings", this, &MainWindow::settings);

    QMenu *helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction("&About", this, &MainWindow::about);
    helpMenu->addAction("&Documentation");
}

void MainWindow::setupToolBar()
{
    QToolBar *mainToolBar = addToolBar("Main");
    mainToolBar->setMovable(false);
    mainToolBar->setIconSize(QSize(20, 20));

    mainToolBar->addAction("Dashboard");
    mainToolBar->addAction("Files");
    mainToolBar->addAction("Editor");
    mainToolBar->addAction("Security");
    mainToolBar->addAction("Terminal");
}

void MainWindow::setupStatusBar()
{
    statusLabel = new QLabel("Ready");
    clockLabel = new QLabel();

    statusBar()->addPermanentWidget(statusLabel);
    statusBar()->addPermanentWidget(clockLabel);

    statusTimer = new QTimer(this);
}

void MainWindow::setupTabs()
{
    dashboard = new Dashboard(this);
    fileManager = new FileManager(this);
    textEditor = new TextEditor(this);
    securityTools = new SecurityTools(this);
    terminal = new Terminal(this);
    settingsWidget = new Settings(this);

    tabWidget->addTab(dashboard, "Dashboard");
    tabWidget->addTab(fileManager, "Files");
    tabWidget->addTab(textEditor, "Editor");
    tabWidget->addTab(securityTools, "Security");
    tabWidget->addTab(terminal, "Terminal");
}

void MainWindow::setupConnections()
{
    connect(statusTimer, &QTimer::timeout, this, &MainWindow::updateStatus);
}

void MainWindow::newFile()
{
    textEditor->newFile();
    tabWidget->setCurrentWidget(textEditor);
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        "Open File", QDir::homePath(),
        "All Files (*);;Text Files (*.txt);;C++ Files (*.cpp *.h)");

    if (!fileName.isEmpty()) {
        textEditor->openFile(fileName);
        tabWidget->setCurrentWidget(textEditor);
    }
}

void MainWindow::saveFile()
{
    textEditor->saveFile();
}

void MainWindow::about()
{
    QMessageBox::about(this, "About DevSecArch Desktop",
        "<h2>DevSecArch Desktop</h2>"
        "<p>Version 1.0.0</p>"
        "<p>Complete desktop environment for developers and cybersecurity professionals.</p>"
        "<p>License: GPLv3</p>"
        "<p>GitHub: github.com/zougar99/arch-devsec-build</p>"
    );
}

void MainWindow::settings()
{
    tabWidget->addTab(settingsWidget, "Settings");
    tabWidget->setCurrentWidget(settingsWidget);
}

void MainWindow::toggleSidebar()
{
    // TODO: Implement sidebar toggle
}

void MainWindow::fullscreen()
{
    if (isFullScreen()) {
        showNormal();
    } else {
        showFullScreen();
    }
}

void MainWindow::updateStatus()
{
    QString time = QDateTime::currentDateTime().toString("hh:mm:ss");
    clockLabel->setText(time);
}
