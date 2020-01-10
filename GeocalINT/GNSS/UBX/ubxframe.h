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
        constexpr static uint8_t CKA_ENDPOS        = 1;
        constexpr static uint8_t CKB_ENDPOS        = 0;
        constexpr static uint8_t CHKSUM_PROCESS_START_POS = 2;
        constexpr static uint8_t CHKSUM_PROCESS_END_POSEND = 2;

        //==================
        //  Class of the UBX frame
        //==================
        enum class ClsId
        {
            ACK_ACK     = GNSS_UBX_CLSID(0x05,0x01),
            ACK_NACK    = GNSS_UBX_CLSID(0x05,0x00),

            NAV_ODO     = GNSS_UBX_CLSID(0x01,0x09),

            CFG_TP5     = GNSS_UBX_CLSID(0x06,0x31),

            AID_EPH     = GNSS_UBX_CLSID(0x0B,0x31),

            RXM_SFRBX   = GNSS_UBX_CLSID(0x02,0x13),

            UNKOWN
        };


        //==================
        //  Checksum struct
        //==================
        struct ChkSum
        {
            int8_t a = 0;
            int8_t b = 0;
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
        static ClsId findClassId(const QByteArray& rawData);

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
        static ChkSum checksum(const QByteArray&);

        //=================================
        //  Convert payLoad from 'index' to uint8_t with little-endian
        //=================================
        uint8_t payload_LE_U1(int index) const;

        //=================================
        //  Convert payLoad from 'index' to int8_t with little-endian
        //=================================
        int8_t payload_LE_I1(int index) const;

        //=================================
        //  Convert payLoad from 'index' to uint16_t with little-endian
        //=================================
        uint16_t payload_LE_U2(int index) const;

        //=================================
        //  Convert payLoad from 'index' to int16_t with little-endian
        //=================================
        uint16_t payload_LE_I2(int index) const;

        //=================================
        //  Convert payLoad from 'index' to uint32_t with little-endian
        //=================================
        uint32_t payload_LE_U4(int index) const;

        //=================================
        //  Convert payLoad from 'index' to int32_t with little-endian
        //=================================
        int32_t payload_LE_I4(int index) const;

    };
}


#endif // UBXFRAME_H
