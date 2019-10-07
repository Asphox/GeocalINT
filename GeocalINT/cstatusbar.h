#ifndef CSTATUSBAR_H
#define CSTATUSBAR_H

#include <QStatusBar>
#include <QComboBox>
#include <QPushButton>
#include <QThread>
#include <ccombobox.h>
#include <cserialstatus.h>
#include <serialmanager.h>


//========================
//  Widget for the bottom status bar, with all serial connection parameter
//========================
class CStatusBar : public QStatusBar
{
    Q_OBJECT
public:
    CStatusBar(SerialManager* serialManager, QWidget* parent = nullptr);

private:
    CComboBox       m_serialPortList;
    QComboBox       m_serialBaudrate;
    QPushButton     m_connectDisconnect;
    CSerialStatus   m_serialStatus;

    SerialManager*  m_serialManager;

private slots:

    //================================
    //  Slots called when an update occures in the serial port list
    //================================
    void updateSerialPortList();

    //================================
    //  Slots called when an update occures in the serial baudrate list
    //================================
    void updateSerialBaudrateList();

    //================================
    //  Slots called to update connect and disconnect button
    //================================
    void updateConnectDisconnect();

    //================================
    //  Slols called when connect and disconnect button pressed
    //================================
    void onConnectDisconnectPressed();

    //================================
    //  Slots called when data are received (blinking led)
    //================================
    void onSerialDataReceived(QByteArray);

};

#endif // CSTATUSBAR_H
