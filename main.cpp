#include "mainwindow.h"

#include <QApplication>
#include <iostream>
#include "TelegramManager.h"

#include "Logger.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    setupLogger( a.applicationName().toStdString() , quill::LogLevel::TraceL3 );

    LOG_DEBUG("{}" , "." );

    TelegramManager::instance();

    MainWindow w;
    w.show();
    return a.exec();
}
