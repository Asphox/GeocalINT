#ifndef UBXFRAME_H
#define UBXFRAME_H

#include <QByteArray>
#include <QVector>

#define GNSS_UBX_CLSID(cls,id) (((cls)<<8)|(id))
#define GNSS_UBX_CLS(enm) static_cast<int8_t>((((static_cast<int>(enm))>>8) & 0xFF))
#define GNSS_UBX_ID(enm) static_cast<int8_t>(((static_cast<int>(enm)) & 0xFF))

namespace GNSS
{
    //=================
    //  Represents an abstract UBX-typed frame
    //=================
    class UBXFrame
    {
    public:

        constexpr static uint8_t SYNC_CHAR_1       = 0xB5;
        constexpr static uint8_t SYNC_CHAR_2       = 0x62;
        constexpr static uint8_t SYNC_CHAR_1_POS   = 0;
        constexpr static uint8_t SYNC_CHAR_2_POS   = 1;
        constexpr static uint8_t CLASS_POS         = 2;
        constexpr static uint8_t ID_POS            = 3;
        constexpr static uint8_t LENGTH_1_POS      = 4;
        constexpr static uint8_t LENGTH_2_POS      = 5;
        constexpr static uint8_t PAYLOAD_START_POS = 6;
        constexpr static uint8_t CKA_ENDPOS        = 2;
        constexpr static uint8_t CKB_ENDPOS        = 1;
        constexpr static uint8_t CK_PROCESS_START_POS = 2;
        constexpr static uint8_t CK_PROCESS_END_POSEND = 3;

        //==================
        //  Class of the UBX frame
        //==================
        enum class ClsId
        {
            ACK_ACK     = GNSS_UBX_CLSID(0x05,0x01),
            ACK_NACK    = GNSS_UBX_CLSID(0x05,0x00),

            NAV_ODO     = GNSS_UBX_CLSID(0x01,0x09),

            UNKOWN
        };


        //=================================
        //  Constrcuts an UBX from raw
        //=================================
        UBXFrame(const QByteArray&);

        //=================================
        // Constructs an empty UBX frame
        //=================================
        UBXFrame() = default;

        //=================================
        //  Makes an empty frame for polling data
        //=================================
        static QByteArray makePollMessage(ClsId clsId, const QByteArray& options = {} );

        //=================================
        //  Finds the UBX class of a raw frame
        //=================================
        static ClsId findClass(const QByteArray& rawData);

        //=================================
        //  Finds the UBX id of a raw frame
        //=================================
        static uint8_t findId(const QByteArray& rawData);

        //=================================
        //  Returns if the trame is valid (checksum pass)
        //=================================
        inline bool isValid() const { return m_valid; }


    protected:
        bool m_valid = false;
        ClsId m_clsId = ClsId::UNKOWN;
        QByteArray m_payLoad;

        //=================================
        //  Process 8-Bit Fletcher checksum
        //=================================
        void checksumCheck(const QByteArray&);

        //=================================
        //  Process 8-bit Fletcher checksum
        //=================================
        static QPair<int8_t,int8_t> checksum(const QByteArray&);

        //=================================
        //  Convert payLoad from 'index' to uint32_t with little-endian
        //=================================
        uint32_t plleToUint32(int index) const;

    };
}


#endif // UBXFRAME_H
