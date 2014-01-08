#ifndef DOTCSETTINGS_H
#define DOTCSETTINGS_H

#include <QObject>
#include <QSettings>
#include <QMap>
#include <QHostAddress>

class DOTCSettings : public QObject
{
    Q_OBJECT
public:
    explicit DOTCSettings(QObject *parent = 0);
    

    bool isConfigured(); //check if settings have been set (no more default)
    void setToDefault();    //Set Settings to default

    //Bitmessage Settings
    void setBMAPIUsername(QString username);
    QString getBMAPIUsername();
    
    void setBMAPIPassword(QString password);
    QString getBMAPIPassword();

    void setBMIP(QString ip);
    QString getBMIP();

    void setBMPort(quint16 port);
    quint16 getBMPort();

    void setMyBMAddress(QString address);
    QString getMyBMAddress();

    void setBMChannelList(QMap<QString,QString> channels);
    QMap<QString,QString> getBMChannelList();

    void addChannel(QString channelName, QString bmAddress);
    int getNrOfChannels()   {   return getBMChannelList().size();   };

    //Database Settings
    void setDBHostName(QString hostName);
    QString getDBHostName();

    void setDBName(QString dbName);
    QString getDBName();

    void setDBUsername(QString username);
    QString getDBUsername();

    void setDBPassword(QString password);
    QString getDBPassword();

    //UI Settings
    void setCurrentChannel(quint16 currentChannel);
    quint16 getCurrentChannel();

private:
    QSettings mSettings;
};

#endif // DOTCSETTINGS_H
