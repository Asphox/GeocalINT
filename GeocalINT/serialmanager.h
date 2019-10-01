#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <iostream>

class SerialManager : public QObject
{
    Q_OBJECT
public:

    explicit SerialManager(QObject *parent = nullptr);
    ~SerialManager();

    bool connect(const QString& name, const QString& baudrate );
    void disconnect();

    QStringList   getAvailablePorts(bool enableFilterACM_COM = false) const;
    QStringList   getAvailableBaudrates() const;

private:
    QSerialPort   serialPort;
    QByteArray    receiveBuffer;

signals:
    void dataReceived(QByteArray);

public slots:

private slots:
    void onReadyRead();

};

#endif // SERIALMANAGER_H
