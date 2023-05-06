#ifndef EXCHANGEINFO_H
#define EXCHANGEINFO_H

#include <QWidget>



namespace Ui {
class ExchangeInfo;
}

namespace ExchangeInfo{

class ExchangeModel;

class ExchangeInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ExchangeInfo(QWidget *parent = nullptr);
    ~ExchangeInfo();

private:
    Ui::ExchangeInfo *ui;
    ExchangeModel* mModel;
};

}



#endif // EXCHANGEINFO_H
