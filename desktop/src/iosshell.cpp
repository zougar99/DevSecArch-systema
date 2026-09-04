#include "iosshell.h"
#include "iosstatusbar.h"
#include "ioshome.h"
#include "iosdock.h"
#include "ioscontrolcenter.h"
#include "ioslockscreen.h"
#include "iossettings.h"
#include "dashboard.h"
#include "filemanager.h"
#include "texteditor.h"
#include "terminal.h"
#include "forxostore.h"

#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include <QStackedLayout>
#include <QResizeEvent>

IOSShell::IOSShell(QWidget *parent)
    : QWidget(parent)
    , unlocked(false)
{
    setupUI();
    setupLockScreen();
}

void IOSShell::setupUI()
{
    setStyleSheet("IOSShell { background-color: #0B1020; }");

    // Home icon button for control center access (top-right of status bar area)
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Status bar with a CC toggle button embedded
    QWidget *topBar = new QWidget();
    topBar->setStyleSheet("background: rgba(20,20,25,90%);");
    QHBoxLayout *topLayout = new QHBoxLayout(topBar);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->setSpacing(0);

    statusBar = new IOSStatusBar();

    ccToggleBtn = new QPushButton("⌄");
    ccToggleBtn->setFixedSize(32, 32);
    ccToggleBtn->setCursor(Qt::PointingHandCursor);
    ccToggleBtn->setStyleSheet(
        "QPushButton { background: rgba(255,255,255,15%); color: white; border: none; "
        "border-radius: 16px; font-size: 16px; }"
        "QPushButton:hover { background: rgba(255,255,255,30%); }"
    );
    connect(ccToggleBtn, &QPushButton::clicked, this, &IOSShell::toggleControlCenter);

    topLayout->addWidget(statusBar, 1);
    topLayout->addWidget(ccToggleBtn);
    topLayout->addSpacing(8);

    mainLayout->addWidget(topBar);

    // Content area (home + apps)
    contentStack = new QStackedWidget();

    home = new IOSHome();
    connect(home, &IOSHome::appRequested, this, &IOSShell::handleAppRequest);

    dashboard = new Dashboard();
    fileManager = new FileManager();
    textEditor = new TextEditor();
    terminal = new Terminal();
    store = new ForxoStore();
    settings = new IOSSettings();

    contentStack->addWidget(home);        // 0 - home
    contentStack->addWidget(dashboard);   // 1
    contentStack->addWidget(fileManager); // 2
    contentStack->addWidget(textEditor);  // 3
    contentStack->addWidget(terminal);    // 4
    contentStack->addWidget(store);       // 5
    contentStack->addWidget(settings);    // 6

    mainLayout->addWidget(contentStack, 1);

    // Dock (iOS style, bottom)
    dock = new IOSDock();
    connect(dock, &IOSDock::appRequested, this, &IOSShell::handleAppRequest);
    connect(dock, &IOSDock::homeRequested, this, [this]() { contentStack->setCurrentIndex(0); });
    mainLayout->addWidget(dock);

    // Control Center - positioned top-right, hidden by default
    controlCenter = new IOSControlCenter(this);
    controlCenter->setVisible(false);
}

void IOSShell::setupLockScreen()
{
    lockScreen = new IOSLockScreen(this);
    connect(lockScreen, &IOSLockScreen::unlocked, this, &IOSShell::onUnlocked);
    lockScreen->setGeometry(rect());
    lockScreen->raise();
    lockScreen->show();
}

void IOSShell::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    if (lockScreen) {
        lockScreen->setGeometry(rect());
    }
    if (controlCenter->isVisible()) {
        controlCenter->move(width() - controlCenter->width() - 20, statusBar->height() + 20);
    }
}

void IOSShell::onUnlocked()
{
    unlocked = true;
    if (lockScreen) {
        lockScreen->hide();
        lockScreen->deleteLater();
        lockScreen = nullptr;
    }
}

void IOSShell::handleAppRequest(const QString &name)
{
    // Map app names to stack indices
    if (name == "Files") contentStack->setCurrentIndex(2);
    else if (name == "Browser") {} // TODO: browser
    else if (name == "Editor") contentStack->setCurrentIndex(3);
    else if (name == "Terminal") contentStack->setCurrentIndex(4);
    else if (name == "Store" || name == "Forxo Store") contentStack->setCurrentIndex(5);
    else if (name == "Security") {} // TODO kill this feature
    else if (name == "Settings") contentStack->setCurrentIndex(6);
    else if (name == "About") {} // TODO
    else contentStack->setCurrentIndex(0);

    // Add a "Home" way back - the dock shows apps but not home.
    // Simple: show home via Settings->??? Actually let's allow escape:
    // We'll keep it simple: clicking an already-open app returns home? No.
    // Provide a small home button floating on the dock? For now, return home
    // is not wired; instead we just switch. That's acceptable.
}

void IOSShell::toggleControlCenter()
{
    controlCenter->setVisible(!controlCenter->isVisible());
    if (controlCenter->isVisible()) {
        controlCenter->raise();
        controlCenter->move(width() - controlCenter->width() - 20, statusBar->height() + 20);
    }
}
