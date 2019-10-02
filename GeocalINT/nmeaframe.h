#ifndef NMEAFRAME_H
#define NMEAFRAME_H

#include <QByteArray>
#include <QString>
#include <QMap>

#include <iostream>

//https://www.gpsinformation.org/dale/nmea.htm

namespace GNSS
{
    class NMEAFrame
    {
        public:

            enum class Type
            {
                GLL,
                UNKNOWN
            };

            enum class Talker
            {
                GP,     //GPS
                GL,     //GLONNAS
                GN,     //GPS+GLONNAS
                UNKNOWN
            };

            NMEAFrame(const QByteArray& rawData, const QList<QString>* fieldNames);

            static Type findType(const QByteArray& rawData);
            static Talker findTalker( const QByteArray& rawData);
            static bool   hasChecksum( const QByteArray& rawData);

            inline bool isValid() const { return valid && bHasChecksum; }

        protected:
            bool valid = false;
            bool bHasChecksum = false;
            QList<QByteArray> data;
            const QList<QString>* fieldNames;
            Type type;
            Talker talker;

            void checksum(const QByteArray& rawData);
            void fillData(const QByteArray& rawData);

            //virtual void __dummy() = 0;

    };

    class NMEAFrameGLL : public NMEAFrame
    {
        public:
            NMEAFrameGLL(const QByteArray& rawData);

            QString getLat() const { return QString(data.at(0)); }
            QString getNS() const { return QString(data.at(1)); }
            QString getLon() const { return QString(data.at(2)); }
            QString getEW() const { return QString(data.at(3)); }
            QString getUTC() const { return QString(data.at(4)); }
            QString getStatus() const { return QString(data.at(5)); }

           // void __dummy() final{}
    };
    static const QList<QString> fieldNames_GLL     = {"LAT",
                                                      "N/S",
                                                      "LON",
                                                      "E/W",
                                                      "UTC",
                                                      "STATUS",
                                                      "NONE"};
}

#endif // NMEAFRAME_H
