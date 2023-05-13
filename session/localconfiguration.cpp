#include "localconfiguration.h"

#include <mutex>

#include <QFile>
#include <QDataStream>

namespace Session {

std::once_flag mLocalConfigCallOnceFlag;

LocalConfiguration* LocalConfiguration::mLocalConfiguration{nullptr};

LocalConfiguration *LocalConfiguration::instance()
{
    std::call_once(mLocalConfigCallOnceFlag,[=](){
        mLocalConfiguration = new LocalConfiguration();
    });
    return mLocalConfiguration;
}

bool LocalConfiguration::saveSessionToRecentFile(const QString &recentSessionFullPath)
{

    QFile file("config");

    if( file.exists() ){
        file.remove();
    }

    if( mConfiguration.contains("recentSession") ){
        auto ar = mConfiguration.value("recentSession").toArray();
        ar.append(recentSessionFullPath);
        mConfiguration.insert("recentSession",ar);
    }else{
        QJsonArray ar;
        ar.append(recentSessionFullPath);
        mConfiguration.insert("recentSession",ar);
    }

    mConfiguration.value("recentSession").toArray();

    if( file.open(QIODevice::WriteOnly) ){
        QDataStream out(&file);
        out <<mConfiguration;
        return true;
    }
    return false;
}

LocalConfiguration::LocalConfiguration()
{

}

} // namespace Session
