#ifndef SERIES_SERIES_H
#define SERIES_SERIES_H

#include <QObject>

namespace Series {

class Series : public QObject
{
    Q_OBJECT
public:
    explicit Series(QObject *parent = nullptr);

signals:

};

} // namespace Series

#endif // SERIES_SERIES_H
