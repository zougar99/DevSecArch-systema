#include <QApplication>
#include <QStyleFactory>
#include <QPalette>
#include <QFont>
#include "installer.h"

void setDarkTheme(QApplication &app)
{
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(26, 26, 46));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(13, 17, 23));
    darkPalette.setColor(QPalette::AlternateBase, QColor(22, 33, 62));
    darkPalette.setColor(QPalette::ToolTipBase, QColor(22, 33, 62));
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(22, 33, 62));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    app.setPalette(darkPalette);
    app.setStyle(QStyleFactory::create("Fusion"));
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("ForxoOS Installer");
    app.setOrganizationName("ForxoOS");
    app.setApplicationVersion("1.0.0");

    QFont defaultFont("Segoe UI", 10);
    app.setFont(defaultFont);

    setDarkTheme(app);

    Installer installer;
    installer.show();

    return app.exec();
}
