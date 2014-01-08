#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "addoffer.h"
#include "addchannel.h"
#include "settingsdialog.h"

#include <QMessageBox>
#include <QMap>
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QDateTime>
#include <QCryptographicHash>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->frameChannel->hide();
    if(!connectToDB())
    {
        QMessageBox::critical(this,"Error",QString(tr("Database connection failed! Maybe you have to change your settings.\n\nQt error message: %1")).arg(getDBErrorText()));
    }


    if(addDBMyOfferTable())
    {
        mMyOffers.name = "My Offers";
        mMyOffers.model = new QSqlTableModel(this,QSqlDatabase::database());
        mMyOffers.table = new QTableView;

        mMyOffers.model->setTable("myOffers");
        mMyOffers.model->setEditStrategy(QSqlTableModel::OnRowChange);
        mMyOffers.model->select();
        mMyOffers.model->setHeaderData(0, Qt::Horizontal, tr("Hash"));
        mMyOffers.model->setHeaderData(1, Qt::Horizontal, tr("UTC Date Time"));
        mMyOffers.model->setHeaderData(2, Qt::Horizontal, tr("Channel"));
        mMyOffers.model->setHeaderData(3, Qt::Horizontal, tr("Amount"));
        mMyOffers.model->setHeaderData(4, Qt::Horizontal, tr("Price/Pcs"));
        mMyOffers.model->setHeaderData(5, Qt::Horizontal, tr("Payment method"));

        mMyOffers.table->setModel(mMyOffers.model);
        mMyOffers.table->hideColumn(0);
        mMyOffers.table->show();
        mMyOffers.table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        mMyOffers.table->resizeColumnsToContents();
        mMyOffers.table->horizontalHeader()->setStretchLastSection(true);
        mMyOffers.table->setFrameShape(QFrame::NoFrame);
        mMyOffers.table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        mMyOffers.table->verticalHeader()->setVisible(false);
        mMyOffers.table->setSortingEnabled(true);
        mMyOffers.table->setSelectionMode(QAbstractItemView::SingleSelection);

        ui->tabWidget->addTab(mMyOffers.table,mMyOffers.name);
        ui->tabWidget->setTabIcon(0,QIcon(":/icons/icons/flag-blue.png"));
    }
    else
    {
        QMessageBox::critical(this,"Error",QString(tr("Database failed! Couldn't create \"My Offers\" table. Maybe you have to change your settings.\n\nQt error message: %1")).arg(getDBErrorText()));
    }


    if(!mSettings.isConfigured())       //Set some default channels
    {
        mSettings.addChannel("BTC/USD","BM-2cXMXjtRiXkYVrNAPdN1xx4BZ2fEkYMvWf");
        mSettings.addChannel("USD/BTC","BM-2cTB7Gap2zfB6E9oYzkfqgmY94whsovCZM");
    }

    QMapIterator<QString, QString> i(mSettings.getBMChannelList());
    while (i.hasNext())
    {
        i.next();
        addChannel(i.key(), i.value());
    }
    ui->tabWidget->setCurrentIndex(mSettings.getCurrentChannel());

    removeOldOffers();  //Remove offers that are older than 10 days form the databse / tables



    mQDOTCSocket = new QDOTCSocket(&mNetworkAccessManager);
    QUrl lUrl;
    lUrl.setScheme("http");
    lUrl.setHost(mSettings.getBMIP());
    lUrl.setPort(mSettings.getBMPort());
   // lUrl.setUserName(mSettings.getBMAPIUsername());
  //  lUrl.setPassword(mSettings.getBMAPIPassword());
    mQDOTCSocket->setEndPoint(lUrl);

  //lclc  mQDOTCSocket->setEndPoint("http://dotcusername:sgdfhgfnaargbdpasswordsg56eudj9wbxwe446236ggsdb@localhost:8442/");


//qDebug() << QString("%1:%2@%3").arg(apiusername,apipassword,apiinterface); //lclc RAUS
 /*   mTcpSocket.connectToHost(QString("%1:%2@%3").arg(apiusername,apipassword,apiinterface),apiport);

    mTcpSocket.connectToHost(apiinterface,apiport);
    if (!mTcpSocket.waitForConnected()) {
        qDebug() << "could not connect to server: " << mTcpSocket.errorString();
        return;
    }*/

 //   qDebug() << "mQDOTCSocket: " << mQDOTCSocket->addChannel("testlclc");
}

