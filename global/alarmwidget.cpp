#include "alarmwidget.h"

#include <mutex>
#include <QApplication>
#include <QDesktopServices>
#include <QScreen>
#include <QVBoxLayout>
#include <QLabel>



namespace Global {
namespace Alarm {

AlarmWidget* AlarmWidget::mAlarmWidget{nullptr};
std::once_flag mAlarmOnceFlag;
AlarmWidget *AlarmWidget::instance()
{
    std::call_once(mAlarmOnceFlag,[=](){
        mAlarmWidget = new AlarmWidget();
        mAlarmWidget->setWindowFlag(Qt::WindowStaysOnTopHint);
    });

    return mAlarmWidget;
}

void AlarmWidget::popUpMessage(const QString &msg)
{
    if( counterToClose > 0 ) return;
    counterToClose++;

    this->mMessageLabel->setText(msg);
    auto width = QApplication::screens().first()->geometry().width();
    auto height = QApplication::screens().first()->geometry().height();

    this->setGeometry(width-mWidth,height-mHeight-40,mWidth,mHeight);
    this->show();
    this->mTimer->start(200);


    this->playSound();
}

AlarmWidget::AlarmWidget(QWidget *parent)
    : QWidget{parent}
{
    mWidth = 200;
    mHeight = 100;
    counterToClose = 0;

    mTimer = new QTimer(parent);
    QObject::connect(mTimer,&QTimer::timeout,[=](){

        counterToClose++;
        if( counterToClose >= 25 ){
            if( counterToClose == 25 ){
                this->close();
            }
            if( counterToClose > 10*5 ){
                counterToClose = 0;
                this->mTimer->stop();
            }
        }
    });

    mLayout = new QVBoxLayout(this);
    this->setLayout(mLayout);

    mMessageLabel = new QLabel();
    mLayout->addWidget(mMessageLabel);

}

void AlarmWidget::playSound()
{
    mPlaySound.setLoopCount(1);
    mPlaySound.setVolume(1.0);
    mPlaySound.setSource(QUrl::fromLocalFile(QString("info.wav")));
    mPlaySound.play();
}

} // namespace Alarm
} // namespace Global
