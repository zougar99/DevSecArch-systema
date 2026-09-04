#include "installing.h"
#include "installer.h"
#include <QVBoxLayout>
#include <QLabel>

Installing::Installing(Installer *inst, QWidget *parent)
    : QWidget(parent)
    , installer(inst)
    , progress(0)
{
    setupUI();

    connect(progressTimer, &QTimer::timeout, this, &Installing::updateProgress);
    connect(installProcess, &QProcess::readyReadStandardOutput, this, &Installing::readOutput);
    connect(installProcess, &QProcess::readyReadStandardError, this, &Installing::readOutput);
    connect(installProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &Installing::onFinished);

    startInstallation();
}

void Installing::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *title = new QLabel("Installing ForxoOS...");
    title->setStyleSheet("font-size: 20px; font-weight: bold; color: #2a82da;");
    layout->addWidget(title);

    QLabel *desc = new QLabel("Please wait while the installation completes.");
    desc->setStyleSheet("font-size: 14px; color: #888;");
    layout->addWidget(desc);

    layout->addSpacing(20);

    progressBar = new QProgressBar();
    progressBar->setRange(0, 0);
    progressBar->setValue(0);
    progressBar->setTextVisible(true);
    progressBar->setStyleSheet(
        "QProgressBar { border: 2px solid #333; border-radius: 5px; text-align: center; "
        "height: 30px; font-size: 14px; color: white; }"
        "QProgressBar::chunk { background-color: #2a82da; border-radius: 3px; }"
    );
    layout->addWidget(progressBar);

    layout->addSpacing(10);

    logOutput = new QTextEdit();
    logOutput->setReadOnly(true);
    logOutput->setStyleSheet(
        "QTextEdit { background-color: #0d1117; color: #00ff00; border: 1px solid #333; "
        "font-family: monospace; font-size: 12px; padding: 10px; }"
    );
    layout->addWidget(logOutput);

    installProcess = new QProcess(this);
    progressTimer = new QTimer(this);
}

void Installing::startInstallation()
{
    logOutput->append("Starting ForxoOS installation...");
    logOutput->append("=====================================");
    logOutput->append("");

    QString desktop = installer->desktop.toLower();
    if (desktop.contains("deepin")) desktop = "deepin";
    else if (desktop.contains("gnome")) desktop = "gnome";
    else if (desktop.contains("kde")) desktop = "kde-plasma";
    else if (desktop.contains("xfce")) desktop = "xfce4";
    else if (desktop.contains("i3")) desktop = "i3wm";
    else if (desktop.contains("sway")) desktop = "sway";
    else if (desktop.contains("cinnamon")) desktop = "cinnamon";
    else if (desktop.contains("mate")) desktop = "mate";
    else desktop = "deepin";

    QString config = QString(
        "{\"language\": \"en\", "
        "\"keymap\": \"us\", "
        "\"hostname\": \"%1\", "
        "\"username\": \"%2\", "
        "\"password\": \"%3\", "
        "\"root-password\": \"%4\", "
        "\"desktop\": {\"base\": \"%5\"}, "
        "\"audio\": \"pipewire\", "
        "\"kernel\": \"linux\", "
        "\"bootloader\": \"grub\"}"
    ).arg(installer->hostname.isEmpty() ? "forxos" : installer->hostname)
     .arg(installer->username.isEmpty() ? "devsec" : installer->username)
     .arg(installer->password.isEmpty() ? "password" : installer->password)
     .arg(installer->rootPassword.isEmpty() ? "root" : installer->rootPassword)
     .arg(desktop);

    logOutput->append("Configuration:");
    logOutput->append(config);
    logOutput->append("");
    logOutput->append("Running archinstall...");
    logOutput->append("");

    installProcess->start("archinstall", {"--config", config});
}

void Installing::updateProgress()
{
    if (progress < 95) {
        progress += 1;
        progressBar->setValue(progress);
    }
}

void Installing::readOutput()
{
    QString output = installProcess->readAllStandardOutput();
    QString error = installProcess->readAllStandardError();

    if (!output.isEmpty()) {
        logOutput->append(output);
    }
    if (!error.isEmpty()) {
        logOutput->append("<span style='color: #e74c3c;'>" + error + "</span>");
    }

    QTextCursor cursor = logOutput->textCursor();
    cursor.movePosition(QTextCursor::End);
    logOutput->setTextCursor(cursor);
}

void Installing::onFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    progressTimer->stop();
    progressBar->setRange(0, 100);

    if (exitStatus == QProcess::NormalExit && exitCode == 0) {
        progressBar->setValue(100);
        logOutput->append("<span style='color: #2ecc71;'>Installation completed successfully!</span>");
    } else {
        progressBar->setValue(progress);
        logOutput->append(QString("<span style='color: #e74c3c;'>Installation failed (exit code: %1)</span>").arg(exitCode));
    }
}
