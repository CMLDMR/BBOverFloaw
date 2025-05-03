#ifndef TELEGRAMMANAGER_H
#define TELEGRAMMANAGER_H

#include <QObject>
#include <queue>

// This chat
//  ├ id: -4667449481
//  ├ title: Monitoring
//  ├ type: group
//  └ all_members_are_administrators: true



// Done! Congratulations on your new bot. You will find it at t.me/werawsdfsadfgbot.
// You can now add a description, about section and profile picture for your bot,
// see /help for a list of commands. By the way, when you've finished creating your cool bot,
// ping our Bot Support if you want a better username for it.
// Just make sure the bot is fully operational before you do this.

// Use this token to access the HTTP API:
// 7754649251:AAFNR4Ib-jsg4cQpIcd2HcVCVf2-8B-j4jA
// Keep your token secure and store it safely, it can be used by anyone to control your bot.

// For a description of the Bot API, see this page: https://core.telegram.org/bots/api

namespace TgBot {
class Bot;
}

class QThread;
class QTimer;

class TelegramManager : public QObject
{
    Q_OBJECT
public:
    static TelegramManager* instance();


public Q_SLOTS:
    void sendMessage( const std::string &from , const std::string &message );
    void sendPhoto(const std::string &photoPath , const std::string &photoMimeType = "image/jpeg");
    void initTgBot();
    void checkMessageToSend();

Q_SIGNALS:


private Q_SLOTS:
    void sendMessagetoTg( const std::string &from , const std::string &message );
    void sendPhototoTg(const std::string &photoPath , const std::string &photoMimeType = "image/jpeg");

private:
    static TelegramManager* m_instance;
    explicit TelegramManager(QObject *parent = nullptr);

    TgBot::Bot*  m_telegramBot;
    const std::int64_t chatId { -1002657073408 };
    const std::string token{ "8133638457:AAGGzBbJ6FDdvF5JwgDFJg154e0eKpgSKTE" };

private:
    QThread* m_thread;
    QTimer *m_timer;

    std::queue<std::tuple<std::string,std::string>> m_messageQue;
    std::queue<std::tuple<std::string,std::string>> m_photoQue;

};

#endif // TELEGRAMMANAGER_H
