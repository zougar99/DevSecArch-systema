#ifndef FORXOSTORE_H
#define FORXOSTORE_H

#include <QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QProgressBar>
#include <QLabel>
#include <QPushButton>
#include <QProcess>
#include <QScrollArea>
#include <QStringList>

class ForxoStore : public QWidget
{
    Q_OBJECT

public:
    explicit ForxoStore(QWidget *parent = nullptr);

private slots:
    void installPackage();
    void removePackage();
    void refreshPackages();
    void showCategory(const QString &category);

private:
    void setupUI();
    void loadPackages();
    void runCommand(const QString &cmd);
    QStringList getInstalledPackages();

    QListWidget *categoryList;
    QListWidget *packageList;
    QProgressBar *progressBar;
    QLabel *statusLabel;
    QProcess *process;
    QString currentCategory;
};

#endif // FORXOSTORE_H
