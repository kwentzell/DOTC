#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QHostAddress>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    ui->lineEditMyBMAddress->setText(mSettings.getMyBMAddress());
    ui->lineEditBMAPIUsername->setText(mSettings.getBMAPIUsername());
    ui->lineEditBMAPIPassword->setText(mSettings.getBMAPIPassword());
    ui->lineEditBMIP->setText(mSettings.getBMIP());
    ui->lineEditBMPort->setText(QString::number(mSettings.getBMPort()));

    ui->lineEditDBHostname->setText(mSettings.getDBHostName());
    ui->lineEditDBName->setText(mSettings.getDBName()); //Path
    ui->lineEditDBUsername->setText(mSettings.getDBUsername());
    ui->lineEditDBPassword->setText(mSettings.getDBPassword());
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_buttonBox_accepted()
{
    mSettings.setMyBMAddress(ui->lineEditMyBMAddress->text());
    mSettings.setBMAPIUsername(ui->lineEditBMAPIUsername->text());
    mSettings.setBMAPIPassword(ui->lineEditBMAPIPassword->text());
    mSettings.setBMIP(ui->lineEditBMIP->text());
    mSettings.setBMPort(ui->lineEditBMPort->text().toUInt());

    mSettings.setDBHostName(ui->lineEditDBHostname->text());
    mSettings.setDBName(ui->lineEditDBName->text()); //Path
    mSettings.setDBUsername(ui->lineEditDBUsername->text());
    mSettings.setDBPassword(ui->lineEditDBPassword->text());
}
