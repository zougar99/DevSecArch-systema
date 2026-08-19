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

    startInstallation();
}

void Installing::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *title = new QLabel("Installing Arch Linux...");
    title->setStyleSheet("font-size: 20px; font-weight: bold; color: #2a82da;");
    layout->addWidget(title);

    QLabel *desc = new QLabel("Please wait while the installation completes.");
    desc->setStyleSheet("font-size: 14px; color: #888;");
    layout->addWidget(desc);

    layout->addSpacing(20);

    progressBar = new QProgressBar();
    progressBar->setRange(0, 100);
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
    logOutput->append("Starting Arch Linux installation...");
    logOutput->append("=====================================");
    logOutput->append("");

    // Generate archinstall configuration
    QString config = QString(
        "{\"language\": \"en\", "
        "\"keymap\": \"us\", "
        "\"hostname\": \"%1\", "
        "\"username\": \"%2\", "
        "\"password\": \"%3\", "
        "\"root-password\": \"%4\", "
        "\"desktop\": \"%5\", "
        "\"audio\": \"pipewire\", "
        "\"kernel\": \"linux\", "
        "\"bootloader\": \"grub\"}"
    ).arg(installer->hostname.isEmpty() ? "archlinux" : installer->hostname)
     .arg(installer->username.isEmpty() ? "user" : installer->username)
     .arg(installer->password.isEmpty() ? "password" : installer->password)
     .arg(installer->rootPassword.isEmpty() ? "root" : installer->rootPassword)
     .arg(installer->desktop.isEmpty() ? "gnome" : installer->desktop.toLower());

    logOutput->append("Configuration:");
    logOutput->append(config);
    logOutput->append("");
    logOutput->append("Running archinstall...");
    logOutput->append("");

    // Run archinstall
    installProcess->start("archinstall", {"--config", config});

    progressTimer->start(100);
}

void Installing::updateProgress()
{
    if (progress < 100) {
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

    // Auto-scroll
    QTextCursor cursor = logOutput->textCursor();
    cursor.movePosition(QTextCursor::End);
    logOutput->setTextCursor(cursor);
}
