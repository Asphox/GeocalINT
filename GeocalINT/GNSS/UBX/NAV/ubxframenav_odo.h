#ifndef UBXFRAMENAV_ODO_H
#define UBXFRAMENAV_ODO_H

#include <GNSS/UBX/ubxframe.h>

namespace GNSS
{
    class UBXFrameNAV_ODO : public UBXFrame
    {
    public:

        UBXFrameNAV_ODO(const QByteArray& rawData) : UBXFrame(rawData)
        {}

        inline uint8_t getVersion() const { return static_cast<uint8_t>(m_payLoad[0]); }

        uint32_t getITOW() const
        {
            return payload_LE_U4(4);
        }

        uint32_t getDistance() const
        {
            return payload_LE_U4(8);
        }

        uint32_t getTotalDistance() const
        {
            return payload_LE_U4(12);
        }

        uint32_t getDistanceStd() const
        {
            return payload_LE_U4(16);
        }
    };
}

#endif // UBXFRAMENAV_ODO_H
