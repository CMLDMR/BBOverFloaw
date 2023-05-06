#ifndef BOLLIGNERBANDPERCENT_H
#define BOLLIGNERBANDPERCENT_H

#include <QWidget>

namespace Ui {
class BollignerBandPercent;
}

namespace Bollinger{

class NearModel;


class BollignerBandPercent : public QWidget
{
    Q_OBJECT

public:
    explicit BollignerBandPercent(QWidget *parent = nullptr);
    ~BollignerBandPercent();

private:
    Ui::BollignerBandPercent *ui;

    NearModel* mModel;
};

}


#endif // BOLLIGNERBANDPERCENT_H
