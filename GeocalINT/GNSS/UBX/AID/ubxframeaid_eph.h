#ifndef UBXFRAMEAID_EPH_H
#define UBXFRAMEAID_EPH_H

#include <GNSS/UBX/ubxframe.h>
#include <Utils/bytearraymanipulator.h>
#include <iostream>

namespace GNSS
{
    class UBXFrameAID_EPH : public UBXFrame
    {
    public:
        constexpr static int POS_SVID = 0;
        constexpr static int POS_HOW = 4;

        constexpr static int WEEKTIME_BIT_SIZE = 10;
        constexpr static int WEEKTIME_BIT_OFFSET = 14;

        constexpr static int L2CODE_BIT_SIZE = 2;
        constexpr static int L2CODE_BIT_OFFSET = 12;

        constexpr static int URA_BIT_SIZE = 4;
        constexpr static int URA_BIT_OFFSET = 8;

        constexpr static int SVH_BIT_SIZE = 6;
        constexpr static int SVH_BIT_OFFSET = 2;

        constexpr static int IOCDMSB_BIT_SIZE = 2;
        constexpr static int IODCMSB_BIT_OFFSET = 0;

        constexpr static int IOCDLSB_BIT_SIZE = 8;
        constexpr static int IOCDLSB_BIT_OFFSET = 16;

        constexpr static int WORD_BIT_SIZE = 32;
        UBXFrameAID_EPH(const QByteArray& array) : UBXFrame(array)
        {
            // displayQByteArray(m_payLoad,std::hex);
        }

        inline uint32_t getSVID()
        {
            return payload_LE_U4(0);
        }

        inline bool hasEphemeris()
        {
            return payload_LE_U4(4);
        }

        uint32_t getHOW()
        {
            return payload_LE_U4(4);
        }

        inline uint32_t getWord(int index)
        {
            return payload_LE_U4(4*index + 4);
        }

        inline uint32_t getField(int word_index, int field_bit_size, int field_bit_offset)
        {
            return (getWord(word_index)>>(field_bit_offset) & ((1<<(field_bit_size))-1));
        }

        uint32_t getWeekTime()
        {
            if( hasEphemeris() )
            {
                return getField(1,WEEKTIME_BIT_SIZE,WEEKTIME_BIT_OFFSET);
            }
            else
            {
                return 0;
            }
        }

        uint32_t getL2Code()
        {
            if( hasEphemeris() )
            {
                return getField(1,L2CODE_BIT_SIZE,L2CODE_BIT_OFFSET);
            }
            {
                return 0;
            }
        }

        uint32_t getURA()
        {
            if( hasEphemeris() )
            {
                return getField(1,URA_BIT_SIZE,URA_BIT_OFFSET);
            }
            {
                return 0;
            }
        }

        uint32_t getSVHealth()
        {
            if( hasEphemeris() )
            {
                return getField(1,SVH_BIT_SIZE,SVH_BIT_OFFSET);
            }
            else
            {
                return 0;
            }
        }

        uint32_t getIOCD()
        {
            if( hasEphemeris() )
            {
                return (getField(1,IOCDMSB_BIT_SIZE,IOCDLSB_BIT_OFFSET)<<8)|getField(8,IOCDLSB_BIT_SIZE,IOCDLSB_BIT_OFFSET);
            }
            else
            {
                return 0;
            }
        }
    };
}

#endif // UBXFRAMEAID_EPH_H
