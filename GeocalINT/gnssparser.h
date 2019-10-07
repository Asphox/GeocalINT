#ifndef GNSSPARSER_H
#define GNSSPARSER_H

#include <QObject>
#include <iostream>
#include "gnss.h"
#include "nmeaframe.h"

namespace GNSS
{

    //======================
    //  Parses all raw frames received,
    //  builds fully typed frames and emits them.
    //======================
    class Parser : public QObject
    {
        Q_OBJECT
    public:
        explicit Parser(QObject *parent = nullptr);

    public slots:

        //=======================
        //  Slot called when raw frames are received, parses them.
        //=======================
        void parseData(QByteArray);

    private:

        //=======================
        // Creats and emits a NMEA frame based on raw frame
        //=======================
        void createNMEAFrame(const QByteArray& rawData);

    signals:

        //========================
        //  Signal emitted when a GLL NMEA frame is fully created
        //========================
        void NMEAFrameGLL_created(NMEAFrameGLL);

    };
}

#endif // GNSSPARSER_H
