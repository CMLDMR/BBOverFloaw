#ifndef VOLUMEGRAPH_H
#define VOLUMEGRAPH_H

#include <QWidget>

namespace Series{
class Series;
class Seri;
};


namespace Chart {


namespace Ui {
class VolumeGraph;
}

class VolumeGraph : public QWidget
{
    Q_OBJECT

public:
    explicit VolumeGraph( Series::Series* _mSeries, QWidget *parent = nullptr);
    ~VolumeGraph();

private:
    Ui::VolumeGraph *ui;

    Series::Series* mSeries;

};
}


#endif // VOLUMEGRAPH_H
