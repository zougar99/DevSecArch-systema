#include <QApplication>
#include <QStyleFactory>
#include <QPalette>
#include <QFont>
#include <QFile>
#include <QIcon>
#include "installer.h"

void setDarkTheme(QApplication &app)
{
    QPalette darkPalette;
    // ForxoOS palette: Void #0B1020 · Navy #12182B · Fox #FF6B2C
    darkPalette.setColor(QPalette::Window, QColor(11, 16, 32));
    darkPalette.setColor(QPalette::WindowText, QColor(244, 247, 251));
    darkPalette.setColor(QPalette::Base, QColor(18, 24, 43));
    darkPalette.setColor(QPalette::AlternateBase, QColor(32, 38, 58));
    darkPalette.setColor(QPalette::ToolTipBase, QColor(18, 24, 43));
    darkPalette.setColor(QPalette::ToolTipText, QColor(244, 247, 251));
    darkPalette.setColor(QPalette::Text, QColor(244, 247, 251));
    darkPalette.setColor(QPalette::Button, QColor(30, 41, 59));
    darkPalette.setColor(QPalette::ButtonText, QColor(244, 247, 251));
    darkPalette.setColor(QPalette::BrightText, QColor(225, 29, 72));
    darkPalette.setColor(QPalette::Link, QColor(255, 107, 44));
    darkPalette.setColor(QPalette::Highlight, QColor(255, 107, 44));
    darkPalette.setColor(QPalette::HighlightedText, QColor(11, 16, 32));
    darkPalette.setColor(QPalette::Disabled, QPalette::Text, QColor(139, 147, 167));
    darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(139, 147, 167));

    app.setPalette(darkPalette);
    app.setStyle(QStyleFactory::create("Fusion"));
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("ForxoOS Installer");
    app.setOrganizationName("ForxoOS");
    app.setApplicationVersion("2.0.0");

    QFont defaultFont("Noto Sans", 10);
    app.setFont(defaultFont);

    setDarkTheme(app);

    QFile styleFile(":/theme.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        app.setStyleSheet(styleFile.readAll());
    }

    app.setWindowIcon(QIcon(":/icons/forxoos-logo.svg"));

    Installer installer;
    installer.show();

    return app.exec();
}
