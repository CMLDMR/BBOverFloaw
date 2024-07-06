#include "VolumeGraph.h"
#include "ui_VolumeGraph.h"

Chart::VolumeGraph::VolumeGraph(Series::Series *_mSeries, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VolumeGraph),
    mSeries(_mSeries)
{
    ui->setupUi(this);

    this->setWindowTitle("Volume Chart");



}

Chart::VolumeGraph::~VolumeGraph()
{
    delete ui;
}
