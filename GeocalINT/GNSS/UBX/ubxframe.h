#ifndef UBXFRAME_H
#define UBXFRAME_H

#include <QByteArray>

namespace GNSS
{
    //=================
    //  Represents an abstract UBX-typed frame
    //=================
    class UBXFrame
    {
    public:

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
        enum class Class
        {
            NAV = 0x01, //Navigation Results Messages: Position, Speed, Time, Acceleration, Heading, DOP,SVs used
            RXM = 0x02, //Receiver Manager Messages: Satellite Status, RTC Status
            INF = 0x04, //Information  Messages:  Printf-Style  Messages,  with  IDs  such  as  Error,  Warning,Notice
            ACK = 0x05, //Ack/Nak Messages: Acknowledge or Reject messages to UBX-CFG input messages
            CFG = 0x06, //Configuration Input Messages: Configure the receiver.
            UPD = 0x09, //Firmware   Update   Messages:   Memory/Flash   erase/write,   Reboot,   Flashidentification, etc.
            MON = 0x0A, //Monitoring  Messages:  Communication  Status,  CPU  Load,  Stack  Usage,  TaskStatus
            AID = 0x0B, //AssistNow Aiding Messages: Ephemeris, Almanac, other A-GPS data input
            TIM = 0x0D, //Timing Messages: Time Pulse Output, Time Mark Results
            ESF = 0x10, //External  Sensor  Fusion  Messages:  External  Sensor  Measurements  and  StatusInformation
            MGA = 0x13, //Multiple GNSS Assistance Messages: Assistance data for various GNSS
            LOG = 0x21, //Logging Messages: Log creation, deletion, info and retrieval
            SEC = 0x27, //Security Feature Messages
            HNR = 0x28, //High Rate Navigation Results Messages: High rate time, position, speed, heading
            UNKOWN
        };


        //=================================
        //  Constrcuts an UBX from raw
        //=================================
        UBXFrame(const QByteArray&);

        //=================================
        //  Finds the UBX class of a raw frame
        //=================================
        static Class findClass(const QByteArray& rawData);

        //=================================
        //  Finds the UBX id of a raw frame
        //=================================
        static uint8_t findId(const QByteArray& rawData);

        //=================================
        //  Returns if the trame is valid (checksum pass)
        //=================================
        inline bool isValid() const { return m_valid; }

        //=================================
        //  Returns id
        //=================================
        inline uint8_t getId() const { return m_id; }


    protected:
        bool m_valid = false;
        Class m_class = Class::UNKOWN;
        uint8_t m_id;
        QByteArray m_payLoad;

        //=================================
        //  Process 8-Bit Fletcher checksum
        //=================================
        void checksum(const QByteArray&);

        //=================================
        //  Convert payLoad from 'index' to uint32_t with little-endian
        //=================================
        uint32_t plleToUint32(int index) const;

    };

    class UBXFrameACK : public UBXFrame
    {
    public:

        UBXFrameACK(const QByteArray& rawData) : UBXFrame(rawData)
        {}

        inline bool isAcknowledged() const { return m_id; }
    };
}


#endif // UBXFRAME_H
