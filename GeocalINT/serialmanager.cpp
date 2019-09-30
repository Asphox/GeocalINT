#include "serialmanager.h"

SerialManager::SerialManager(QObject *parent) : QObject(parent)
{
    serialPort.setDataBits(QSerialPort::Data8);
    serialPort.setParity(QSerialPort::Parity::NoParity);
    serialPort.setStopBits(QSerialPort::StopBits::OneStop);
    serialPort.setFlowControl(QSerialPort::FlowControl::NoFlowControl);
}

bool SerialManager::connect(const QString& name, const QString& baudrate)
{
    serialPort.setPortName(name);
    serialPort.setBaudRate(baudrate.toInt());
    return serialPort.open(QIODevice::ReadWrite);
}

void SerialManager::disconnect()
{
    serialPort.close();
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
