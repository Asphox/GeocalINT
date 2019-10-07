#ifndef NMEAFRAME_H
#define NMEAFRAME_H

#include <QByteArray>
#include <QString>
#include <QMap>

namespace GNSS
{
    //=================
    //  Represents an abstract NMEA-typed frame
    //=================
    class NMEAFrame
    {
        public:

            //==================
            //  Type of the NMEA frame
            //==================
            enum class Type
            {
                GLL,
                UNKNOWN
            };

            //=================
            // Talker (constellation) for this frame
            //=================
            enum class Talker
            {
                GP,     //GPS
                GL,     //GLONNAS
                GN,     //GPS+GLONNAS
                UNKNOWN
            };

            //=================================
            //  Constrcut an NMEA frame from a raw frame, with the fieldNames corresponding to the frame type
            //=================================
            NMEAFrame(const QByteArray& rawData, const QList<QString>* fieldNames);

            //=================================
            //  Finds the NMEA type of a raw frame
            //=================================
            static Type findType(const QByteArray& rawData);

            //=================================
            //  Finds the NMEA talker of a raw frame
            //=================================
            static Talker findTalker(const QByteArray& rawData);

            //=================================
            //  Checks if an NMEA frame provides a checksum
            //=================================
            static bool   hasChecksum(const QByteArray& rawData);

            //=================================
            //  Converts geo-position from "degrees-minutes" to "degrees"
            //=================================
            static double DMToD( QString DM )
            {
                double angle = 0;
                int pointPos = DM.indexOf('.');
                if( pointPos > 0 )
                {
                    angle += DM.mid(pointPos-2,DM.size()-pointPos).toDouble()/60;
                    angle += DM.left(pointPos-2).toDouble();
                }
                return angle;
            }


            //=================================
            //  Returns if the trame is valid (checksum pass)
            //=================================
            inline bool isValid() const { return m_valid && m_hasChecksum; }

        protected:
            bool m_valid = false;
            bool m_hasChecksum = false;
            QList<QByteArray> m_data;
            const QList<QString>* m_fieldNames;
            Type m_type;
            Talker m_talker;

            //=================================
            //  Process checksum from a raw frame
            //=================================
            void checksum(const QByteArray& rawData);

            //=================================
            //  Extracts all fields in a raw frame
            //=================================
            void fillData(const QByteArray& rawData);

    };


    //==================
    //  Fieldnames for GLL NMEA frame
    //==================
    static const QList<QString> fieldNames_GLL     = {"LAT",
                                                      "N/S",
                                                      "LON",
                                                      "E/W",
                                                      "UTC",
                                                      "STATUS",
                                                      "NONE"};

    //==================
    //  GLL NMEA Frame, with specific getter
    //==================
    class NMEAFrameGLL : public NMEAFrame
    {
        public:

            NMEAFrameGLL(const QByteArray& rawData) : NMEAFrame(rawData,&fieldNames_GLL)
            {}

            inline double getLat() const { return DMToD(QString(m_data.at(0))); }
            inline QString getLatDM() const { return QString(m_data.at(0)); }
            inline QString getNS() const { return QString(m_data.at(1)); }
            inline double getLon() const { return DMToD(QString(m_data.at(2))); }
            inline QString getLonDM() const { return QString(m_data.at(2)); }
            QString getEW() const { return QString(m_data.at(3)); }
            QString getUTC() const { return QString(m_data.at(4)); }
            QString getStatus() const { return QString(m_data.at(5)); }
    };
}

#endif // NMEAFRAME_H
