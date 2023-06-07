#include "graphicsview.h"

#include "scene.h"
#include "seriitem.h"


#include "series/series.h"

namespace Chart {

GraphicsView::GraphicsView(Series::Series *_series)
    :mSeries(_series)
{

    this->setViewportUpdateMode(FullViewportUpdate);
    setDragMode(DragMode::ScrollHandDrag);

    mScene = new Scene();

    this->setScene(mScene);

    int i = 0;
    int j = 0;
    int ypos = 0;
    for( const auto &seri : mSeries->seriList() ){
        auto mSeri3m = new SeriItem(seri);
        mScene->addItem(mSeri3m);

        if( j % 2 == 0 ){
            mSeri3m->setPos(0,i*(mSeri3m->boundingRect().height()+10));
            ypos = i*(mSeri3m->boundingRect().height()+10);
        }else{
            mSeri3m->setPos(100*7+100 + 10,ypos);
        }
        j++;
        if( j >= 2 ){
            i++;
            j = 0;
        }
    }

}

} // namespace Chart
