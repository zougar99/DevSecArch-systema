#include <QApplication>
#include <QStyleFactory>
#include <QPalette>
#include <QFont>
#include "iosshell.h"

void setDarkTheme(QApplication &app)
{
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(15, 32, 39));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(20, 20, 28));
    darkPalette.setColor(QPalette::AlternateBase, QColor(35, 35, 45));
    darkPalette.setColor(QPalette::ToolTipBase, QColor(35, 35, 45));
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(45, 45, 55));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(79, 195, 247));
    darkPalette.setColor(QPalette::Highlight, QColor(79, 195, 247));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    darkPalette.setColor(QPalette::Disabled, QPalette::Text, QColor(127, 127, 127));
    darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(127, 127, 127));

    app.setPalette(darkPalette);
    app.setStyle(QStyleFactory::create("Fusion"));
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("ForxoOS iOS");
    app.setOrganizationName("ForxoOS");
    app.setApplicationVersion("2.0.0");

    QFont defaultFont("Segoe UI", 10);
    app.setFont(defaultFont);

    setDarkTheme(app);

    IOSShell shell;
    shell.setWindowTitle("ForxoOS - iOS Desktop");
    shell.resize(1280, 800);
    shell.show();

    return app.exec();
}
