#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QWidget>
#include <QTreeView>
#include <QListView>
#include <QSplitter>
#include <QLineEdit>
#include <QLabel>
#include <QToolBar>
#include <QFileSystemModel>

class FileManager : public QWidget
{
    Q_OBJECT

public:
    explicit FileManager(QWidget *parent = nullptr);
    ~FileManager();

private slots:
    void navigateTo(const QString &path);
    void goUp();
    void goHome();
    void refresh();
    void onFileClicked(const QModelIndex &index);

private:
    void setupUI();

    QTreeView *treeView;
    QListView *listView;
    QLineEdit *pathEdit;
    QLabel *infoLabel;
    QFileSystemModel *model;
    QSplitter *splitter;
    QString currentPath;
};

#endif // FILEMANAGER_H
