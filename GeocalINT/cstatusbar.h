#ifndef CSTATUSBAR_H
#define CSTATUSBAR_H

#include <QStatusBar>
#include <QComboBox>
#include <QPushButton>
#include <QThread>
#include <ccombobox.h>
#include <cserialstatus.h>
#include <serialmanager.h>

class CStatusBar : public QStatusBar
{
    Q_OBJECT
public:
    CStatusBar(SerialManager* serialManager, QWidget* parent = nullptr);

private:
    CComboBox       CB_serialPortList;
    QComboBox       CB_serialBaudrate;
    QPushButton     PB_connectDisconnect;
    CSerialStatus   LB_serialStatus;

    SerialManager*  serialManager;

private slots:
    void updateSerialPortList();
    void updateSerialBaudrate();
    void updatePB_connectDisconnect();
    void onPB_connectDisconnectPressed();
    void onSerialDataReceived(QByteArray);

};

#endif // CSTATUSBAR_H
