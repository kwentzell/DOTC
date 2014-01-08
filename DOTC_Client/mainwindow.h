#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QSqlTableModel>

#include "QDOTCSocket.h"
#include "dotcsettings.h"

namespace Ui {
class MainWindow;
}

class Channel{
public:
    QString name;       //Channel Name
    QString BMAddress;  //Bitmessage Address of the channel
    QTableView* table;
    QSqlTableModel* model;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool addChannel(QString channelName, QString channelsBMAddress);
    void removeOldOffers();

private slots:
    void on_tabWidget_currentChanged(int index);
    void on_pushButtonAddOffer_clicked();
    void on_pushButtonAddChannel_clicked();
    void on_pushButtonSettings_clicked();

    void on_pushButtonAbout_clicked();

    void on_pushButtonDelete_clicked();

private:
    //Database functions:
    bool connectToDB();
    QString getDBErrorText();
    bool addDBChannelTable(QString tableName);
    bool addDBMyOfferTable();
    bool addDBTable(QString queryString);
    bool addOffer(QString dateTime, QString channel, double amount, double pricePcs, QString paymentMethod);


    Ui::MainWindow *ui;

    DOTCSettings            mSettings;
    QNetworkAccessManager   mNetworkAccessManager;
    QDOTCSocket*            mQDOTCSocket;

    QList<Channel>          mChannels;
    Channel                 mMyOffers;
};

#endif // MAINWINDOW_H
