#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QTabWidget>
#include <QFileDialog>

class TextEditor : public QWidget
{
    Q_OBJECT

public:
    explicit TextEditor(QWidget *parent = nullptr);
    ~TextEditor();

    void newFile();
    void openFile(const QString &filePath);
    void saveFile();

private slots:
    void onTextChanged();

private:
    void setupUI();

    QTabWidget *editorTabs;
    QTextEdit *currentEditor;
    QLabel *statusLabel;
    QLabel *lineLabel;
    QString currentFilePath;
};

#endif // TEXTEDITOR_H
