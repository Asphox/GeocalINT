#include "gnss.h"

GNSS::FrameType GNSS::findFrameTypeFromRaw(const QByteArray& data)
{
    // NMEA check :
    //  1st char is $ or !
    //  7th char is ,
    if(data[0] == '$' && data[6] == ',')
    {
        return GNSS::FrameType::NMEA;
    }
    else if(data[GNSS::UBXFrame::SYNC_CHAR_1_POS] == static_cast<char>(0xB5) &&
            data[GNSS::UBXFrame::SYNC_CHAR_2_POS] == 0x62)
    {
        return GNSS::FrameType::UBX;
    }
    else
    {
        return GNSS::FrameType::UNKNOWN;
    }
}
