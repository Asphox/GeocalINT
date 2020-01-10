#include "serialmanager.h"

SerialManager::SerialManager(QObject *parent) : QObject(parent)
{
    m_serialPort.setDataBits(QSerialPort::Data8);
    m_serialPort.setParity(QSerialPort::Parity::NoParity);
    m_serialPort.setStopBits(QSerialPort::StopBits::OneStop);
    m_serialPort.setFlowControl(QSerialPort::FlowControl::NoFlowControl);

    QObject::connect(&m_serialPort,&QSerialPort::readyRead,this,&SerialManager::onReadyRead);

    timer_test = new QTimer(this);
    QObject::connect(timer_test,SIGNAL(timeout()),this,SLOT(test()));
}

bool SerialManager::connect(const QString& name, const QString& baudrate)
{
    m_serialPort.setPortName(name);
    m_serialPort.setBaudRate(baudrate.toInt());
    timer_test->start(500);
    return m_serialPort.open(QIODevice::ReadWrite);
}

void SerialManager::test()
{
    static int i = 1;
    if( i == 33 ) i = 1;
    QByteArray params;
    params.push_back(i);
    auto tmp = GNSS::UBXFrame::makePollMessage(GNSS::UBXFrame::ClsId::AID_EPH,params);
    //auto tmp = GNSS::UBXFrame::makePollMessage(GNSS::UBXFrame::ClsId::RXM_SFRBX);
    write(tmp);
    i++;
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

//    if( (uint8_t)rawData.at(0) == 0xB5 )
//        displayQByteArray(rawData,std::hex);

//#ifdef CTO_ENABLE_SERIAL_RAW_DISPLAY
//        std::cout <<  "=======================" << std::endl
//                  <<  "   RAW DATA RECEIVED   " << std::endl
//                  <<  rawData.toStdString() << std::endl
//                  <<  "=======================" <<std::endl;
//#endif
        if( m_receiveBuffer.at(0) == '$')
            m_receiveBuffer.remove(m_receiveBuffer.size()-2,2);
        emit dataReceived(m_receiveBuffer);
        m_receiveBuffer.clear();
        m_serialPort.clear();

}

SerialManager::~SerialManager()
{
    disconnect();
}
