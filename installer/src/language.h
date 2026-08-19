#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QWidget>
#include <QListWidget>

class Installer;

class Language : public QWidget
{
    Q_OBJECT

public:
    explicit Language(Installer *installer, QWidget *parent = nullptr);

private:
    void setupUI();
    Installer *installer;
    QListWidget *languageList;
};

#endif // LANGUAGE_H
