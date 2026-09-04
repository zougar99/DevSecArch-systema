#include "installer.h"
#include "welcome.h"
#include "language.h"
#include "keyboard.h"
#include "partition.h"
#include "userinfo.h"
#include "desktop.h"
#include "summary.h"
#include "installing.h"
#include "complete.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QApplication>
#include <QMessageBox>

Installer::Installer(QWidget *parent)
    : QMainWindow(parent)
    , currentStep(0)
    , totalSteps(8)
    , eraseConfirmed(false)
{
    setWindowTitle("ForxoOS Installer");
    setFixedSize(900, 600);
    setStyleSheet("QMainWindow { background-color: #1a1a2e; }");

    setupUI();
    updateButtons();
}

Installer::~Installer()
{
}

void Installer::setupUI()
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    QFrame *header = new QFrame();
    header->setStyleSheet(
        "QFrame { background-color: #16213e; padding: 20px; }"
    );
    QVBoxLayout *headerLayout = new QVBoxLayout(header);

    titleLabel = new QLabel("ForxoOS Installer");
    titleLabel->setStyleSheet(
        "font-size: 28px; font-weight: bold; color: #2a82da; padding: 10px;"
    );

    stepLabel = new QLabel("Step 1 of 8 - Welcome");
    stepLabel->setStyleSheet("font-size: 14px; color: #888; padding-left: 10px;");

    headerLayout->addWidget(titleLabel);
    headerLayout->addWidget(stepLabel);

    mainLayout->addWidget(header);

    QFrame *contentFrame = new QFrame();
    contentFrame->setStyleSheet("QFrame { background-color: #1a1a2e; }");
    QVBoxLayout *contentLayout = new QVBoxLayout(contentFrame);
    contentLayout->setContentsMargins(30, 20, 30, 20);

    stack = new QStackedWidget();

    welcomePage = new Welcome(this);
    languagePage = new Language(this);
    keyboardPage = new Keyboard(this);
    partitionPage = new Partition(this);
    userinfoPage = new UserInfo(this);
    desktopPage = new Desktop(this);
    summaryPage = new Summary(this);
    installingPage = new Installing(this);
    completePage = new Complete(this);

    stack->addWidget(welcomePage);
    stack->addWidget(languagePage);
    stack->addWidget(keyboardPage);
    stack->addWidget(partitionPage);
    stack->addWidget(userinfoPage);
    stack->addWidget(desktopPage);
    stack->addWidget(summaryPage);
    stack->addWidget(installingPage);
    stack->addWidget(completePage);

    contentLayout->addWidget(stack);
    mainLayout->addWidget(contentFrame, 1);

    QFrame *footer = new QFrame();
    footer->setStyleSheet(
        "QFrame { background-color: #16213e; padding: 15px; }"
    );
    QHBoxLayout *footerLayout = new QHBoxLayout(footer);

    cancelBtn = new QPushButton("Cancel");
    cancelBtn->setStyleSheet(
        "QPushButton { background-color: #e74c3c; color: white; border: none; "
        "padding: 12px 30px; border-radius: 5px; font-size: 14px; font-weight: bold; }"
        "QPushButton:hover { background-color: #c0392b; }"
    );

    backBtn = new QPushButton("Back");
    backBtn->setStyleSheet(
        "QPushButton { background-color: #555; color: white; border: none; "
        "padding: 12px 30px; border-radius: 5px; font-size: 14px; font-weight: bold; }"
        "QPushButton:hover { background-color: #666; }"
        "QPushButton:disabled { background-color: #333; color: #666; }"
    );

    nextBtn = new QPushButton("Next >");
    nextBtn->setStyleSheet(
        "QPushButton { background-color: #2a82da; color: white; border: none; "
        "padding: 12px 30px; border-radius: 5px; font-size: 14px; font-weight: bold; }"
        "QPushButton:hover { background-color: #3a92ea; }"
    );

    footerLayout->addWidget(cancelBtn);
    footerLayout->addStretch();
    footerLayout->addWidget(backBtn);
    footerLayout->addWidget(nextBtn);

    mainLayout->addWidget(footer);

    connect(nextBtn, &QPushButton::clicked, this, &Installer::nextStep);
    connect(backBtn, &QPushButton::clicked, this, &Installer::prevStep);
    connect(cancelBtn, &QPushButton::clicked, qApp, &QApplication::quit);
}

void Installer::nextStep()
{
    // Step 3 = Partition page. Enforce ERASE confirmation before advancing.
    if (currentStep == 3 && !eraseConfirmed) {
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("ERASE Not Confirmed");
        msgBox.setText("You must type ERASE on the Disk page before proceeding.");
        msgBox.setInformativeText("This is a safety measure to prevent accidental data loss.\n\n"
                                   "Go back and type ERASE in the confirmation field.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    if (currentStep < totalSteps - 1) {
        currentStep++;
        stack->setCurrentIndex(currentStep);
        updateButtons();
    }
}

void Installer::prevStep()
{
    if (currentStep > 0) {
        currentStep--;
        stack->setCurrentIndex(currentStep);
        updateButtons();
    }
}

void Installer::goToStep(int step)
{
    currentStep = step;
    stack->setCurrentIndex(step);
    updateButtons();
}

void Installer::updateButtons()
{
    backBtn->setEnabled(currentStep > 0);

    if (currentStep == totalSteps - 1) {
        nextBtn->setVisible(false);
        cancelBtn->setText("Finish");
    } else if (currentStep == totalSteps - 2) {
        nextBtn->setVisible(true);
        nextBtn->setText("Install");
    } else {
        nextBtn->setVisible(true);
        nextBtn->setText("Next >");
    }

    QStringList steps = {
        "Welcome", "Language", "Keyboard", "Partition",
        "User Info", "Desktop", "Summary", "Installing", "Complete"
    };

    if (currentStep < steps.size()) {
        stepLabel->setText(QString("Step %1 of %2 - %3")
            .arg(currentStep + 1).arg(totalSteps).arg(steps[currentStep]));
    }
}
