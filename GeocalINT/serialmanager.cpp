#include "serialmanager.h"

SerialManager::SerialManager(QObject *parent) : QObject(parent)
{
    m_serialPort.setDataBits(QSerialPort::Data8);
    m_serialPort.setParity(QSerialPort::Parity::NoParity);
    m_serialPort.setStopBits(QSerialPort::StopBits::OneStop);
    m_serialPort.setFlowControl(QSerialPort::FlowControl::NoFlowControl);

    QObject::connect(&m_serialPort,&QSerialPort::readyRead,this,&SerialManager::onReadyRead);
}

bool SerialManager::connect(const QString& name, const QString& baudrate)
{
    m_serialPort.setPortName(name);
    m_serialPort.setBaudRate(baudrate.toInt());

    return m_serialPort.open(QIODevice::ReadWrite);
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
    QByteArray rawData = m_serialPort.readAll();
    m_receiveBuffer.append(rawData);

    //===========================
    //  Checks if buffer terminates with \r\n to have a complete frame
    //===========================
#ifdef CTO_ENABLE_SERIAL_RAW_DISPLAY
        std::cout <<  "=======================" << std::endl
                  <<  "   RAW DATA RECEIVED   " << std::endl
                  <<   rawData.toStdString() << std::endl
                  <<  "=======================" <<std::endl;
#endif
        m_receiveBuffer.remove(m_receiveBuffer.size()-2,2);
        emit dataReceived(m_receiveBuffer);
        m_receiveBuffer.clear();

}

SerialManager::~SerialManager()
{
    disconnect();
}
