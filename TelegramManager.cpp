#include "TelegramManager.h"

#include <mutex>

#include <QThread>
#include <QTimer>

#include <tgbot/tgbot.h>
#include "Logger.h"

TelegramManager *TelegramManager::m_instance{nullptr};
std::once_flag m_flag;

TelegramManager::TelegramManager(QObject *parent)
    : QObject{parent}
{
    m_thread = new QThread( this );
    connect( m_thread , &QThread::started , this , &TelegramManager::initTgBot );
    m_thread->start();
}

TelegramManager *TelegramManager::instance()
{
    std::call_once( m_flag , [=](){
        m_instance = new TelegramManager();
    });
    return m_instance;
}

void TelegramManager::sendMessage(const std::string &from, const std::string &message)
{
    m_messageQue.push( { from , message } );
}

void TelegramManager::sendPhoto(const std::string &photoPath , const std::string &photoMimeType )
{
    m_photoQue.push( { photoPath , photoMimeType } );
}

void TelegramManager::sendMessagetoTg(const std::string &from, const std::string &message)
{
    const auto fullMessage = from + ": " + message;
    try {
        m_telegramBot->getApi().sendMessage( chatId , fullMessage );
    } catch ( TgBot::TgException& e ) {
        LOG_ERROR("Telegram Manager Error {}" , e.what() );
    }
}

void TelegramManager::sendPhototoTg(const std::string &photoPath, const std::string &photoMimeType)
{
    m_telegramBot->getApi().sendPhoto( chatId , TgBot::InputFile::fromFile(photoPath, photoMimeType) );
}

void TelegramManager::initTgBot()
{
    m_telegramBot = new TgBot::Bot( token );
    m_timer = new QTimer( this );
    m_timer->setInterval( 5000 );
    connect( m_timer , &QTimer::timeout, this , &TelegramManager::checkMessageToSend );
    m_timer->start( );

    this->sendMessage("Bot","Telegram Bot Started");
}

void TelegramManager::checkMessageToSend()
{

    if( m_messageQue.size() ) {
        const auto [ from , message ] = m_messageQue.front();
        sendMessagetoTg( from , message );
        m_messageQue.pop();
    }

    if( m_photoQue.size() ) {
        const auto [ photoPath , mimeType ] = m_photoQue.front();
        sendPhototoTg( photoPath , mimeType );
        m_photoQue.pop();
    }
}
