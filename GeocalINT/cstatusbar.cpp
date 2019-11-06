#include "cstatusbar.h"

CStatusBar::CStatusBar(SerialManager* serialManager, QWidget* parent)
    :QStatusBar(parent)
    ,m_serialManager(serialManager)
{
    m_serialPortList.setParent(parent);
    addWidget(&m_serialPortList);
    m_serialBaudrate.setParent(parent);
    addWidget(&m_serialBaudrate);
    m_connectDisconnect.setParent(parent);
    m_connectDisconnect.setText(tr("connect"));
    addWidget(&m_connectDisconnect);
    addPermanentWidget(&m_statusText);
    m_statusText.setText(tr("disconnected"));
    m_serialStatus.setParent(parent);
    addPermanentWidget(&m_serialStatus);

    updateSerialPortList();
    updateSerialBaudrateList();

    connect(&m_serialPortList,SIGNAL(clicked()),this,SLOT(updateSerialPortList()));
    connect(&m_serialPortList,SIGNAL(currentIndexChanged(int)),this,SLOT(updateConnectDisconnect()));
    connect(&m_connectDisconnect,SIGNAL(clicked()),this,SLOT(updateSerialPortList()));
    connect(&m_connectDisconnect,SIGNAL(clicked()),this,SLOT(onConnectDisconnectPressed()));
    connect(serialManager,SIGNAL(dataReceived(QByteArray)),this,SLOT(onSerialDataReceived(QByteArray)));

}

void CStatusBar::updateSerialPortList()
{
    m_serialPortList.clear();
#ifdef CTO_ENABLE_FILTER_SERIAL_PORT_NAME
    m_serialPortList.addItems(m_serialManager->getAvailablePorts(true));
#endif
#ifndef CTO_ENABLE_FILTER_SERIAL_PORT_NAME
    m_serialPortList.addItems(m_serialManager->getAvailablePorts(false));
#endif
}

void CStatusBar::updateSerialBaudrateList()
{
    m_serialBaudrate.clear();
    m_serialBaudrate.addItems(m_serialManager->getAvailableBaudrates());
    if(m_serialManager->getAvailableBaudrates().contains("9600"))
        m_serialBaudrate.setCurrentText("9600");
}

void CStatusBar::updateConnectDisconnect()
{
    m_connectDisconnect.setEnabled( m_serialPortList.currentIndex() >= 0 );
}

void CStatusBar::onConnectDisconnectPressed()
{
    if( m_serialStatus.getStatus() == CSerialStatus::STATUS::CONNECTED )
    {
        m_connectDisconnect.setText(tr("connect"));
        m_statusText.setText(tr("disconnected"));
        m_serialBaudrate.setEnabled(true);
        m_serialPortList.setEnabled(true);
        m_serialStatus.setStatus(CSerialStatus::STATUS::DISCONNECTED);
        m_serialManager->disconnect();
    }
    else
    {
        if( m_serialManager->connect(m_serialPortList.currentText(),m_serialBaudrate.currentText()) )
        {
            m_connectDisconnect.setText(tr("disconnect"));
            m_statusText.setText(tr("connected"));
            m_serialBaudrate.setEnabled(false);
            m_serialPortList.setEnabled(false);
            m_serialStatus.setStatus(CSerialStatus::STATUS::CONNECTED);
        }
        else
        {
            m_statusText.setText(HTMLFormat(m_serialManager->getLastErrorString(),"red"));
        }
    }
}

void CStatusBar::onSerialDataReceived(QByteArray array)
{
    (void)array;
    m_serialStatus.setStatus(CSerialStatus::STATUS::TRANSFERING);
}
