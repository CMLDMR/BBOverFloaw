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
    int lastWidth;
    for( const auto &seri : mSeries->seriList() ){
        auto mSeri3m = new SeriItem(seri);

        QObject::connect( mSeri3m , &SeriItem::updated , this , &GraphicsView::reArrageItem );

        mScene->addItem(mSeri3m);


        if( j % 2 == 0 ){
            mSeri3m->setPos(0,i*(mSeri3m->boundingRect().height()+10));
            ypos = i*(mSeri3m->boundingRect().height()+10);
        }else{
            mSeri3m->setPos(lastWidth + 10,ypos);
        }
        j++;
        if( j >= 2 ){
            i++;
            j = 0;
        }

        lastWidth = mSeri3m->boundingRect().width();

    }

}

void GraphicsView::reArrageItem()
{
    int i = 0;
    int j = 0;
    int ypos = 0;
    int lastWidth;
    for( const auto &item : this->items() ){
        if( j % 2 == 0 ){
            item->setPos(0,i*(item->boundingRect().height()+10));
            ypos = i*(item->boundingRect().height()+10);
        }else{
            item->setPos(lastWidth + 10,ypos);
        }
        j++;
        if( j >= 2 ){
            i++;
            j = 0;
        }

        lastWidth = item->boundingRect().width();
    }
}

} // namespace Chart
