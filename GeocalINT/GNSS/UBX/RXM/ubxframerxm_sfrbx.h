#ifndef UBXFRAMERXM_SFRBX_H
#define UBXFRAMERXM_SFRBX_H

#include <GNSS/UBX/ubxframe.h>

namespace GNSS
{
    class UBXFrameRXM_SFRBX : public UBXFrame
    {
        UBXFrameRXM_SFRBX(const QByteArray& array) : UBXFrame(array)
        {}

    };
}

#endif // UBXFRAMERXM_SFRBX_H
