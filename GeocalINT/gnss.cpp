#include "gnss.h"

GNSS::FrameType GNSS::findFrameTypeFromRaw(const QByteArray& data)
{
    // NMEA check :
    //  1st char is $ or !
    //  7th char is ,
    if( data[0] == '$' && data[6] == ',' )
    {
        return GNSS::FrameType::NMEA;
    }
    else
    {
        return GNSS::FrameType::UNKNOWN;
    }
}