MainWindow::~MainWindow()
{
    mSettings.setCurrentChannel(ui->tabWidget->currentIndex());
    delete ui;
}

bool MainWindow::addChannel(QString channelName, QString channelsBMAddress)
{
    //qDebug() << "channelName: " << channelName << "channelsBMAddress: " << channelsBMAddress;
    if(addDBChannelTable(channelName))
    {
        mSettings.addChannel(channelName, channelsBMAddress);

        Channel lChannel;
        lChannel.name = channelName;
        lChannel.BMAddress = channelsBMAddress;
        lChannel.model = new QSqlTableModel(this,QSqlDatabase::database());
        lChannel.table = new QTableView;

        QString lTableName = lChannel.name;
        lTableName.replace("\/","");
        lChannel.model->setTable(lTableName);
        lChannel.model->setEditStrategy(QSqlTableModel::OnRowChange);
        lChannel.model->select();
        lChannel.model->setHeaderData(0, Qt::Horizontal, tr("Hash"));
        lChannel.model->setHeaderData(1, Qt::Horizontal, tr("Timestamp"));
        lChannel.model->setHeaderData(2, Qt::Horizontal, tr("Reputation"));
        lChannel.model->setHeaderData(3, Qt::Horizontal, tr("Amount"));
        lChannel.model->setHeaderData(4, Qt::Horizontal, tr("Price/Pcs"));
        lChannel.model->setHeaderData(5, Qt::Horizontal, tr("Payment method"));
        lChannel.model->setHeaderData(6, Qt::Horizontal, tr("Trader"));

        lChannel.table->setModel(lChannel.model);
        lChannel.table->hideColumn(0);
        lChannel.table->hideColumn(1);
        lChannel.table->hideColumn(2);  // lclc next version
        lChannel.table->show();
        lChannel.table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        lChannel.table->resizeColumnsToContents();
        lChannel.table->horizontalHeader()->setStretchLastSection(true);
        lChannel.table->setFrameShape(QFrame::NoFrame);
        lChannel.table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        lChannel.table->verticalHeader()->setVisible(false);
        lChannel.table->setSortingEnabled(true);

        mChannels.append(lChannel);
        ui->tabWidget->setCurrentIndex(ui->tabWidget->addTab(mChannels.last().table,lChannel.name));
    }
    else
    {
        QMessageBox::critical(this,"Error",QString(tr("Database failed! Couldn't create table. Maybe you have to change your settings.\n\nQt error message: %1")).arg(getDBErrorText()));
    }
}

/////////////////////////////////////////// Database stuff
bool MainWindow::connectToDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(mSettings.getDBHostName());
    db.setDatabaseName(mSettings.getDBName());
    db.setUserName(mSettings.getDBUsername());
    db.setPassword(mSettings.getDBPassword());
    return db.open();
}

QString MainWindow::getDBErrorText()
{
    QSqlDatabase db = QSqlDatabase::database();
    return db.lastError().databaseText();
}

bool MainWindow::addDBMyOfferTable()
{
    return addDBTable("CREATE TABLE IF NOT EXISTS myOffers (hash TEXT PRIMARY KEY, dateTime STRING, channel STRING, amount REAL, pricePcs REAL, paymentMethod TEXT)");
}

bool MainWindow::addDBChannelTable(QString tableName)
{
    tableName = tableName.replace("\/","");
    QString lQueryString = QString("CREATE TABLE IF NOT EXISTS %1 (hash TEXT PRIMARY KEY, timestamp INTEGER, reputation REAL, amount REAL, pricePcs REAL, paymentMethod TEXT, trader TEXT)").arg(tableName);
    return addDBTable(lQueryString);
}

