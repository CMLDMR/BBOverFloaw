#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSoundEffect>

class QVBoxLayout;

namespace ExchangeInfo{
class ExchangeInfo;
}

namespace Main {
class ViewPort;
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    ExchangeInfo::ExchangeInfo* mExchangeInfo;

    Main::ViewPort* mViewPort;

    QSoundEffect mPlaySound;


};
#endif // MAINWINDOW_H
