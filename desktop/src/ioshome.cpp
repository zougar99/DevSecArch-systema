#include "ioshome.h"
#include <QVBoxLayout>
#include <QPushButton>

IOSHome::IOSHome(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
}

void IOSHome::setupUI()
{
    setStyleSheet("IOSHome { background: transparent; }");

    QVBoxLayout *main = new QVBoxLayout(this);
    main->setContentsMargins(40, 30, 40, 20);
    main->setSpacing(20);

    appGrid = new QGridLayout();
    appGrid->setSpacing(28);
    appGrid->setContentsMargins(0, 0, 0, 0);

    // iOS home screen grid of apps
    addIcon(0, 0, "Files",       "📁", "#0277bd");
    addIcon(0, 1, "Browser",     "🌐", "#1565c0");
    addIcon(0, 2, "Editor",      "✏️", "#2e7d32");
    addIcon(0, 3, "Terminal",    "⌨️", "#424242");
    addIcon(1, 0, "Forxo Store", "🛒", "#00838f");
    addIcon(1, 1, "Security",    "🛡️", "#b71c1c");
    addIcon(1, 2, "Settings",    "⚙️", "#37474f");
    addIcon(1, 3, "About",       "ℹ️", "#6a1b9a");

    QWidget *gridWrap = new QWidget();
    gridWrap->setStyleSheet("background: transparent;");
    gridWrap->setLayout(appGrid);
    main->addWidget(gridWrap);
    main->addStretch();
}

void IOSHome::addIcon(int row, int col, const QString &name, const QString &icon, const QString &color)
{
    QWidget *app = new QWidget();
    app->setFixedSize(92, 100);
    app->setCursor(Qt::PointingHandCursor);

    QVBoxLayout *v = new QVBoxLayout(app);
    v->setContentsMargins(0, 0, 0, 0);
    v->setSpacing(6);

    QPushButton *btn = new QPushButton(icon);
    btn->setFixedSize(72, 72);
    btn->setStyleSheet(QString(
        "QPushButton { background-color: %1; color: white; border: none; "
        "border-radius: 18px; font-size: 34px; }"
        "QPushButton:hover { background-color: %2; }"
    ).arg(color, color));
    btn->setCursor(Qt::PointingHandCursor);
    btn->setToolTip(name);
    connect(btn, &QPushButton::clicked, this, [this, name]() { emit appRequested(name); });

    v->addWidget(btn, 0, Qt::AlignHCenter);

    QLabel *lbl = new QLabel(name);
    lbl->setStyleSheet("color: white; font-size: 11px; background: transparent;");
    lbl->setAlignment(Qt::AlignCenter);
    v->addWidget(lbl, 0, Qt::AlignHCenter);

    appGrid->addWidget(app, row, col);
}
