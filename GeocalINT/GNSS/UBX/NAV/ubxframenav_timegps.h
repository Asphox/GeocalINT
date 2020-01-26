#ifndef UBXFRAMENAV_TIMEGPS_H
#define UBXFRAMENAV_TIMEGPS_H

#include <GNSS/UBX/ubxframe.h>

namespace GNSS
{

class UBXFrameNAV_TIMEGPS : public UBXFrame
{
public:
    UBXFrameNAV_TIMEGPS(const QByteArray& rawData) : UBXFrame(rawData)
    {}

    double getTimeGPS()
    {
        return static_cast<double>(payload_LE_U4(0))*static_cast<double>(0.001) + static_cast<double>(payload_LE_I4(4))*static_cast<double>(0.000000001);
    }
};

}

#endif // UBXFRAMENAV_TIMEGPS_H
