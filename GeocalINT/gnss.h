#ifndef GNSS_H
#define GNSS_H

#include <QByteArray>

namespace GNSS
{
    enum class FrameType
    {
        UNKNOWN,
        NMEA,
        UBX
    };

    FrameType findFrameTypeFromRaw(const QByteArray& data);
}

#endif // GNSS_H
