#ifndef UBXFRAMECFG_TP5_H
#define UBXFRAMECFG_TP5_H

#include <GNSS/UBX/ubxframe.h>

namespace GNSS
{
    class UBXFrameCFG_TP5 : public UBXFrame
    {
    public:

        UBXFrameCFG_TP5(const QByteArray& rawData) : UBXFrame(rawData)
        {}
    };
}

#endif // UBXFRAMECFG_TP5_H
