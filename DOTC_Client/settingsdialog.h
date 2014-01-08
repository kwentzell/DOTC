#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include "dotcsettings.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
    
private slots:
    void on_buttonBox_accepted();

private:
    Ui::SettingsDialog *    ui;
    DOTCSettings            mSettings;
};

#endif // SETTINGSDIALOG_H
