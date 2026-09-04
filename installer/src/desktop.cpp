#include "desktop.h"
#include "installer.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QRadioButton>
#include <QFrame>

Desktop::Desktop(Installer *inst, QWidget *parent)
    : QWidget(parent)
    , installer(inst)
{
    setupUI();
}

void Desktop::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *title = new QLabel("Select Desktop Environment");
    title->setStyleSheet("font-size: 20px; font-weight: bold; color: white;");
    mainLayout->addWidget(title);

    QLabel *desc = new QLabel("Choose your desktop environment:");
    desc->setStyleSheet("font-size: 14px; color: #888;");
    mainLayout->addWidget(desc);

    mainLayout->addSpacing(20);

    QGridLayout *grid = new QGridLayout();
    grid->setSpacing(15);

    desktopGroup = new QButtonGroup(this);

    QStringList names = {"Deepin DDE", "GNOME", "KDE Plasma", "i3wm", "Sway", "XFCE", "Cinnamon", "MATE"};
    QStringList descs = {
        "Beautiful, modern desktop",
        "Clean, modern desktop",
        "Feature-rich, customizable",
        "Tiling window manager",
        "Wayland tiling WM",
        "Lightweight, fast",
        "Traditional desktop",
        "Classic desktop"
    };
    QStringList colors = {"#e74c3c", "#2a82da", "#1abc9c", "#9b59b6", "#3498db", "#f39c12", "#27ae60", "#95a5a6"};

    for (int i = 0; i < names.size(); i++) {
        QFrame *card = new QFrame();
        card->setStyleSheet(
            QString("QFrame { background-color: #16213e; border-radius: 10px; padding: 15px; "
                    "border: 2px solid transparent; }"
                    "QFrame:hover { border: 2px solid %1; }").arg(colors[i])
        );

        QVBoxLayout *cardLayout = new QVBoxLayout(card);

        QRadioButton *radio = new QRadioButton(names[i]);
        radio->setStyleSheet(QString("color: %1; font-size: 16px; font-weight: bold;").arg(colors[i]));
        desktopGroup->addButton(radio, i);

        QLabel *descLabel = new QLabel(descs[i]);
        descLabel->setStyleSheet("color: #888; font-size: 12px;");

        cardLayout->addWidget(radio);
        cardLayout->addWidget(descLabel);

        grid->addWidget(card, i / 4, i % 4);

        if (i == 0) radio->setChecked(true);
    }

    connect(desktopGroup, QOverload<int, bool>::of(&QButtonGroup::buttonClicked), this, [this](int id) {
        installer->desktop = desktopGroup->button(id)->text();
    });

    installer->desktop = "Deepin DDE";

    mainLayout->addLayout(grid);
    mainLayout->addStretch();
}
