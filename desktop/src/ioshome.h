#ifndef IOSHOME_H
#define IOSHOME_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

class IOSHome : public QWidget
{
    Q_OBJECT

public:
    explicit IOSHome(QWidget *parent = nullptr);

signals:
    void appRequested(const QString &appName);

private:
    void setupUI();
    void addIcon(int row, int col, const QString &name, const QString &icon, const QString &color);
    QGridLayout *appGrid;
};

#endif // IOSHOME_H
