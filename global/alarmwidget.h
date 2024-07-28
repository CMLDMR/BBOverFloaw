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
    Q_OBJECT
public:
    explicit AlarmWidget(QWidget *parent = nullptr);

    static AlarmWidget* instance( QWidget * parent = nullptr );


public slots:
    void popUpMessage( const QString &msg );

signals:


private:

    static AlarmWidget* mAlarmWidget;
    QVBoxLayout* mLayout;

    QSoundEffect *mPlaySound;
    void playSound();

    int counterToClose{0};

    int mWidth;
    int mHeight;

    QLabel* mMessageLabel;

    bool m_enableAlarm { false };

    qint64 m_lastAlarmed { 0 };


    // QObject interface
protected:
    virtual void timerEvent(QTimerEvent *event) override;
};

} // namespace Alarm
} // namespace Global

#endif // GLOBAL_ALARM_ALARMWIDGET_H
