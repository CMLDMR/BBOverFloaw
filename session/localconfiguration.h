#ifndef SESSION_LOCALCONFIGURATION_H
#define SESSION_LOCALCONFIGURATION_H

#include <QJsonObject>
#include <QJsonArray>


namespace Session {

class LocalConfiguration
{
public:

    static LocalConfiguration* instance();

    bool saveSessionToRecentFile( const QString &recentSessionFullPath );

private:
    LocalConfiguration();

    static LocalConfiguration* mLocalConfiguration;

    QJsonObject mConfiguration;
};

} // namespace Session

#endif // SESSION_LOCALCONFIGURATION_H
