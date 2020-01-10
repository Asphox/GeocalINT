#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <GNSS/UBX/ubx.h>
#include <iostream>

#include <Utils/bytearraymanipulator.h>

//===============================
// Manages read and write opertions on the serial port
//===============================

class SerialManager : public QObject
{
    Q_OBJECT
public:

    explicit SerialManager(QObject *parent = nullptr);
    ~SerialManager();

    //=============================
    //  Connects to the port with name @name and with speed @baudrate.
    //  Returns true if the connection is successfull, false otherwise.
    //=============================
    bool connect(const QString& name, const QString& baudrate );

    //=============================
    //  Disconnects from the previously connected port
    //=============================
    void disconnect();

    //=============================
    //  Returns a list with all available serial ports,
    //  you can pass "true" in parameter if you want to filter non "ACM" and "COM" ports
    //=============================
    QStringList   getAvailablePorts(bool enableFilterACM_COM = false) const;

    //=============================
    //  Returns a list with all baudrates supported by the system
    //=============================
    QStringList   getAvailableBaudrates() const;

    //=============================
    //  Returns the last error
    //=============================
    inline QSerialPort::SerialPortError getLastError() const { return m_serialPort.error(); }

    //=============================
    //  Returns the last error string
    //=============================
    inline QString getLastErrorString() const { return m_serialPort.errorString(); }


    //=============================
    //  Writes an raw array on the serial port
    //=============================
    inline void write(const QByteArray& rawData) { m_serialPort.write(rawData); }

private:

    QSerialPort   m_serialPort;
    QByteArray    m_receiveBuffer;
    QSerialPort::SerialPortError m_lastError = QSerialPort::SerialPortError::NoError;
    QString       m_lastErrorString = "";
    QTimer* timer_test;

private slots:

    //=============================
    //  Slot called when some data are received on the serial port
    //=============================
    void onReadyRead();

    void test();


signals:

    //=============================
    //  Signal emitted when some valid data are received
    //=============================
    void dataReceived(QByteArray);

};

#endif // SERIALMANAGER_H
