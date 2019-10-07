#ifndef GNSS_H
#define GNSS_H

#include <QByteArray>

namespace GNSS
{
    //=======================
    //  Enum with all frame modes (classic NMEA, raw UBX)
    //=======================
    enum class FrameType
    {
        UNKNOWN,
        NMEA,
        UBX
    };

    //========================
    //  Returns the frame type from a raw frame
    //========================
    FrameType findFrameTypeFromRaw(const QByteArray& data);
}

#endif // GNSS_H
