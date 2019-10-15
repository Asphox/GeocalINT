#ifndef UBXFRAMENAV_H
#define UBXFRAMENAV_H

#include <GNSS/UBX/ubxframe.h>

namespace GNSS
{
    class UBXFrameNAV : public UBXFrame
    {
    public:

        UBXFrameNAV(const QByteArray& rawData) : UBXFrame(rawData)
        {}

        enum class Id
        {
            AOPSTATUS = 0x60,   SOL     = 0x06,
            ATT       = 0x05,   STATUS  = 0x03,
            CLOCK     = 0x22,   SVINFO  = 0x30,
            DGPS      = 0x31,   SVIN    = 0x3B,
            DOP       = 0x04,   TIMEBDS = 0x24,
            EOE       = 0x61,   TIMEGAL = 0x25,
            GEOFENCE  = 0x39,   TIMEGLO = 0x23,
            HPPOSECEF = 0x13,   TIMEGPS = 0x20,
            HPPOSLLH  = 0x14,   TIMELS  = 0x26,
            ODO       = 0x09,   TIMEUTC = 0x21,
            ORB       = 0x34,   VELECEF = 0x11,
            POSECEF   = 0x01,   VELNED  = 0x12,
            POSLLH    = 0x02,
            PVT       = 0x07,
            RELPOSNED = 0x3C,
            RESETODO  = 0x10,
            SAT       = 0x35,
            SBAS      = 0x32,
            SLAS      = 0x42
        };
    };
}

#endif // UBXFRAMENAV_H
