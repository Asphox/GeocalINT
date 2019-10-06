#include "serialmanager.h"

SerialManager::SerialManager(QObject *parent) : QObject(parent)
{
    serialPort.setDataBits(QSerialPort::Data8);
    serialPort.setParity(QSerialPort::Parity::NoParity);
    serialPort.setStopBits(QSerialPort::StopBits::OneStop);
    serialPort.setFlowControl(QSerialPort::FlowControl::NoFlowControl);

    //QObject::connect(&serialPort,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
    QObject::connect(&serialPort,&QSerialPort::readyRead,this,&SerialManager::onReadyRead);
}

bool SerialManager::connect(const QString& name, const QString& baudrate)
{
    serialPort.setPortName(name);
    serialPort.setBaudRate(baudrate.toInt());

    bool r = serialPort.open(QIODevice::ReadWrite);
    //serialPort.setDataTerminalReady(true);
    std::cout << serialPort.error() << std::endl;
    return r;
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

void SerialManager::onReadyRead()
{
    QByteArray rawData = serialPort.readAll();
    receiveBuffer.append(rawData);
    if( receiveBuffer[receiveBuffer.size()-2] == '\r' && rawData[receiveBuffer.size()-1] == '\n' )
    {
        std::cout << rawData.toStdString() << std::endl;
        receiveBuffer.remove(receiveBuffer.size()-2,2);
        emit dataReceived(receiveBuffer);
        receiveBuffer.clear();
    }
}

SerialManager::~SerialManager()
{
    disconnect();
}
