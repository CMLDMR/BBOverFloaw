#ifndef SESSION_SESSIONMANAGER_H
#define SESSION_SESSIONMANAGER_H

#include <QJsonObject>
#include <QString>
#include <QStringList>

namespace Session {

class SessionManager
{
public:

    static Session::SessionManager* instance();

    bool saveDialog();

    bool openSessionDialog();

    bool save( const QString &sessionPath );
    bool load( const QString &sessionPath );

    QString getCurrentSessionPath() const;

    void addPair( const QString &pair );

    bool pairContains( const QString &pair );

    int pairListSize() const;
    QString pairName( const int &index ) const;
    bool removePair( const QString &pairName );


private:
    SessionManager();


    QString mSessionPath;
    QJsonObject mSessionObj;

    static SessionManager* mSessionManager;
};

} // namespace Session

#endif // SESSION_SESSIONMANAGER_H
