#include <QApplication>
#include <QStyleFactory>
#include <QPalette>
#include <QFont>
#include <QFile>
#include <QTextStream>
#include "mainwindow.h"

void setDarkTheme(QApplication &app)
{
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(30, 30, 30));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(35, 35, 35));
    darkPalette.setColor(QPalette::AlternateBase, QColor(45, 45, 45));
    darkPalette.setColor(QPalette::ToolTipBase, QColor(45, 45, 45));
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(45, 45, 45));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    darkPalette.setColor(QPalette::Disabled, QPalette::Text, QColor(127, 127, 127));
    darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(127, 127, 127));

    app.setPalette(darkPalette);
    app.setStyle(QStyleFactory::create("Fusion"));
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("ForxoOS Desktop");
    app.setOrganizationName("ForxoOS");
    app.setApplicationVersion("1.0.0");

    QFont defaultFont("Segoe UI", 10);
    app.setFont(defaultFont);

    setDarkTheme(app);

    MainWindow window;
    window.show();

    return app.exec();
}
