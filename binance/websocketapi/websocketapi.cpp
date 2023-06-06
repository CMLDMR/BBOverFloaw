#include "websocketapi.h"
#include <mutex>
#include <QJsonDocument>
#include <QJsonObject>

namespace Binance {
namespace Public {
namespace WebSocketAPI {



WebSocketAPI *WebSocketAPI::createSocket(const QString &pair)
{
    WebSocketAPI* mWebSocketAPI = new WebSocketAPI(pair);
    return mWebSocketAPI;
}

void WebSocketAPI::startAggregateStream()
{
    mThread->start(QThread::LowPriority);
}

WebSocketAPI::WebSocketAPI(const QString &pair, QObject *parent)
    : QObject{parent},mPair(pair)
{
    mThread = new QThread();
    this->moveToThread(mThread);
    QObject::connect(mThread,&QThread::started,this,&WebSocketAPI::startedSocket);
}

void WebSocketAPI::startedSocket()
{
    mSocket = new QWebSocket();

    QObject::connect(mSocket,&QWebSocket::textMessageReceived,[=](const QString &msg){
        const auto obj = QJsonDocument::fromJson(msg.toUtf8()).object();
        mLastAggregate = Aggregate(obj);
        emit receivedAggregate(mLastAggregate);
    });

    QObject::connect(mSocket,&QWebSocket::connected,[=](){
        qDebug() << __FILE__ << __LINE__ <<"Socket Connected" << mPair;
    });

    QObject::connect(mSocket,&QWebSocket::disconnected,[=](){
        qDebug() << __FILE__ << __LINE__ <<"Socket DisConnected" << mPair;
    });

    // Kline Websocket
    //mSocket->open(QUrl("wss://fstream.binance.com/ws/"+mPair.toLower()+"@kline_1m"));


    mSocket->open(QUrl("wss://fstream.binance.com/ws/"+mPair.toLower()+"@aggTrade"));

    //"wss://fstream.binance.com/ws/"+symbol+"@aggTrade"
}

} // namespace WebSocketAPI
} // namespace Public
} // namespace Binance
