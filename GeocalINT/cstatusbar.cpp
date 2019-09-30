#include "cstatusbar.h"

CStatusBar::CStatusBar(SerialManager* serialManager, QWidget* parent)
    :QStatusBar(parent)
    ,serialManager(serialManager)
{
    CB_serialPortList.setParent(parent);
    addWidget(&CB_serialPortList);
    CB_serialBaudrate.setParent(parent);
    addWidget(&CB_serialBaudrate);
    PB_connectDisconnect.setParent(parent);
    PB_connectDisconnect.setText(tr("connect"));
    addWidget(&PB_connectDisconnect);
    LB_serialStatus.setParent(parent);
    addPermanentWidget(&LB_serialStatus);

    updateSerialPortList();
    updateSerialBaudrate();

    connect(&CB_serialPortList,SIGNAL(clicked()),this,SLOT(updateSerialPortList()));
    connect(&CB_serialPortList,SIGNAL(currentIndexChanged(int)),this,SLOT(updatePB_connectDisconnect()));
    connect(&PB_connectDisconnect,SIGNAL(clicked()),this,SLOT(updateSerialPortList()));
    connect(&PB_connectDisconnect,SIGNAL(clicked()),this,SLOT(onPB_connectDisconnectPressed()));
}

void CStatusBar::updateSerialPortList()
{
    CB_serialPortList.clear();
#ifdef CTO_ENABLE_FILTER_SERIAL_PORT_NAME
    CB_serialPortList.addItems(serialManager->getAvailablePorts(true));
#endif
#ifndef CTO_ENABLE_FILTER_SERIAL_PORT_NAME
    CB_serialPortList.addItems(serialManager->getAvailablePorts(false));
#endif
}

void CStatusBar::updateSerialBaudrate()
{
    CB_serialBaudrate.clear();
    CB_serialBaudrate.addItems(serialManager->getAvailableBaudrates());
}

void CStatusBar::updatePB_connectDisconnect()
{
    PB_connectDisconnect.setEnabled( CB_serialPortList.currentIndex() >= 0 );
}

void CStatusBar::onPB_connectDisconnectPressed()
{
    if( LB_serialStatus.getStatus() == CSerialStatus::STATUS::CONNECTED )
    {
        PB_connectDisconnect.setText(tr("connect"));
        CB_serialBaudrate.setEnabled(true);
        CB_serialPortList.setEnabled(true);
        LB_serialStatus.setStatus(CSerialStatus::STATUS::DISCONNECTED);
        serialManager->disconnect();
    }
    else
    {
        if( serialManager->connect(CB_serialPortList.currentText(),CB_serialBaudrate.currentText()) )
        {
            PB_connectDisconnect.setText(tr("disconnect"));
            CB_serialBaudrate.setEnabled(false);
            CB_serialPortList.setEnabled(false);
            LB_serialStatus.setStatus(CSerialStatus::STATUS::CONNECTED);
        }
    }
}
