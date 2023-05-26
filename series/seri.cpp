#include "seri.h"

namespace Series {

Seri::Seri(const Binance::Public::RestAPI::Symbol &smybol, QObject *parent)
    : QObject{parent}
{

}

} // namespace Series
