#include "graphicsview.h"

#include "scene.h"
#include "seriitem.h"


#include "series/series.h"

namespace Chart {

GraphicsView::GraphicsView(Series::Series *_series)
    :mSeries(_series)
{

    // Y eksenini Ters çevir
//    auto transform = this->transform();
//    transform.scale(1,-1);
//    this->setTransform(transform);


    mScene = new Scene();

    this->setScene(mScene);

    mScene->addItem(new SeriItem(mSeries->getSeri("1m").value()));
}

} // namespace Chart
