#ifndef GNSSPARSER_H
#define GNSSPARSER_H

#include <QObject>
#include <iostream>
#include "gnss.h"
#include "NMEA/nmeaframe.h"
#include "UBX/ubx.h"

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
        // Creats and emits a new NMEA frame based on raw frame
        //=======================
        void createNMEAFrame(const QByteArray& rawData);

        //=======================
        // Creats and emits a UBX frame based on raw frame
        //=======================
        void createUBXFrame(const QByteArray& rawData);

    signals:

        //========================
        //  Signal emitted when a GLL NMEA frame is fully created
        //========================
        void NMEAFrameGLL_created(NMEAFrameGLL);

        void UBXFrameNAV_ODO_created(UBXFrameNAV_ODO);

        void UBXFrameAID_EPH_created(UBXFrameAID_EPH);

        void UBXFrameRXM_SFRBX_created(UBXFrameRXM_SFRBX);

    };
}

#endif // GNSSPARSER_H
