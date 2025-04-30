#ifndef SERIES_SERIES_H
#define SERIES_SERIES_H

#include <QObject>
#include <QImage>
#include <QPainter>

#include "seri.h"
#include "binance/websocketapi/websocketapi.h"

#include <optional>


namespace Series {

class Series : public QObject
{
    Q_OBJECT
public:
    explicit Series(const QString &_mPair, QObject *parent = nullptr);

    QVector<Seri*> seriList() const;

    const double &close() const;

    QString timeStr() const;

    QString pair() const;

    std::optional<Seri*> getSeri( const QString &interval );

    QImage *image() const;

    double getM5MinunteUpperPercent() const;

    double allUpperPercent() const;

    double getM15MinunteUpperPercent() const;

    double getM1HinunteUpperPercent() const;

    double getM4HinunteUpperPercent() const;

    double getM1DinunteUpperPercent() const;

    double getM5MDownPercent() const;

    double getM15MDownPercent() const;
    double getM1HDownPercent() const;
    double getM4HDownPercent() const;
    double getM1DDownPercent() const;
    double allDownPercent() const;

    int upperGreenCount() const;

    int downGreenCount() const;

    double allUpperSumPercent() const;

    double allDownSumPercent() const;

    double getM5MinuntePercent() const;

    double getM15MinuntePercent() const;

    double getM1HinuntePercent() const;

    double getM4HinuntePercent() const;

    double getM1DinuntePercent() const;

    double getM12HinuntePercent() const;

    double getM12HinunteUpperPercent() const;

    double getM12HDownPercent() const;

    ///
    /// \brief getAllBarPercentAndColorCount, L/S/N, Percent, GreenCount, RedCount
    /// \return
    ///
    std::tuple<double,double,double> getAllBarPercentAndColorCount();

    double open() const;

    double getM1MinunteSMA200Percent() const;
    double getM5MinunteSMA200Percent() const;
    double getM15MinunteSMA200Percent() const;
    double getM1HinunteSMA200Percent() const;
    double getM4HinunteSMA200Percent() const;
    double getM12HinunteSMA200Percent() const;
    double getM1DinunteSMA200Percent() const;

    double getM1MinunteEMA200Percent() const;
    double getM5MinunteEMA200Percent() const;
    double getM15MinunteEMA200Percent() const;
    double getM1HinunteEMA200Percent() const;
    double getM4HinunteEMA200Percent() const;
    double getM12HinunteEMA200Percent() const;
    double getM1DinunteEMA200Percent() const;

    double getM1MinunteEMA20Percent() const;
    double getM5MinunteEMA20Percent() const;
    double getM15MinunteEMA20Percent() const;
    double getM1HinunteEMA20Percent() const;
    double getM4HinunteEMA20Percent() const;
    double getM12HinunteEMA20Percent() const;
    double getM1DinunteEMA20Percent() const;

    double getM1WinunteEMA20Percent() const;

    double getM1MinunteUpperPercent() const;

    double getM1MinuntePercent() const;

    double getM1MDownPercent() const;

    void setEnableBBD1minuteAlarm(bool newEnableBBD1minuteAlarm);

    bool enableBBD1minuteAlarm() const;

    bool enableBBD5minuteAlarm() const;
    void setEnableBBD5minuteAlarm(bool newEnableBBD5minuteAlarm);

    bool enableBBD15minuteAlarm() const;
    void setEnableBBD15minuteAlarm(bool newEnableBBD15minuteAlarm);

    bool enableBBD1hourAlarm() const;
    void setEnableBBD1hourAlarm(bool newEnableBBD1hourAlarm);

    bool enableBBD4hourAlarm() const;
    void setEnableBBD4hourAlarm(bool newEnableBBD4hourAlarm);

    bool enableBBD1dayAlarm() const;
    void setEnableBBD1dayAlarm(bool newEnableBBD1dayAlarm);

    double getM15MinunteRSI() const;

