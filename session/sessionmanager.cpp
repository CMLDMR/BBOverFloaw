#include "sessionmanager.h"

#include <mutex>

#include <QFileDialog>
#include <QFile>
#include <QDataStream>

#include <QJsonObject>
#include <QJsonArray>


namespace Session {


std::once_flag mSessionIntanceFlag;
SessionManager* SessionManager::mSessionManager{nullptr};


SessionManager *SessionManager::instance()
{
    std::call_once(mSessionIntanceFlag,[=](){
        mSessionManager = new SessionManager();
    });
    return mSessionManager;
}

bool SessionManager::saveDialog()
{
    auto mFileName = QFileDialog::getSaveFileName(nullptr,"Save Session");
    mFileName.append(".cxs");
    return this->save(mFileName);
}

bool SessionManager::openSessionDialog()
{
    auto mFileName = QFileDialog::getOpenFileName(nullptr,"Open Session","","*.cxs");
    return load(mFileName);
}

bool SessionManager::save(const QString &sessionPath)
{

    QFile file(sessionPath);

    if( file.exists() ){
        if( !file.remove() ){
            // TODO: impleteamation for error code
            qDebug() << "File Can Not Be Removed For Replaced";
            return false;
        }
    }
    if( file.open(QIODevice::WriteOnly) ){
        QDataStream out( &file );
        out << mSessionObj;
        file.close();
        mSessionPath = sessionPath;
        return true;
    }else{
        return false;
    }
}

bool SessionManager::load(const QString &sessionPath)
{
    QFile file(sessionPath);
    if( !file.exists() ){
        return false;
    }
    if( file.open(QIODevice::ReadOnly) ){
        QDataStream in(&file);
        while (mSessionObj.keys().size()) {
            mSessionObj.remove(mSessionObj.keys().first());
        }
        in >> mSessionObj;
        file.close();
        mSessionPath = sessionPath;
        return true;
    }else{
        return false;
    }
}

QString SessionManager::getCurrentSessionPath() const
{
    return mSessionPath;
}

void SessionManager::addPair(const QString &pair)
{
    if( mSessionObj.contains("pairList") ){
        auto ar = mSessionObj.value("pairList").toArray();
        ar.append(pair);
        mSessionObj.insert("pairList",ar);
    }else{
        QJsonArray ar;
        ar.append(pair);
        mSessionObj.insert("pairList",ar);
    }
}

bool SessionManager::pairContains(const QString &pair)
{
    if( mSessionObj.contains("pairList") ){
        auto ar = mSessionObj.value("pairList").toArray();
        bool exist = false;

        for( const auto &item : ar ){
            if( item.toString() == pair ){
                exist = true;
                break;
            }
        }
        return exist;
    }else{
        return false;
    }
}

int SessionManager::pairListSize() const
{
    if( mSessionObj.contains("pairList") ){
        auto ar = mSessionObj.value("pairList").toArray();
        return ar.size();
    }else{
        return 0;
    }
}

QString SessionManager::pairName(const int &index) const
{
    if( mSessionObj.contains("pairList") ){
        auto ar = mSessionObj.value("pairList").toArray();
        if( index < ar.size() && index >= 0 ){
            return ar.at(index).toString();
        }
        return "";
    }else{
        return "";
    }
}

bool SessionManager::removePair(const QString &pairName)
{
    if( mSessionObj.contains("pairList") ){
        bool removed = false;
        auto ar = mSessionObj.value("pairList").toArray();
        if( !ar.contains(QJsonValue(pairName)) ){
            return false;
        }
        for( int i = 0 ; i < ar.size() ; i++ ){
            if( ar.at(i).toString() == pairName ){
                ar.removeAt(i);
                removed = true;
                break;
            }
        }
        return removed;
    }else{
        return false;
    }
}

SessionManager::SessionManager()
{

}



} // namespace Session
