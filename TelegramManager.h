#ifndef TELEGRAMMANAGER_H
#define TELEGRAMMANAGER_H

#include <QObject>

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

class TelegramManager : public QObject
{
    Q_OBJECT
public:
    static TelegramManager* instance();


public Q_SLOTS:
    void sendMessage( const std::string &from , const std::string &message );

Q_SIGNALS:

private:
    static TelegramManager* m_instance;
    explicit TelegramManager(QObject *parent = nullptr);

    TgBot::Bot*  m_telegramBot;
    const std::int64_t chatId { -4649625421 };
    const std::string token{ "8133638457:AAGGzBbJ6FDdvF5JwgDFJg154e0eKpgSKTE" };
};

#endif // TELEGRAMMANAGER_H
