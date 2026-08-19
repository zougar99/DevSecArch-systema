#ifndef SECURITYTOOLS_H
#define SECURITYTOOLS_H

#include <QWidget>
#include <QTabWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QListWidget>

class SecurityTools : public QWidget
{
    Q_OBJECT

public:
    explicit SecurityTools(QWidget *parent = nullptr);
    ~SecurityTools();

private slots:
    void runNmap();
    void runScan();
    void updateOutput();

private:
    void setupUI();
    void createNmapTab();
    void createWifiTab();
    void createPentestTab();
    void createForensicsTab();

    QTabWidget *toolTabs;
    QTextEdit *output;
    QLineEdit *targetInput;
    QComboBox *scanType;
    QPushButton *scanBtn;
    QProgressBar *progressBar;
    QListWidget *toolsList;
};

#endif // SECURITYTOOLS_H
