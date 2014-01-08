#include "QDOTCSocket.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QStringList>

QDOTCSocket::QDOTCSocket(QNetworkAccessManager *manager) : QJsonRpcHttpClient(manager)
{
}

QDOTCSocket::QDOTCSocket()
{
}

QDOTCSocket::~QDOTCSocket()
{

}

void QDOTCSocket::handleAuthenticationRequired(QNetworkReply *reply, QAuthenticator * authenticator) {
    Q_UNUSED(reply);
    authenticator->setUser(mDOTCSettings.getBMAPIUsername());
    authenticator->setPassword(mDOTCSettings.getBMAPIPassword());
}


QString QDOTCSocket::addChannel(QString name)
{
    QByteArray lChannelName = name.toLatin1().toBase64();

    QJsonObject lJsonObjectAddChannel;
    lJsonObjectAddChannel.insert("createChan",QString(lChannelName));

    QJsonRpcMessage lMessage(lJsonObjectAddChannel);
    QJsonRpcMessage lAnswer = sendMessageBlocking(lMessage);
/*
    QVariantList t;
    t.append("aa");
    t.append("bb");
    QJsonRpcMessage lRequest = QJsonRpcMessage::createRequest("statusBar",t);
    qDebug() << lRequest.isValid() << lRequest.method() << lRequest.params();

*/
           /* bool isValid() const;
            int id() const;

            // request
            QString method() const;
            QVariantList params() const;*/

  //  QJsonRpcMessage lAnswer  = sendMessageBlocking(lRequest);

  //  qDebug() << lAnswer.result().toStringList().at(0);

    qDebug() << "QDOTCSocket::addChannel -> " << lAnswer.result().toString() << lAnswer.errorCode() << lAnswer.errorMessage() << lAnswer.errorData().toString();
    return lAnswer.result().toString();
}

bool QDOTCSocket::deleteChannel(QString name)
{
//lclc : does leaveChan channelname also have to be in base64??
    QByteArray lChannelName = name.toLatin1().toBase64();

    QJsonObject lJsonObjectAddChannel;
    lJsonObjectAddChannel.insert("leaveChan",QString(lChannelName));

    QJsonRpcMessage lMessage(lChannelName);
    QJsonRpcMessage lAnswer = sendMessageBlocking(lMessage);
    qDebug() << "QDOTCSocket::deleteChannel -> " << lAnswer.result().toString() << lAnswer.errorMessage();
    if(lAnswer.result().toString() == "success")
    {
        return true;
    }
    else
    {
        return true;
    }
}

bool QDOTCSocket::addOffer(QString channel, double amount, double pricePcs, QString paymentMethod)
{
	QJsonObject lJsonObjectOffer;
	lJsonObjectOffer.insert("amount",amount);
	lJsonObjectOffer.insert("pricePcs",pricePcs);
	lJsonObjectOffer.insert("paymentMethod",paymentMethod);

    QJsonDocument lJsonOffer;
    lJsonOffer.setObject(lJsonObjectOffer);
    QByteArray lOffer = lJsonOffer.toJson();
//sendMessage

    QJsonRpcMessage lMessage(lJsonObjectOffer);
    QJsonRpcMessage lAnswer = sendMessageBlocking(lMessage);
    qDebug() << "QDOTCSocket::addChannel -> " << lAnswer.result().toString() << lAnswer.errorMessage();
    if(lAnswer.result().toString() == "success")
    {
        return true;
    }
    else
    {
        return true;
    }

//lclc ToDo: lOffer an $channel senden
}

bool QDOTCSocket::removeOffer(QString channel, QString hash)
{
	QJsonObject lJsonObjectRemoveOffer;
    lJsonObjectRemoveOffer.insert("remove",hash);

	QJsonDocument lJsonRemoveOffer;
	lJsonRemoveOffer.setObject(lJsonObjectRemoveOffer);
	QByteArray lRemoveOffer = lJsonRemoveOffer.toJson();

//lclc ToDo: lRemoveOffer an $channel senden
}

bool QDOTCSocket::renewOffer(QString hash, QString channel, double amount, double pricePcs, QString paymentMethod)
{
    if(removeOffer(channel, hash))
    {
        if(addOffer(channel, amount, pricePcs, paymentMethod))
        {
            return true;
        }
    }
    return false;
};

/*
###########################################################
#### newOffer (empfangen einer Offer)
QJsonDocument lJsonOffer = QJsonDocument::fromJson(QByteArray);
QJsonObject lJsonObjectOffer = QJsonOffer.object();
double lAmount = lJsonObjectOffer.value("amount").toDouble();
double lPricePcs = lJsonObjectOffer.value("pricePcs").toDouble();
QString lPaymentMethod = lJsonObjectOffer.value("paymentMethod").toString();

emit newOffer(QString channel, QString bmAddress, lAmount, lPricePcs, lPaymentMethod);


###offerRemoved (empfangen)
QJsonDocument lJsonRemoveOffer = QJsonDocument::fromJson(QByteArray);
QJsonObject lJsonObjectRemoveOffer = lJsonRemoveOffer.object();
QString lHash = lJsonObjectRemoveOffer.value("delete").toString();

emit offerRemoved(QString channel, QString bmAddress, lHash);
*/