    double getM1MinunteRSI() const;
    double getM5MinunteRSI() const;
    double getM1HourRSI() const;
    double getM4HourRSI() const;
    double getM12HourRSI() const;
    double getM1DayRSI() const;
    double getM1WeekRSI() const;

    double getMaboveTotalHourRSI() const;

signals:
    void dataUpdated(const bool&);

    void alarmed( const QString &);

    void aggregateSignal( const Binance::Public::WebSocketAPI::Aggregate &);


private:
    QString mPair;
    QVector<Seri*> mSeriList;
    Binance::Public::WebSocketAPI::WebSocketAPI* mSocket;

    QImage m_alarmImage;

    bool mViewOnlyPositive{true};

    QThread* mThread;
    void SocketWorker();

    double mClose;
    double mOpen;
    QString mTimeStr;
    qint64 mLastTimeForEmitSignal{0};

    QImage* mImage{nullptr};
    QPainter* mPainter;
    void prePareImage( QPainter* painter );
    bool mAlarmActivated{false};

    double m1MinunteUpperPercent{0};
    double m5MinunteUpperPercent{0};
    double m15MinunteUpperPercent{0};
    double m1HinunteUpperPercent{0};
    double m4HinunteUpperPercent{0};
    double m12HinunteUpperPercent{0};
    double m1DinunteUpperPercent{0};
    double mAllUpperPercent{0};
    double mAllUpperSumPercent{0};

    int mUpperGreenCount{0};

    double m1MDownPercent{0};
    double m5MDownPercent{0};
    double m15MDownPercent{0};
    double m1HDownPercent{0};
    double m4HDownPercent{0};
    double m12HDownPercent{0};
    double m1DDownPercent{0};
    double mAllDownPercent{0};
    double mAllDownSumPercent{0};
    int mDownGreenCount{0};

    double m1MinuntePercent{0};
    double m5MinuntePercent{0};
    double m15MinuntePercent{0};
    double m1HinuntePercent{0};
    double m4HinuntePercent{0};
    double m12HinuntePercent{0};
    double m1DinuntePercent{0};

    double mAllBarPercentSum{0};
    int mAllBarGreenCount{0};
    int mAllBarRedCount{0};

    int m_length { 41 };
    double m1MinunteSMA200Percent{0};
    double m5MinunteSMA200Percent{0};
    double m15MinunteSMA200Percent{0};
    double m1HinunteSMA200Percent{0};
    double m4HinunteSMA200Percent{0};
    double m12HinunteSMA200Percent{0};
    double m1DinunteSMA200Percent{0};

    double m1MinunteEMA200Percent{0};
    double m5MinunteEMA200Percent{0};
    double m15MinunteEMA200Percent{0};
    double m1HinunteEMA200Percent{0};
    double m4HinunteEMA200Percent{0};
    double m12HinunteEMA200Percent{0};
    double m1DinunteEMA200Percent{0};



    double m1MinunteEMA20Percent{0};
    double m5MinunteEMA20Percent{0};
    double m15MinunteEMA20Percent{0};
    double m1HinunteEMA20Percent{0};
    double m4HinunteEMA20Percent{0};
    double m12HinunteEMA20Percent{0};
    double m1DinunteEMA20Percent{0};
    double m1WinunteEMA20Percent{0};

    double m1MinunteRSI{0};
    double m3MinunteRSI{0};
    double m5MinunteRSI{0};
    double m15MinunteRSI{0};
    double m30MinunteRSI{0};
    double m1HourRSI{0};
    double maboveTotalHourRSI{0};

    double m4HourRSI{0};
    double m12HourRSI{0};
    double m1DayRSI{0};
    double m1WeekRSI{0};

    bool m_enableBBD1minuteAlarm { false };
    bool m_enableBBD5minuteAlarm { false };
    bool m_enableBBD15minuteAlarm { false };
    bool m_enableBBD1hourAlarm { false };
    bool m_enableBBD4hourAlarm { false };
    bool m_enableBBD1dayAlarm { false };




};

} // namespace Series

#endif // SERIES_SERIES_H
