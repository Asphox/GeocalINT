#ifndef UBXFRAMEAID_EPH_H
#define UBXFRAMEAID_EPH_H

#include <GNSS/UBX/ubxframe.h>
#include <Utils/bytearraymanipulator.h>
#include <GNSS/UBX/AID/ubxframeaid_eph_defines.h>
#include <iostream>

namespace GNSS
{
    class UBXFrameAID_EPH : public UBXFrame
    {
    public:



        constexpr static int WORD_BIT_SIZE = 32;
        UBXFrameAID_EPH(const QByteArray& array) : UBXFrame(array)
        {
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

        uint8_t getSVHealth()
        {
            if( hasEphemeris() )
            {
                return (uint8_t)(getField(1,SVH_BIT_SIZE,SVH_BIT_OFFSET) & 0x3F);
            }
            else
            {
                return 0;
            }
        }

        uint16_t getIOCD()
        {
            if( hasEphemeris() )
            {
                return (uint16_t)(((getField(1,IOCDMSB_BIT_SIZE,IOCDLSB_BIT_OFFSET)<<8)|getField(8,IOCDLSB_BIT_SIZE,IOCDLSB_BIT_OFFSET)) & 0xFFFF);
            }
            else
            {
                return 0;
            }
        }

        int8_t getTgd()
        {
            if( hasEphemeris() )
            {
                return (int8_t)(getField(5,TGD_BIT_SIZE,TGD_BIT_OFFSET) & 0xFF);
            }
            else
            {
                return 0;
            }
        }

        uint16_t getToc()
        {
            if( hasEphemeris() )
            {
                return (uint16_t)(getField(6,TOC_BIT_SIZE,TOC_BIT_OFFSET) & 0xFFFF);
            }
            else
            {
                return 0;
            }
        }

        int8_t getF2()
        {
            if ( hasEphemeris() )
            {
                return (int8_t)(getField(7,F2_BIT_SIZE,F2_BIT_OFFSET) & 0xFF);
            }
            else
            {
                return 0;
            }
        }

        int16_t getF1()
        {
            if( hasEphemeris() )
            {
                return (int16_t)(getField(7,F1_BIT_SIZE,F1_BIT_OFFSET) & 0xFFFF);
            }
            else
            {
                return 0;
            }
        }

        int32_t getF0()
        {
            int32_t ret = 0;
            if( hasEphemeris() )
            {
                uint32_t tmp = getField(8,F0_BIT_SIZE,F0_BIT_OFFSET);
                if( tmp & (1<<(F0_BIT_SIZE-1)) )
                {
                    ret = F0_32SIGNED_MASK;
                }
                ret |= tmp;
            }
            return ret;
        }

        uint8_t getIODE()
        {
            if( hasEphemeris() )
            {
                return (uint8_t)(getField(9,IODE_BIT_SIZE,IODE_BIT_OFFSET) & 0xFF);
            }
            {
                return 0;
            }
        }

        int16_t getCrs()
        {
            if( hasEphemeris() )
            {
                return (int16_t)(getField(9,CRS_BIT_SIZE,CRS_BIT_OFFSET) & 0xFFFF);
            }
            else
            {
                return 0;
            }
        }

        int16_t getDn()
        {
            if( hasEphemeris() )
            {
                return (int16_t)(getField(10,DN_BIT_SIZE,DN_BIT_OFFSET) & 0xFFFF);
            }
            else
            {
                return 0;
            }
        }

        int32_t getM0()
        {
            if( hasEphemeris() )
            {
                return (int32_t)((getField(10,M0MSB_BIT_SIZE,M0MSB_BIT_OFFSET))<<(32-M0MSB_BIT_SIZE))|(getField(11,M0LSB_BIT_SIZE,M0LSB_BIT_OFFSET));
            }
            else
            {
                return 0;
            }
        }

        int16_t getCuc()
        {
            if( hasEphemeris() )
            {
                return (int16_t)(getField(12,CUC_BIT_SIZE,CUC_BIT_OFFSET) & 0xFFFF);
            }
            else
            {
                return 0;
            }
        }

        uint32_t getE()
        {
            if( hasEphemeris() )
            {
                return ((getField(12,EMSB_BIT_SIZE,EMSB_BIT_OFFSET)<<(32-EMSB_BIT_SIZE))|getField(13,ELSB_BIT_SIZE,ELSB_BIT_OFFSET));
            }
            else
            {
                return 0;
            }
        }

        int16_t getCus()
        {
            if( hasEphemeris() )
            {
                return (getField(14,CUS_BIT_SIZE,CUS_BIT_OFFSET) & 0xFFFF);
            }
            else
            {
                return 0;
            }
        }

        uint32_t getSqrtA()
        {
            if( hasEphemeris() )
            {
                return ((getField(14,SQRTAMSB_BIT_SIZE,SQRTAMSB_BIT_OFFSET) & 0xFF)<<(32-SQRTAMSB_BIT_SIZE))|(getField(15,SQRTALSB_BIT_SIZE,SQRTALSB_BIT_OFFSET));
            }
            else
            {
                return 0;
            }
        }

        int16_t getTOE()
        {
            if( hasEphemeris() )
            {
                return (int16_t)(getField(16,TOE_BIT_SIZE,TOE_BIT_OFFSET) & 0xFFFF);
            }
            else
            {
                return 0;
            }
        }

        bool getFIT()
        {
            if( hasEphemeris() )
            {
                return (bool)getField(16,FIT_BIT_SIZE,FIT_BIT_OFFSET);
            }
            else
            {
                return false;
            }
        }

        uint8_t getAODO()
        {
            if( hasEphemeris() )
            {
                return (uint8_t)getField(16,AODO_BIT_SIZE,AODO_BIT_OFFSET);
            }
            else
            {
                return 0;
            }
        }

        int16_t getCic()
        {
            if( hasEphemeris() )
            {
                return (int16_t)(getField(17,CIC_BIT_SIZE,CIC_BIT_OFFSET) & 0xFFFF);
            }
            else
            {
                return 0;
            }
        }

        int32_t getOMEGA0()
        {
            if( hasEphemeris() )
            {
                return (int32_t)((getField(17,OMEGA0MSB_BIT_SIZE,OMEGA0MSB_BIT_OFFSET)<<(32-OMEGA0MSB_BIT_SIZE))|(getField(18,OMEGA0LSB_BIT_SIZE,OMEGA0LSB_BIT_OFFSET)));
            }
            else
            {
                return 0;
            }
        }

        int16_t getCis()
        {
            if( hasEphemeris() )
            {
                return (int16_t)(getField(19,CIS_BIT_SIZE,CIS_BIT_OFFSET) & 0xFFFF);
            }
            else
            {
                return 0;
            }
        }

        int32_t getI0()
        {
            if( hasEphemeris() )
            {
                return (int32_t)((getField(19,I0MSB_BIT_SIZE,I0MSB_BIT_OFFSET) & 0xFF)<<(32-I0MSB_BIT_SIZE))|(getField(20,I0LSB_BIT_SIZE,I0LSB_BIT_OFFSET));
            }
            else
            {
                return 0;
            }
        }

        int16_t getCrc()
        {
            if( hasEphemeris() )
            {
                return (int16_t)(getField(21,CRC_BIT_SIZE,CRC_BIT_OFFSET) & 0xFFFF);
            }
            else
            {
                return 0;
            }
        }

        int32_t getOMEGA()
        {
            if( hasEphemeris() )
            {
                return (int32_t)((getField(21,OMEGAMSB_BIT_SIZE,OMEGAMSB_BIT_OFFSET)<<(32-OMEGAMSB_BIT_SIZE))|getField(22,OMEGALSB_BIT_SIZE,OMEGALSB_BIT_OFFSET));
            }
            else
            {
                return 0;
            }
        }

        int32_t getOMEGAP()
        {
            int32_t ret = 0;
            if( hasEphemeris() )
            {
                uint32_t tmp = getField(23,OMEGAP_BIT_SIZE,OMEGAP_BIT_OFFSET);
                if( tmp & (1<<(OMEGAP_BIT_SIZE-1)) )
                {
                    ret = OMEGAP_32SIGNED_MASK;
                }
                ret |= tmp;
            }
            return ret;
        }

        int16_t getIDOT()
        {
            int16_t ret = 0;
            if( hasEphemeris() )
            {
                uint16_t tmp = (uint16_t)(getField(24,IDOT_BIT_SIZE,IDOT_BIT_SIZE) & 0xFFFF);
                if( tmp & (1<<(IDOT_BIT_SIZE-1)) )
                {
                    ret = IDOT_16SIGNED_MASK;
                }
                ret |= tmp;
            }
            return ret;
        }

        inline double getScaledCRS()
        {
            return getCrc()*CRC_SCALE_FACTOR;
        }

        inline double getScaledDN()
        {
            return getDn()*DN_SCALE_FACTOR;
        }

        inline double getScaledM0()
        {
            return getM0()*M0_SCALE_FACTOR;
        }

        inline double getScaledCUC()
        {
            return getCuc()*CUC_SCALE_FACTOR;
        }

        inline double getScaledE()
        {
            return getE()*E_SCALE_FACTOR;
        }

        inline double getScaledCUS()
        {
            return getCus()*CUS_SCALE_FACTOR;
        }

        inline double getScaledSqrtA()
        {
            return getSqrtA()*SQRTA_SCALE_FACTOR;
        }

        inline double getScaledTOE()
        {
            return getTOE()*TOE_SCALE_FACTOR;
        }

        inline double getScaledCic()
        {
            return getCic()*CIC_SCALE_FACTOR;
        }

        inline double getScaledOMEGA0()
        {
            return getOMEGA0()*OMEGA0_SCALE_FACTOR;
        }

        inline double getScaledCis()
        {
            return getCis()*CIS_SCALE_FACTOR;
        }

        inline double getScaledI0()
        {
            return getI0()*I0_SCALE_FACTOR;
        }

        inline double getScaledCrc()
        {
            return getCrc()*CRC_SCALE_FACTOR;
        }

        inline double getScaledOMEGA()
        {
            return getOMEGA()*OMEGA_SCALE_FACTOR;
        }

        inline double getScaledOMEGAP()
        {
            return getOMEGAP()*OMEGAP_SCALE_FACTOR;
        }

        inline double getScaledIDOT()
        {
            return getIDOT()*IDOT_SCALE_FACTOR;
        }


    };
}

#endif // UBXFRAMEAID_EPH_H
