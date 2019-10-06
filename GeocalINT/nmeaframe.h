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

            static double DMSToD( QString DMS )
            {
                double angle = 0;
                int pointPos = DMS.indexOf('.');
                if( pointPos > 0 )
                {
                    angle += DMS.mid(pointPos-2,DMS.size()-pointPos).toDouble()/60;
                    angle += DMS.left(pointPos-2).toDouble();
                }
                std::cout << angle << std::endl;
                return angle;
            }

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

            double getLat() const { return DMSToD(QString(data.at(0))); }
            QString getLatDMS() const { return QString(data.at(0)); }
            QString getNS() const { return QString(data.at(1)); }
            double getLon() const { return DMSToD(QString(data.at(2))); }
            //QString getLonDMS() const {  }
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
