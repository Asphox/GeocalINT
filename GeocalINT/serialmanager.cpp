#include "serialmanager.h"

SerialManager::SerialManager(QObject *parent) : QObject(parent)
{
    m_serialPort.setDataBits(QSerialPort::Data8);
    m_serialPort.setParity(QSerialPort::Parity::NoParity);
    m_serialPort.setStopBits(QSerialPort::StopBits::OneStop);
    m_serialPort.setFlowControl(QSerialPort::FlowControl::NoFlowControl);

    QObject::connect(&m_serialPort,&QSerialPort::readyRead,this,&SerialManager::onReadyRead);

    timer_test = new QTimer(this);
    //QObject::connect(timer_test,SIGNAL(timeout()),this,SLOT(test()));
}

bool SerialManager::connect(const QString& name, const QString& baudrate)
{
    m_serialPort.setPortName(name);
    m_serialPort.setBaudRate(baudrate.toInt());
    timer_test->start(5000);
    return m_serialPort.open(QIODevice::ReadWrite);
}

void SerialManager::test()
{
    /*static int i = 1;
    if( i == 33 ) i = 1;
    QByteArray params;
    params.push_back(i);
    auto tmp = GNSS::UBXFrame::makePollMessage(GNSS::UBXFrame::ClsId::AID_EPH,params);
    write(tmp);
    i++;*/

    auto tmp = GNSS::UBXFrame::makePollMessage(GNSS::UBXFrame::ClsId::NAV_TIMEGPS);
    write(tmp);

}

void SerialManager::disconnect()
{
    m_serialPort.close();
}

QStringList SerialManager::getAvailablePorts(bool enableFilterACM_COM) const
{
    QList<QSerialPortInfo> list = QSerialPortInfo::availablePorts();

    QStringList listName;
    for( auto it : list )
    {
        if(enableFilterACM_COM && (!it.portName().contains("ACM") && !it.portName().contains("COM")) )
            continue;
        listName.append( it.portName() );
    }

    return listName;
}

QStringList SerialManager::getAvailableBaudrates() const
{
    QList<qint32> list = QSerialPortInfo::standardBaudRates();

    QStringList listBaudrate;
    for( auto it : list )
    {
        listBaudrate.append(QString::number(it));
    }

    return listBaudrate;
}

void SerialManager::onReadyRead()
{
    //QByteArray rawData = m_serialPort.readAll();
    //m_receiveBuffer.append(rawData);

    emit dataReceived(m_serialPort.readAll());
}

SerialManager::~SerialManager()
{
    disconnect();
}
