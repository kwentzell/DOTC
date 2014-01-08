#include "dotcsettings.h"

DOTCSettings::DOTCSettings(QObject *parent) :
    QObject(parent)
{
}

bool DOTCSettings::isConfigured()
{
    if(getBMAPIUsername() == "default")
    {
        return false;
    }
    else
    {
        return true;
    }
}

void DOTCSettings::setToDefault()
{
    setBMAPIUsername("default");
    setBMAPIPassword("default");
    setBMIP("localhost");
    setBMPort(8442);
    setMyBMAddress("default");
    setBMChannelList(QMap<QString,QString>());
    setDBHostName("localhost");
    setDBName("dotc.db.sqlite");
    setDBUsername("DOTCUser");
    setDBPassword("password");
}

void DOTCSettings::setBMAPIUsername(QString username)
{
    mSettings.setValue("BMAPIUsername", username);
}

QString DOTCSettings::getBMAPIUsername()
{
    return(mSettings.value("BMAPIUsername").toString());
}

void DOTCSettings::setBMAPIPassword(QString password)
{
    mSettings.setValue("BMAPIPassword", password);
}

QString DOTCSettings::getBMAPIPassword()
{
    return(mSettings.value("BMAPIPassword").toString());
}

void DOTCSettings::setBMIP(QString ip)
{
    mSettings.setValue("BMIP", ip);
}

QString DOTCSettings::getBMIP()
{
    return(mSettings.value("BMIP").toString());
}

void DOTCSettings::setBMPort(quint16 port)
{
    mSettings.setValue("BMPort", port);
}

quint16 DOTCSettings::getBMPort()
{
    return(mSettings.value("BMPort").toUInt());
}

void DOTCSettings::setMyBMAddress(QString address)
{
    mSettings.setValue("MyBMAddress", address);
}

QString DOTCSettings::getMyBMAddress()
{
    return(mSettings.value("MyBMAddress").toString());
}


void DOTCSettings::setBMChannelList(QMap<QString,QString> channels)
{
    mSettings.beginWriteArray("BMChannels");

    QMapIterator<QString, QString> i(channels);
    int c = 0;
     while (i.hasNext()) {
         i.next();
         mSettings.setArrayIndex(c);
         mSettings.setValue("name", i.key());
         mSettings.setValue("address", i.value());
         c++;
     }
     mSettings.endArray();
}

QMap<QString,QString> DOTCSettings::getBMChannelList()
{
    QMap<QString,QString> lBMChannelList;

    int lSize = mSettings.beginReadArray("BMChannels");
    for (int i = 0; i < lSize; ++i) {
        mSettings.setArrayIndex(i);
        lBMChannelList.insert(mSettings.value("name").toString(),mSettings.value("address").toString());
    }
    mSettings.endArray();

    return(lBMChannelList);
}

void DOTCSettings::addChannel(QString channelName, QString bmAddress)
{
    QMap<QString,QString> lBMChannelList = getBMChannelList();
    lBMChannelList.insert(channelName,bmAddress);
    setBMChannelList(lBMChannelList);
}


void DOTCSettings::setCurrentChannel(quint16 currentChannel)
{
    mSettings.setValue("CurrentChannel", currentChannel);
}

quint16 DOTCSettings::getCurrentChannel()
{
    return(mSettings.value("CurrentChannel").toUInt());
}

void DOTCSettings::setDBHostName(QString hostName)
{
    mSettings.setValue("dbHostName", hostName);
}

QString DOTCSettings::getDBHostName()
{
    return(mSettings.value("dbHostName").toString());
}

void DOTCSettings::setDBName(QString dbName)
{
    mSettings.setValue("dbName", dbName);
}

QString DOTCSettings::getDBName()
{
    return(mSettings.value("dbName").toString());
}

void DOTCSettings::setDBUsername(QString username)
{
    mSettings.setValue("dbUsername", username);
}

QString DOTCSettings::getDBUsername()
{
    return(mSettings.value("dbUsername").toString());
}

void DOTCSettings::setDBPassword(QString password)
{
    mSettings.setValue("dbPassword", password);
}

QString DOTCSettings::getDBPassword()
{
    return(mSettings.value("dbPassword").toString());
}

