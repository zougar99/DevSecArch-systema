#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include <QListWidget>

class Installer;

class Keyboard : public QWidget
{
    Q_OBJECT

public:
    explicit Keyboard(Installer *installer, QWidget *parent = nullptr);

private:
    void setupUI();
    Installer *installer;
    QListWidget *keyboardList;
};

#endif // KEYBOARD_H