bool MainWindow::addDBTable(QString queryString)
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery lQuery(db);
    if (db.isOpen())
    {
        if(lQuery.exec(queryString))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

void MainWindow::removeOldOffers()
{
    //Automatically remove offers from the database that are older than 10 days.
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery lQuery(db);

    QMapIterator<QString, QString> i(mSettings.getBMChannelList());
    while (i.hasNext())
    {
        i.next();
        QString lTableName = i.key();
        lTableName.replace("\/","");
        int lTimestampTenDaysAgo = QDateTime::currentDateTimeUtc().toTime_t()-864000;
        QString lQueryString = QString("DELETE FROM %1 WHERE timestamp < %2").arg(lTableName).arg(lTimestampTenDaysAgo);
        lQuery.exec(lQueryString);
    }

}

bool MainWindow::addOffer(QString dateTime, QString channel, double amount, double pricePcs, QString paymentMethod)
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery lQuery(db);
    if (db.isOpen())
    {
        QString lHash = QString(QCryptographicHash::hash(QString("%1%2%3%4%5%6").arg(mSettings.getMyBMAddress()).arg(dateTime).arg(channel).arg(amount).arg(pricePcs).arg(paymentMethod).toLatin1(),QCryptographicHash::Sha256).toHex());
        QString lQueryString = QString("INSERT INTO myOffers VALUES ('%1','%2','%3',%4,%5,'%6')").arg(lHash).arg(dateTime).arg(channel).arg(amount).arg(pricePcs).arg(paymentMethod);
        if(lQuery.exec(lQueryString))
        {
            mMyOffers.table->resizeColumnsToContents();
            mMyOffers.model->select();
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

/////////////////////////////////////////// END Database

/////////////////////////////////////////// UI User Events (Button clicks etc)
void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index != 0)
    {
       ui->frameMyOffers->hide();
       //ui->frameChannel->show();      //lclc Hide in 0.1
    }
    else
    {
        ui->frameMyOffers->show();
        ui->frameChannel->hide();
    }
}

void MainWindow::on_pushButtonAddOffer_clicked()
{
   QStringList lChannelNameList = mSettings.getBMChannelList().keys();
   AddOffer lAddOffer(lChannelNameList,ui->tabWidget->tabText(ui->tabWidget->currentIndex()));
   if(lAddOffer.exec() == QDialog::Accepted)
    {
        double lAmount, lPricePcs;
        QString lPaymentMethod, lChannel;
        lAddOffer.getParameters(lAmount,lPricePcs,lPaymentMethod,lChannel);

        //lclc
        //send to BM

        if(!addOffer(QDateTime::currentDateTimeUtc().toString("yyyy.mm.dd hh:mm"),lChannel,lAmount,lPricePcs,lPaymentMethod))
        {
            QMessageBox::critical(this,"Error",QString(tr("Database failed! Couldn't add offer. Maybe you have to change your settings.\n\nQt error message: %1")).arg(getDBErrorText()));
        }

    }
}

void MainWindow::on_pushButtonAddChannel_clicked()
{
   AddChannel lAddChannel;
   if(lAddChannel.exec() == QDialog::Accepted)
    {
        QString lChannelName;
        lAddChannel.getParameters(lChannelName);

        QString lChannelsBMAddress = mQDOTCSocket->addChannel(lChannelName);
        if(lChannelsBMAddress != "")
        {
            addChannel(lChannelName, lChannelsBMAddress);
        }
        else
        {
            QMessageBox::information(this,"Add Channel","Could not add new channel. Is Bitmessage running?");
        }
    }
}

void MainWindow::on_pushButtonSettings_clicked()
{
    SettingsDialog lSettingsDialog;
    if(lSettingsDialog.exec() == QDialog::Accepted)
    {
        QMessageBox::information(this,"DOTC Settings","The new settings will take effct after a restart of the application.");
    }
}
/////////////////////////////////////////// END UI User Events


void MainWindow::on_pushButtonAbout_clicked()
{
    QMessageBox::about (this, "About", "For informations and help see:\n<a href=\"www.dotc.com\">www.dotc.com</a>");
}

void MainWindow::on_pushButtonDelete_clicked()
{
    //lclc remove Offer BM schicke
 //   bool removeOffer(QString channel, QString hash);

    mMyOffers.model->removeRow(mMyOffers.table->currentIndex().row());
    mMyOffers.model->select();
}
