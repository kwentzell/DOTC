#ifndef ADDCHANNEL_H
#define ADDCHANNEL_H

#include <QDialog>

namespace Ui {
class AddChannel;
}

class AddChannel : public QDialog
{
    Q_OBJECT

public:
    explicit AddChannel(QWidget *parent = 0);
    ~AddChannel();

    void getParameters(QString& channelName);

private:
    Ui::AddChannel *ui;
};

#endif // ADDCHANNEL_H
