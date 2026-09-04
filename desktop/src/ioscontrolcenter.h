#ifndef IOSCONTROLCENTER_H
#define IOSCONTROLCENTER_H

#include <QWidget>
#include <QSlider>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>

class IOSControlCenter : public QWidget
{
    Q_OBJECT

public:
    explicit IOSControlCenter(QWidget *parent = nullptr);

private:
    void setupUI();
    QWidget *makeToggle(const QString &icon, const QString &label, bool active);
    QGridLayout *grid;

    QSlider *brightnessSlider;
    QSlider *volumeSlider;
};

#endif // IOSCONTROLCENTER_H
