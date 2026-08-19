#ifndef ABOUT_H
#define ABOUT_H

#include <QWidget>

class About : public QWidget
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = nullptr);
    ~About();

private:
    void setupUI();
};

#endif // ABOUT_H
