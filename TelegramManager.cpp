#include "TelegramManager.h"

#include <mutex>



// #include <tgbot/tgbot.h>

// TelegramManager *TelegramManager::m_instance{nullptr};
// std::once_flag m_flag;

// TelegramManager::TelegramManager(QObject *parent)
//     : QObject{parent}
// {
//     m_telegramBot = new TgBot::Bot( token );
//     // this->sendMessage("Bot","Telegram Bot Started");
// }

// TelegramManager *TelegramManager::instance()
// {
//     std::call_once( m_flag , [=](){
//         m_instance = new TelegramManager();
//     });
//     return m_instance;
// }

// void TelegramManager::sendMessage(const std::string &from, const std::string &message)
// {
//     const auto fullMessage = from + ": " + message;
//     try {
//         m_telegramBot->getApi().sendMessage( chatId , fullMessage );

//     } catch ( TgBot::TgException& e ) {
//         // LOG_ERROR("{}" , e.what() );
//             std::cout << "Telegram Manager Error: " << e.what() << std::endl;
//     }
// }
