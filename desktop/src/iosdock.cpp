#include "iosdock.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QSignalMapper>

IOSDock::IOSDock(QWidget *parent)
    : QWidget(parent)
{
    setFixedHeight(96);
    setStyleSheet("IOSDock { background: transparent; }");

    dockContainer = new QWidget(this);
    dockContainer->setStyleSheet(
        "QWidget { background-color: rgba(18,24,43,72%); "
        "border-radius: 22px; border: 1px solid rgba(255,255,255,15%); }"
    );

    QVBoxLayout *outer = new QVBoxLayout(this);
    outer->setContentsMargins(20, 10, 20, 10);
    outer->addWidget(dockContainer);

    dockLayout = new QHBoxLayout(dockContainer);
    dockLayout->setContentsMargins(18, 12, 18, 12);
    dockLayout->setSpacing(14);
    dockLayout->addStretch();

    // Home button (iOS home indicator -> return to home screen)
    QPushButton *homeBtn = new QPushButton("🏠");
    homeBtn->setFixedSize(40, 40);
    homeBtn->setCursor(Qt::PointingHandCursor);
    homeBtn->setStyleSheet(
        "QPushButton { background: rgba(255,255,255,15%); border: none; border-radius: 20px; "
        "font-size: 16px; }"
        "QPushButton:hover { background: rgba(255,255,255,30%); }"
    );
    homeBtn->setToolTip("Home");
    connect(homeBtn, &QPushButton::clicked, this, &IOSDock::homeRequested);
    dockLayout->insertWidget(0, homeBtn);

    // iOS-style dock apps
    addApp(0, "Files",      "📁",  "#0277bd");
    addApp(1, "Browser",    "🌐",  "#1565c0");
    addApp(2, "Editor",     "✏️",  "#2e7d32");
    addApp(3, "Terminal",   "⌨️",  "#424242");
    addApp(4, "Store",      "🛒",  "#00838f");
    addApp(5, "Security",   "🛡️",  "#b71c1c");

    dockLayout->addStretch();
}

void IOSDock::addApp(int index, const QString &name, const QString &icon, const QString &color)
{
    QWidget *app = new QWidget(dockContainer);
    app->setFixedSize(62, 70);
    app->setCursor(Qt::PointingHandCursor);

    QVBoxLayout *v = new QVBoxLayout(app);
    v->setContentsMargins(0, 0, 0, 0);
    v->setSpacing(4);

    QPushButton *iconBtn = new QPushButton(icon);
    iconBtn->setFixedSize(54, 54);
    iconBtn->setStyleSheet(QString(
        "QPushButton { background-color: %1; color: white; border: none; "
        "border-radius: 14px; font-size: 24px; }"
        "QPushButton:hover { background-color: %2; }"
    ).arg(color, color));
    iconBtn->setToolTip(name);
    iconBtn->setCursor(Qt::PointingHandCursor);

    connect(iconBtn, &QPushButton::clicked, this, [this, name]() {
        emit appRequested(name);
    });

    v->addWidget(iconBtn, 0, Qt::AlignHCenter);

    QLabel *label = new QLabel(name);
    label->setStyleSheet("color: white; font-size: 9px; background: rgba(0,0,0,120); "
                         "border-radius: 4px; padding: 1px 4px;");
    label->setAlignment(Qt::AlignCenter);
    v->addWidget(label, 0, Qt::AlignHCenter);

    dockLayout->insertWidget(dockLayout->count() - 1, app);
}
