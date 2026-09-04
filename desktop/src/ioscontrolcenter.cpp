#include "ioscontrolcenter.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QProcess>

IOSControlCenter::IOSControlCenter(QWidget *parent)
    : QWidget(parent)
{
    setFixedWidth(340);
    setStyleSheet("IOSControlCenter { background-color: rgba(20,20,28,92%); "
                  "border-radius: 28px; border: 1px solid rgba(255,255,255,12%); }");

    setupUI();
}

QWidget *IOSControlCenter::makeToggle(const QString &icon, const QString &label, bool active)
{
    QFrame *card = new QFrame();
    card->setFixedSize(88, 88);
    QString bg = active ? "rgba(79,195,247,70%)" : "rgba(255,255,255,10%)";
    card->setStyleSheet(QString(
        "QFrame { background-color: %1; border-radius: 18px; }"
        "QFrame:hover { background-color: %2; }"
    ).arg(bg, active ? "rgba(79,195,247,85%)" : "rgba(255,255,255,18%)"));

    QVBoxLayout *v = new QVBoxLayout(card);
    v->setSpacing(6);
    v->setContentsMargins(8, 10, 8, 10);

    QLabel *iconLbl = new QLabel(icon);
    iconLbl->setStyleSheet("background: transparent;");
    iconLbl->setAlignment(Qt::AlignCenter);

    QLabel *textLbl = new QLabel(label);
    textLbl->setStyleSheet("color: white; background: transparent; font-size: 10px;");
    textLbl->setAlignment(Qt::AlignCenter);

    v->addStretch();
    v->addWidget(iconLbl);
    v->addWidget(textLbl);
    v->addStretch();

    return card;
}

void IOSControlCenter::setupUI()
{
    QVBoxLayout *main = new QVBoxLayout(this);
    main->setContentsMargins(20, 20, 20, 20);
    main->setSpacing(16);

    QLabel *title = new QLabel("Control Center");
    title->setStyleSheet("color: white; font-size: 16px; font-weight: bold; background: transparent;");
    main->addWidget(title);

    // Toggles grid - 3 columns x 2 rows
    QWidget *gridWrap = new QWidget();
    gridWrap->setStyleSheet("background: transparent;");
    grid = new QGridLayout(gridWrap);
    grid->setSpacing(12);
    grid->setContentsMargins(0, 0, 0, 0);

    grid->addWidget(makeToggle("✈️", "Airplane", false), 0, 0);
    grid->addWidget(makeToggle("📡", "WiFi", true), 0, 1);
    grid->addWidget(makeToggle("🔵", "Bluetooth", true), 0, 2);
    grid->addWidget(makeToggle("🔔", "Silent", false), 1, 0);
    grid->addWidget(makeToggle("🔄", "Rotate", true), 1, 1);
    grid->addWidget(makeToggle("📱", "DND", false), 1, 2);

    main->addWidget(gridWrap);

    // Brightness
    QLabel *brightLabel = new QLabel("🔆 Brightness");
    brightLabel->setStyleSheet("color: white; background: transparent; font-size: 12px;");
    brightnessSlider = new QSlider(Qt::Horizontal);
    brightnessSlider->setRange(0, 100);
    brightnessSlider->setValue(80);
    brightnessSlider->setStyleSheet(
        "QSlider::groove:horizontal { height: 6px; background: rgba(255,255,255,20%); border-radius: 3px; }"
        "QSlider::handle:horizontal { width: 14px; height: 14px; margin: -5px 0; background: white; border-radius: 7px; }"
    );
    connect(brightnessSlider, &QSlider::valueChanged, this, [](int v) {
        // Best-effort: only works with xbacklight / brightnessctl
        if (v % 5 == 0) QProcess::startDetached("bash", {"-c", QString("brightnessctl set %1%% 2>/dev/null || true").arg(v)});
    });

    QLabel *volLabel = new QLabel("🔊 Volume");
    volLabel->setStyleSheet("color: white; background: transparent; font-size: 12px;");
    volumeSlider = new QSlider(Qt::Horizontal);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(70);
    volumeSlider->setStyleSheet(
        "QSlider::groove:horizontal { height: 6px; background: rgba(255,255,255,20%); border-radius: 3px; }"
        "QSlider::handle:horizontal { width: 14px; height: 14px; margin: -5px 0; background: white; border-radius: 7px; }"
    );
    connect(volumeSlider, &QSlider::valueChanged, this, [](int v) {
        QProcess::startDetached("bash", {"-c", QString("pactl set-sink-volume @DEFAULT_SINK@ %1% 2>/dev/null || true").arg(v)});
    });

    main->addWidget(brightLabel);
    main->addWidget(brightnessSlider);
    main->addWidget(volLabel);
    main->addWidget(volumeSlider);
    main->addStretch();
}
