#include "terminal.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

Terminal::Terminal(QWidget *parent)
    : QWidget(parent)
    , currentDir(QDir::homePath())
{
    setupUI();

    process = new QProcess(this);
    connect(process, &QProcess::readyReadStandardOutput, this, &Terminal::readOutput);
    connect(process, &QProcess::readyReadStandardError, this, &Terminal::readError);

    appendOutput("<span style='color: #2a82da;'>ForxoOS Terminal v1.0</span>");
    appendOutput("<span style='color: #888;'>Type 'help' for commands</span>");
    appendOutput("");
}

Terminal::~Terminal()
{
    process->kill();
}

void Terminal::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // Output
    output = new QTextEdit();
    output->setReadOnly(true);
    output->setStyleSheet(
        "QTextEdit { background-color: #1e1e1e; color: #00ff00; border: none; "
        "font-family: 'Cascadia Code', 'Consolas', monospace; font-size: 13px; "
        "padding: 10px; }"
    );

    mainLayout->addWidget(output);

    // Input
    QFrame *inputFrame = new QFrame();
    inputFrame->setStyleSheet("QFrame { background-color: #252525; }");
    QHBoxLayout *inputLayout = new QHBoxLayout(inputFrame);

    QLabel *prompt = new QLabel("$ ");
    prompt->setStyleSheet("color: #2a82da; font-family: monospace; font-size: 14px; font-weight: bold;");

    input = new QLineEdit();
    input->setStyleSheet(
        "QLineEdit { background-color: transparent; color: #00ff00; border: none; "
        "font-family: 'Cascadia Code', monospace; font-size: 14px; }"
    );

    inputLayout->addWidget(prompt);
    inputLayout->addWidget(input);

    mainLayout->addWidget(inputFrame);

    // Connect
    connect(input, &QLineEdit::returnPressed, this, &Terminal::executeCommand);
}

void Terminal::executeCommand()
{
    QString cmd = input->text().trimmed();
    if (cmd.isEmpty()) return;

    // Show command
    appendOutput("<span style='color: #2a82da;'>$ </span>" + cmd.toHtmlEscaped());

    // Handle special commands
    if (cmd == "clear") {
        output->clear();
        input->clear();
        return;
    }

    if (cmd == "help") {
        appendOutput("<span style='color: #ffc107;'>Available commands:</span>");
        appendOutput("  clear     - Clear terminal");
        appendOutput("  help      - Show this help");
        appendOutput("  ls        - List files");
        appendOutput("  pwd       - Print working directory");
        appendOutput("  whoami    - Current user");
        appendOutput("  nmap      - Network scanner");
        appendOutput("  neofetch  - System info");
        appendOutput("");
        input->clear();
        return;
    }

    // Execute command
    process->setWorkingDirectory(currentDir);
    process->start("bash", {"-c", cmd});

    input->clear();
}

void Terminal::readOutput()
{
    QString output_text = process->readAllStandardOutput();
    appendOutput(output_text);
}

void Terminal::readError()
{
    QString error_text = process->readAllStandardError();
    appendOutput("<span style='color: #dc3545;'>" + error_text.toHtmlEscaped() + "</span>");
}

void Terminal::appendOutput(const QString &text)
{
    output->append(text);
    // Auto-scroll to bottom
    QTextCursor cursor = output->textCursor();
    cursor.movePosition(QTextCursor::End);
    output->setTextCursor(cursor);
}
