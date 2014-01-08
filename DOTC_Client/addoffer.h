#ifndef ADDOFFER_H
#define ADDOFFER_H

#include <QDialog>

namespace Ui {
class AddOffer;
}

class AddOffer : public QDialog
{
    Q_OBJECT

public:
    explicit AddOffer(QStringList channels, QString channelName, QWidget *parent = 0);
    ~AddOffer();

    void getParameters(double& amount,double& pricePcs, QString& paymentMethod, QString& channel);

private:
    Ui::AddOffer *ui;
};

#endif // ADDOFFER_H
