#ifndef QDOTC_SOCKET_H_
#define QDOTC_SOCKET_H_

#include <QObject>
#include <QHostAddress>
#include <QAuthenticator>

#include "qjsonrpchttpclient.h"
#include "qjsonrpcmessage.h"

#include "dotcsettings.h"


class QDOTCSocket  : public QJsonRpcHttpClient
{
Q_OBJECT

public:
    QDOTCSocket();
    QDOTCSocket(QNetworkAccessManager *manager);
    virtual ~QDOTCSocket();

    QString addChannel(QString name);		//Returns the corresponding Bitmessage address or "" if failed
	bool deleteChannel(QString name); //False if invalid or inexistant channel name

    bool addOffer(QString channel, double amount, double pricePcs, QString paymentMethod);
    bool removeOffer(QString channel, QString hash);
    bool renewOffer(QString hash, QString channel, double amount, double pricePcs, QString paymentMethod);

signals:
	void newOffer(QString channel, QString bmAddress, double amount, double pricePcs, QString paymentMethod);	//received a new offer
	void offerRemoved(QString channel, QString bmAddress, QString hash);

private:
    virtual void  handleAuthenticationRequired(QNetworkReply *reply, QAuthenticator * authenticator);

    DOTCSettings    mDOTCSettings;

};


#endif /* QDOTC_SOCKET_H_ */
