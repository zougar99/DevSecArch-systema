#ifndef SUMMARY_H
#define SUMMARY_H

#include <QWidget>
#include <QTextEdit>

class Installer;

class Summary : public QWidget
{
    Q_OBJECT

public:
    explicit Summary(Installer *installer, QWidget *parent = nullptr);

private:
    void setupUI();
    Installer *installer;
    QTextEdit *summaryText;
};

#endif // SUMMARY_H
