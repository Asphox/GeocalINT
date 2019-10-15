#ifndef UBXFRAMENAV_ODO_H
#define UBXFRAMENAV_ODO_H

#include <GNSS/UBX/NAV/ubxframenav.h>

namespace GNSS
{

    class UBXFrameNAV_ODO : public UBXFrameNAV
    {
    public:

        UBXFrameNAV_ODO(const QByteArray& rawData) : UBXFrameNAV(rawData)
        {}

        inline uint8_t getVersion() const { return static_cast<uint8_t>(m_payLoad[0]); }

        uint32_t getITOW() const
        {
            return plleToUint32(4);
        }

        uint32_t getDistance() const
        {
            return plleToUint32(8);
        }

        uint32_t getTotalDistance() const
        {
            return plleToUint32(12);
        }

        uint32_t getDistanceStd() const
        {
            return plleToUint32(16);
        }
    };
}

#endif // UBXFRAMENAV_ODO_H
