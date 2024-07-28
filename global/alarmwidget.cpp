#include "alarmwidget.h"

#include <mutex>
#include <QApplication>
#include <QDesktopServices>
#include <QScreen>
#include <QVBoxLayout>
#include <QLabel>
#include <QDateTime>
#include <QThread>

#include <QDebug>

#define LOG qDebug() << __LINE__ << __FILE__


namespace Global {
namespace Alarm {

AlarmWidget* AlarmWidget::mAlarmWidget{nullptr};
std::once_flag mAlarmOnceFlag;
AlarmWidget *AlarmWidget::instance( QWidget * parent )
{
    std::call_once(mAlarmOnceFlag,[=](){
        mAlarmWidget = new AlarmWidget();
        mAlarmWidget->moveToThread( QThread::currentThread() );
        mAlarmWidget->setWindowFlag(Qt::WindowStaysOnTopHint);
    });

    return mAlarmWidget;
}

void AlarmWidget::popUpMessage(const QString &msg)
{

    if( ! this->isHidden() )
        return;

    m_enableAlarm = true;

    counterToClose++;

    this->mMessageLabel->setText(msg);
    auto width = QApplication::screens().first()->geometry().width();
    auto height = QApplication::screens().first()->geometry().height();

    this->setGeometry(width-mWidth,height-mHeight-40,mWidth,mHeight);

    this->show();
    this->playSound();


    // this->startTimer( 10000 );
    // QTimer::singleShot( 100 , this , [=, this](){
    // });
    // LOG;
    QTimer::singleShot( 10000 , this , [=, this](){
        mPlaySound->stop();
        this->hide();
    });
}

AlarmWidget::AlarmWidget(QWidget *parent)
    : QWidget{parent}
{
    mWidth = 300;
    mHeight = 100;
    counterToClose = 0;

    mPlaySound = new QSoundEffect( this );

    mLayout = new QVBoxLayout(this);
    this->setLayout(mLayout);

    mMessageLabel = new QLabel();
    mLayout->addWidget(mMessageLabel);

    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);

    hide();

}

void AlarmWidget::playSound()
{
    m_lastAlarmed = QDateTime::currentMSecsSinceEpoch();

    if ( mPlaySound->status() == QSoundEffect::Error ) {
        qDebug() << __LINE__ << "Error Sound Effect" << mPlaySound->status();
        return;
    }

    if( mPlaySound->isPlaying() ) {
        LOG << "is Playing";
        return;
    }
    mPlaySound->setLoopCount(1);
    mPlaySound->setVolume(1.0);
    mPlaySound->setSource(QUrl::fromLocalFile(QString("info.wav")));
    mPlaySound->play();

}

} // namespace Alarm
} // namespace Global


void Global::Alarm::AlarmWidget::timerEvent(QTimerEvent *event)
{
    if ( mPlaySound->isPlaying() )
        mPlaySound->stop();

    this->hide();
}
