#include "ioslockscreen.h"
#include <QDateTime>
#include <QKeyEvent>

IOSLockScreen::IOSLockScreen(QWidget *parent)
    : QWidget(parent)
{
    setupUI();

    clockTimer = new QTimer(this);
    connect(clockTimer, &QTimer::timeout, this, &IOSLockScreen::updateClock);
    clockTimer->start(1000);
    updateClock();

    // Fake unlock UI: press button or type password to unlock
    showUI();
}

void IOSLockScreen::setupUI()
{
    // Background = deep gradient (simulated with dark blue)
    setStyleSheet("IOSLockScreen { background: qlineargradient(x1:0,y1:0,x2:0,y2:1, "
                  "stop:0 #0f2027, stop:0.5 #203a43, stop:1 #2c5364); }");

    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    content = new QWidget(this);
    mainLayout->addWidget(content);

    QVBoxLayout *layout = new QVBoxLayout(content);
    layout->setSpacing(12);
    layout->setAlignment(Qt::AlignCenter);

    clockLabel = new QLabel("00:00");
    clockLabel->setStyleSheet("color: white; font-size: 64px; font-weight: 200;");
    clockLabel->setAlignment(Qt::AlignCenter);

    dateLabel = new QLabel("---, ---");
    dateLabel->setStyleSheet("color: rgba(255,255,255,180%); font-size: 18px;");
    dateLabel->setAlignment(Qt::AlignCenter);

    hintLabel = new QLabel("ForxoOS iOS");
    hintLabel->setStyleSheet("color: rgba(255,255,255,120%); font-size: 14px; margin-top: 40px;");
    hintLabel->setAlignment(Qt::AlignCenter);

    passEdit = new QLineEdit();
    passEdit->setPlaceholderText("password or click unlock");
    passEdit->setEchoMode(QLineEdit::Password);
    passEdit->setAlignment(Qt::AlignCenter);
    passEdit->setMaximumWidth(260);
    passEdit->setStyleSheet(
        "QLineEdit { background: rgba(255,255,255,15%); color: white; border: 1px solid "
        "rgba(255,255,255,30%); border-radius: 18px; padding: 10px; font-size: 14px; }"
        "QLineEdit:focus { border: 1px solid #4fc3f7; }"
    );

    connect(passEdit, &QLineEdit::returnPressed, this, &IOSLockScreen::tryUnlock);

    QPushButton *unlockBtn = new QPushButton("Unlock");
    unlockBtn->setMaximumWidth(260);
    unlockBtn->setStyleSheet(
        "QPushButton { background: rgba(79,195,247,60%); color: white; border: none; "
        "border-radius: 18px; padding: 10px; font-size: 14px; font-weight: bold; }"
        "QPushButton:hover { background: rgba(79,195,247,80%); }"
    );
    connect(unlockBtn, &QPushButton::clicked, this, &IOSLockScreen::tryUnlock);

    layout->addStretch();
    layout->addWidget(clockLabel);
    layout->addWidget(dateLabel);
    layout->addWidget(hintLabel);
    layout->addWidget(passEdit, 0, Qt::AlignHCenter);
    layout->addWidget(unlockBtn, 0, Qt::AlignHCenter);
    layout->addStretch();
}

void IOSLockScreen::showUI()
{
    content->show();
}

void IOSLockScreen::updateClock()
{
    QString t = QDateTime::currentDateTime().toString("HH:mm");
    clockLabel->setText(t);
    QString d = QDateTime::currentDateTime().toString("dddd, MMMM d");
    dateLabel->setText(d);
}

void IOSLockScreen::tryUnlock()
{
    // In live ISO auto-login, any unlock works (or no password).
    // For demo purposes, unlock on any input.
    passEdit->setText("");
    emit unlocked();
}
