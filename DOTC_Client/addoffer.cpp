#include "addoffer.h"
#include "ui_addoffer.h"

AddOffer::AddOffer(QStringList channels, QString channelName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddOffer)
{
    ui->setupUi(this);
    ui->comboBoxChannel->addItems(channels);
    ui->comboBoxChannel->setCurrentIndex(ui->comboBoxChannel->findText(channelName));
}

AddOffer::~AddOffer()
{
    delete ui;
}

void AddOffer::getParameters(double& amount,double& pricePcs, QString& paymentMethod, QString& channel)
{
    amount = ui->doubleSpinBoxAmount->value();
    pricePcs = ui->doubleSpinBoxPricePcs->value();
    paymentMethod = ui->lineEditPaymentMethod->text();
    channel = ui->comboBoxChannel->currentText();
}
