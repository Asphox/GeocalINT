#ifndef GNSSPARSER_H
#define GNSSPARSER_H

#include <QObject>
#include <iostream>
#include "gnss.h"
#include "nmeaframe.h"

namespace GNSS
{
    class Parser : public QObject
    {
        Q_OBJECT
    public:
        explicit Parser(QObject *parent = nullptr);

    public slots:
        void parseData(QByteArray);

    private:
        void createNMEAFrame(const QByteArray& rawData);

    signals:
        void NMEAFrameGLL_created(NMEAFrameGLL);
    };
}

#endif // GNSSPARSER_H
