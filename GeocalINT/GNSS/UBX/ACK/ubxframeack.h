#ifndef UBXFRAMEACK_H
#define UBXFRAMEACK_H

#include <GNSS/UBX/ubxframe.h>

namespace GNSS
{
    class UBXFrameACK : public UBXFrame
    {
        public:

        UBXFrameACK(const QByteArray& rawData) : UBXFrame(rawData)
        {}

        inline bool isAcknowledged() const { return GNSS_UBX_ID(m_clsId); }
    };
}
#endif //UBXFRAMEACK_H
