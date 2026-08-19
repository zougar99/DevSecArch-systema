#ifndef USERINFO_H
#define USERINFO_H

#include <QWidget>
#include <QLineEdit>

class Installer;

class UserInfo : public QWidget
{
    Q_OBJECT

public:
    explicit UserInfo(Installer *installer, QWidget *parent = nullptr);

private:
    void setupUI();
    Installer *installer;
    QLineEdit *hostnameEdit;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QLineEdit *confirmEdit;
    QLineEdit *rootPassEdit;
};

#endif // USERINFO_H
