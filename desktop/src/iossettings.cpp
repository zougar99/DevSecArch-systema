#include "iossettings.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QProcess>
#include <QListWidgetItem>

IOSSettings::IOSSettings(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
}

QWidget *IOSSettings::createGeneralPage()
{
    QWidget *page = new QWidget();
    page->setStyleSheet("background: transparent;");
    QVBoxLayout *v = new QVBoxLayout(page);
    v->setSpacing(10);

    auto row = [v](const QString &label) {
        QFrame *f = new QFrame();
        f->setStyleSheet("QFrame { background: rgba(255,255,255,8%); border-radius: 12px; padding: 12px; }");
        QHBoxLayout *h = new QHBoxLayout(f);
        QLabel *l = new QLabel(label);
        l->setStyleSheet("color: white; background: transparent; font-size: 14px;");
        h->addWidget(l);
        h->addStretch();
        v->addWidget(f);
    };

    row("Software Update");
    row("Storage");
    row("Battery");
    row("About");
    v->addStretch();
    return page;
}

QWidget *IOSSettings::createDisplayPage()
{
    QWidget *page = new QWidget();
    QVBoxLayout *v = new QVBoxLayout(page);

    QLabel *info = new QLabel("Display settings (use Deepin Control Center)\n"
                              "This is the ForxoOS iOS-style Settings panel.");
    info->setStyleSheet("color: white; font-size: 14px;");
    info->setWordWrap(true);
    v->addWidget(info);
    v->addStretch();
    return page;
}

QWidget *IOSSettings::createAboutPage()
{
    QWidget *page = new QWidget();
    QVBoxLayout *v = new QVBoxLayout(page);

    QProcess procName;
    procName.start("bash", {"-c", "grep PRETTY_NAME /etc/os-release 2>/dev/null | cut -d= -f2-"});
    procName.waitForFinished(2000);
    QString os = procName.readAllStandardOutput().replace('"', ' ').trimmed();
    if (os.isEmpty()) os = "ForxoOS (Arch Linux)";

    QProcess procKernel;
    procKernel.start("bash", {"-c", "uname -r"});
    procKernel.waitForFinished(2000);
    QString kernel = procKernel.readAllStandardOutput().trimmed();

    auto row = [v](const QString &label, const QString &value) {
        QFrame *f = new QFrame();
        f->setStyleSheet("QFrame { background: rgba(255,255,255,8%); border-radius: 12px; padding: 12px; }");
        QHBoxLayout *h = new QHBoxLayout(f);
        QLabel *l = new QLabel(label);
        l->setStyleSheet("color: white; background: transparent; font-size: 14px;");
        QLabel *val = new QLabel(value);
        val->setStyleSheet("color: #4fc3f7; background: transparent; font-size: 14px;");
        h->addWidget(l);
        h->addStretch();
        h->addWidget(val);
        v->addWidget(f);
    };

    row("OS", os);
    row("Kernel", kernel);
    row("Version", "ForxoOS 2.0.0");
    row("Desktop", "Deepin DDE + iOS Shell");
    v->addStretch();
    return page;
}

void IOSSettings::setupUI()
{
    setStyleSheet("IOSSettings { background: transparent; }");
    QHBoxLayout *main = new QHBoxLayout(this);
    main->setContentsMargins(20, 20, 20, 20);
    main->setSpacing(20);

    // Left menu (iOS settings style)
    QWidget *menuWrap = new QWidget();
    menuWrap->setFixedWidth(260);
    menuWrap->setStyleSheet("background: transparent;");
    QVBoxLayout *ml = new QVBoxLayout(menuWrap);
    ml->setContentsMargins(0, 0, 0, 0);

    QLabel *title = new QLabel("Settings");
    title->setStyleSheet("color: white; font-size: 24px; font-weight: bold; background: transparent;");
    ml->addWidget(title);

    menu = new QListWidget();
    menu->setStyleSheet(
        "QListWidget { background: rgba(255,255,255,6%); color: white; border: none; "
        "border-radius: 16px; font-size: 15px; padding: 8px; }"
        "QListWidget::item { padding: 12px; border-radius: 10px; }"
        "QListWidget::item:selected { background: rgba(79,195,247,40%); }"
    );
    menu->addItem("⚙️  General");
    menu->addItem("🖥️  Display");
    menu->addItem("ℹ️  About");
    menu->setCurrentRow(0);
    ml->addWidget(menu);

    main->addWidget(menuWrap);

    // Right content
    QFrame *contentFrame = new QFrame();
    contentFrame->setStyleSheet("QFrame { background: rgba(255,255,255,5%); border-radius: 16px; }");
    QVBoxLayout *cl = new QVBoxLayout(contentFrame);
    cl->setContentsMargins(16, 16, 16, 16);

    stack = new QStackedWidget();
    stack->addWidget(createGeneralPage());
    stack->addWidget(createDisplayPage());
    stack->addWidget(createAboutPage());
    cl->addWidget(stack);

    main->addWidget(contentFrame, 1);

    connect(menu, &QListWidget::currentRowChanged, stack, &QStackedWidget::setCurrentIndex);
}
