#include "mainwindow.h"

#include <QApplication>
#include <iostream>
#include "TelegramManager.h"

int main(int argc, char *argv[])
{
    std::cout << __FILE__ << " " <<__LINE__ << "\n";

    QApplication a(argc, argv);

    std::cout << __FILE__ << " " <<__LINE__ << "\n";

    // TelegramManager::instance();

    MainWindow w;
    std::cout << "MainWindow \n";
    w.show();
    return a.exec();
}
