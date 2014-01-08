#include "addchannel.h"
#include "ui_addchannel.h"

AddChannel::AddChannel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddChannel)
{
    ui->setupUi(this);
}

AddChannel::~AddChannel()
{
    delete ui;
}

void AddChannel::getParameters(QString& channelName)
{
    channelName = ui->lineEditChannelName->text();
}
