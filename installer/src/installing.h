#ifndef INSTALLING_H
#define INSTALLING_H

#include <QWidget>
#include <QProgressBar>
#include <QTextEdit>
#include <QProcess>
#include <QTimer>

class Installer;

class Installing : public QWidget
{
    Q_OBJECT

public:
    explicit Installing(Installer *installer, QWidget *parent = nullptr);

private slots:
    void updateProgress();
    void readOutput();
    void onFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:
    void setupUI();
    void startInstallation();

    Installer *installer;
    QProgressBar *progressBar;
    QTextEdit *logOutput;
    QTimer *progressTimer;
    QProcess *installProcess;
    int progress;
};

#endif // INSTALLING_H
