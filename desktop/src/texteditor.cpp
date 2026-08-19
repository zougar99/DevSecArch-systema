#include "texteditor.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

TextEditor::TextEditor(QWidget *parent)
    : QWidget(parent)
    , currentFilePath("")
{
    setupUI();
    newFile();
}

TextEditor::~TextEditor()
{
}

void TextEditor::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // Editor tabs
    editorTabs = new QTabWidget();
    editorTabs->setTabsClosable(true);
    editorTabs->setMovable(true);

    mainLayout->addWidget(editorTabs);

    // Status bar
    QFrame *statusBar = new QFrame();
    statusBar->setStyleSheet("QFrame { background-color: #252525; }");
    QHBoxLayout *statusLayout = new QHBoxLayout(statusBar);

    statusLabel = new QLabel("Ready");
    lineLabel = new QLabel("Ln 1, Col 1");

    statusLabel->setStyleSheet("QLabel { color: #888; padding: 5px; }");
    lineLabel->setStyleSheet("QLabel { color: #888; padding: 5px; }");

    statusLayout->addWidget(statusLabel);
    statusLayout->addStretch();
    statusLayout->addWidget(lineLabel);

    mainLayout->addWidget(statusBar);
}

void TextEditor::newFile()
{
    QTextEdit *editor = new QTextEdit();
    editor->setStyleSheet(
        "QTextEdit { background-color: #1e1e1e; color: #d4d4d4; border: none; "
        "font-family: 'Cascadia Code', 'Consolas', monospace; font-size: 14px; }"
    );

    int index = editorTabs->addTab(editor, "Untitled");
    editorTabs->setCurrentIndex(index);
    currentEditor = editor;

    connect(editor, &QTextEdit::textChanged, this, &TextEditor::onTextChanged);
}

void TextEditor::openFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot open file: " + filePath);
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    QTextEdit *editor = new QTextEdit();
    editor->setPlainText(content);
    editor->setStyleSheet(
        "QTextEdit { background-color: #1e1e1e; color: #d4d4d4; border: none; "
        "font-family: 'Cascadia Code', 'Consolas', monospace; font-size: 14px; }"
    );

    QFileInfo info(filePath);
    int index = editorTabs->addTab(editor, info.fileName());
    editorTabs->setCurrentIndex(index);
    currentEditor = editor;
    currentFilePath = filePath;

    statusLabel->setText(filePath);
    connect(editor, &QTextEdit::textChanged, this, &TextEditor::onTextChanged);
}

void TextEditor::saveFile()
{
    if (currentFilePath.isEmpty()) {
        currentFilePath = QFileDialog::getSaveFileName(this,
            "Save File", QDir::homePath(),
            "Text Files (*.txt);;C++ Files (*.cpp *.h);;All Files (*)");
    }

    if (currentFilePath.isEmpty()) return;

    QFile file(currentFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot save file");
        return;
    }

    QTextStream out(&file);
    out << currentEditor->toPlainText();
    file.close();

    statusLabel->setText("Saved: " + currentFilePath);
}

void TextEditor::onTextChanged()
{
    if (currentEditor) {
        QString text = currentEditor->toPlainText();
        int lines = text.count('\n') + 1;
        lineLabel->setText(QString("Ln %1").arg(lines));
    }
}
