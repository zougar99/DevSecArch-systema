#ifndef IOSDOCK_H
#define IOSDOCK_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QList>

class IOSDock : public QWidget
{
    Q_OBJECT

public:
    explicit IOSDock(QWidget *parent = nullptr);

signals:
    void appRequested(const QString &appName);
    void homeRequested();

private:
    void setupUI();
    void addApp(int index, const QString &name, const QString &icon, const QString &color);
    QHBoxLayout *dockLayout;
    QWidget *dockContainer;
};

#endif // IOSDOCK_H
