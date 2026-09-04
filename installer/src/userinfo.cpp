#include "userinfo.h"
#include "installer.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <QFrame>

UserInfo::UserInfo(Installer *inst, QWidget *parent)
    : QWidget(parent)
    , installer(inst)
{
    setupUI();
}

void UserInfo::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *title = new QLabel("User Configuration");
    title->setStyleSheet("font-size: 20px; font-weight: bold; color: white;");
    mainLayout->addWidget(title);

    QLabel *desc = new QLabel("Set up your user account:");
    desc->setStyleSheet("font-size: 14px; color: #888;");
    mainLayout->addWidget(desc);

    mainLayout->addSpacing(20);

    QFrame *formFrame = new QFrame();
    formFrame->setStyleSheet(
        "QFrame { background-color: #16213e; border-radius: 10px; padding: 20px; }"
    );
    QGridLayout *formLayout = new QGridLayout(formFrame);

    QString labelStyle = "color: white; font-size: 14px; font-weight: bold;";
    QString inputStyle = "QLineEdit { background-color: #0d1117; color: white; border: 1px solid #333; "
                        "padding: 12px; border-radius: 5px; font-size: 14px; }"
                        "QLineEdit:focus { border: 1px solid #2a82da; }";

    QLabel *hostLabel = new QLabel("Hostname:");
    hostLabel->setStyleSheet(labelStyle);
    hostnameEdit = new QLineEdit("forxos");
    hostnameEdit->setStyleSheet(inputStyle);

    QLabel *userLabel = new QLabel("Username:");
    userLabel->setStyleSheet(labelStyle);
    usernameEdit = new QLineEdit("devsec");
    usernameEdit->setStyleSheet(inputStyle);

    QLabel *passLabel = new QLabel("Password:");
    passLabel->setStyleSheet(labelStyle);
    passwordEdit = new QLineEdit();
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setStyleSheet(inputStyle);

    QLabel *confirmLabel = new QLabel("Confirm Password:");
    confirmLabel->setStyleSheet(labelStyle);
    confirmEdit = new QLineEdit();
    confirmEdit->setEchoMode(QLineEdit::Password);
    confirmEdit->setStyleSheet(inputStyle);

    QLabel *rootLabel = new QLabel("Root Password:");
    rootLabel->setStyleSheet(labelStyle);
    rootPassEdit = new QLineEdit();
    rootPassEdit->setEchoMode(QLineEdit::Password);
    rootPassEdit->setStyleSheet(inputStyle);

    connect(hostnameEdit, &QLineEdit::textChanged, this, [this](const QString &text) {
        installer->hostname = text;
    });
    connect(usernameEdit, &QLineEdit::textChanged, this, [this](const QString &text) {
        installer->username = text;
    });
    connect(passwordEdit, &QLineEdit::textChanged, this, [this](const QString &text) {
        installer->password = text;
    });
    connect(rootPassEdit, &QLineEdit::textChanged, this, [this](const QString &text) {
        installer->rootPassword = text;
    });

    installer->hostname = "forxos";
    installer->username = "devsec";

    formLayout->addWidget(hostLabel, 0, 0);
    formLayout->addWidget(hostnameEdit, 0, 1);
    formLayout->addWidget(userLabel, 1, 0);
    formLayout->addWidget(usernameEdit, 1, 1);
    formLayout->addWidget(passLabel, 2, 0);
    formLayout->addWidget(passwordEdit, 2, 1);
    formLayout->addWidget(confirmLabel, 3, 0);
    formLayout->addWidget(confirmEdit, 3, 1);
    formLayout->addWidget(rootLabel, 4, 0);
    formLayout->addWidget(rootPassEdit, 4, 1);

    mainLayout->addWidget(formFrame);
    mainLayout->addStretch();
}
