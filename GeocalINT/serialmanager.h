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

    QStringList   getAvailablePorts(bool enableFilterACM_COM = false) const;
    QStringList   getAvailableBaudrates() const;


signals:

public slots:

};

#endif // SERIALMANAGER_H
