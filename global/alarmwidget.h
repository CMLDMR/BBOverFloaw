#ifndef GLOBAL_ALARM_ALARMWIDGET_H
#define GLOBAL_ALARM_ALARMWIDGET_H

#include <QWidget>
#include <QSoundEffect>
#include <QTimer>

class QHBoxLayout;
class QVBoxLayout;
class QLabel;

namespace Global {
namespace Alarm {

class AlarmWidget : public QWidget
{
public:

    static AlarmWidget* instance();


    void popUpMessage( const QString &msg );

signals:


private:
    explicit AlarmWidget(QWidget *parent = nullptr);

    static AlarmWidget* mAlarmWidget;
    QVBoxLayout* mLayout;

    QSoundEffect mPlaySound;
    void playSound();

    QTimer* mTimer;
    int counterToClose{0};

    int mWidth;
    int mHeight;

    QLabel* mMessageLabel;

};

} // namespace Alarm
} // namespace Global

#endif // GLOBAL_ALARM_ALARMWIDGET_H
