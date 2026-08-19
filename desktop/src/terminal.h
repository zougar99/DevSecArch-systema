#ifndef TERMINAL_H
#define TERMINAL_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QProcess>

class Terminal : public QWidget
{
    Q_OBJECT

public:
    explicit Terminal(QWidget *parent = nullptr);
    ~Terminal();

private slots:
    void executeCommand();
    void readOutput();
    void readError();

private:
    void setupUI();
    void appendOutput(const QString &text);

    QTextEdit *output;
    QLineEdit *input;
    QProcess *process;
    QString currentDir;
};

#endif // TERMINAL_H
