#include "filemanager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QDir>
#include <QFileInfo>

FileManager::FileManager(QWidget *parent)
    : QWidget(parent)
    , currentPath(QDir::homePath())
{
    setupUI();
}

FileManager::~FileManager()
{
}

void FileManager::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // Toolbar
    QFrame *toolbar = new QFrame();
    toolbar->setStyleSheet("QFrame { background-color: #252525; padding: 5px; }");
    QHBoxLayout *toolbarLayout = new QHBoxLayout(toolbar);

    QPushButton *homeBtn = new QPushButton("Home");
    QPushButton *upBtn = new QPushButton("Up");
    QPushButton *refreshBtn = new QPushButton("Refresh");

    pathEdit = new QLineEdit(currentPath);
    pathEdit->setStyleSheet(
        "QLineEdit { background-color: #353535; color: white; border: 1px solid #444; "
        "padding: 8px; border-radius: 5px; font-size: 14px; }"
    );

    QString btnStyle = "QPushButton { background-color: #353535; color: white; border: none; "
                       "padding: 8px 16px; border-radius: 5px; }"
                       "QPushButton:hover { background-color: #2a82da; }";

    homeBtn->setStyleSheet(btnStyle);
    upBtn->setStyleSheet(btnStyle);
    refreshBtn->setStyleSheet(btnStyle);

    toolbarLayout->addWidget(homeBtn);
    toolbarLayout->addWidget(upBtn);
    toolbarLayout->addWidget(pathEdit);
    toolbarLayout->addWidget(refreshBtn);

    mainLayout->addWidget(toolbar);

    // Splitter for tree and list
    splitter = new QSplitter(Qt::Horizontal);

    // File system model
    model = new QFileSystemModel(this);
    model->setRootPath(QDir::homePath());
    model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);

    // Tree view (left panel)
    treeView = new QTreeView();
    treeView->setModel(model);
    treeView->setRootIndex(model->index(QDir::homePath()));
    treeView->setAnimated(true);
    treeView->setHeaderHidden(true);
    treeView->setStyleSheet(
        "QTreeView { background-color: #1e1e1e; color: white; border: none; }"
        "QTreeView::item:hover { background-color: #2a82da; }"
        "QTreeView::item:selected { background-color: #2a82da; }"
    );

    // Hide unnecessary columns
    for (int i = 1; i < model->columnCount(); i++) {
        treeView->hideColumn(i);
    }

    // List view (right panel)
    listView = new QListView();
    listView->setModel(model);
    listView->setRootIndex(model->index(QDir::homePath()));
    listView->setViewMode(QListView::IconMode);
    listView->setGridSize(QSize(100, 100));
    listView->setIconSize(QSize(48, 48));
    listView->setStyleSheet(
        "QListView { background-color: #1e1e1e; color: white; border: none; }"
        "QListView::item:hover { background-color: #2a82da; }"
        "QListView::item:selected { background-color: #2a82da; }"
    );

    splitter->addWidget(treeView);
    splitter->addWidget(listView);
    splitter->setSizes({250, 750});

    mainLayout->addWidget(splitter);

    // Info bar
    infoLabel = new QLabel("Ready");
    infoLabel->setStyleSheet(
        "QLabel { background-color: #252525; color: #888; padding: 5px 10px; }"
    );
    mainLayout->addWidget(infoLabel);

    // Connections
    connect(homeBtn, &QPushButton::clicked, this, &FileManager::goHome);
    connect(upBtn, &QPushButton::clicked, this, &FileManager::goUp);
    connect(refreshBtn, &QPushButton::clicked, this, &FileManager::refresh);
    connect(pathEdit, &QLineEdit::returnPressed, this, [this]() {
        navigateTo(pathEdit->text());
    });
    connect(listView, &QListView::clicked, this, &FileManager::onFileClicked);
    connect(treeView, &QTreeView::clicked, this, [this](const QModelIndex &index) {
        navigateTo(model->filePath(index));
    });
}

void FileManager::navigateTo(const QString &path)
{
    QFileInfo info(path);
    if (info.isDir()) {
        currentPath = path;
        pathEdit->setText(path);
        listView->setRootIndex(model->index(path));
        treeView->setRootIndex(model->index(path));
        infoLabel->setText(QString("Files: %1").arg(model->rowCount(model->index(path))));
    }
}

void FileManager::goUp()
{
    QDir dir(currentPath);
    if (dir.cdUp()) {
        navigateTo(dir.absolutePath());
    }
}

void FileManager::goHome()
{
    navigateTo(QDir::homePath());
}

void FileManager::refresh()
{
    model->setRootPath(currentPath);
    listView->setRootIndex(model->index(currentPath));
    treeView->setRootIndex(model->index(currentPath));
}

void FileManager::onFileClicked(const QModelIndex &index)
{
    QString filePath = model->filePath(index);
    QFileInfo info(filePath);

    if (info.isDir()) {
        navigateTo(filePath);
    } else {
        infoLabel->setText(QString("Selected: %1 (%2 KB)")
            .arg(info.fileName())
            .arg(info.size() / 1024));
    }
}
