#include "ubxframe.h"

#include <iostream>

using namespace GNSS;

UBXFrame::UBXFrame(const QByteArray& rawData)
{
    checksum(rawData);
    m_clsId = (ClsId)GNSS_UBX_CLSID(rawData[CLASS_POS],rawData[ID_POS]);
    m_payLoad = (rawData.chopped(2)).mid(6);
}

UBXFrame::ClsId UBXFrame::findClassId(const QByteArray& rawData)
{
    UBXFrame::ClsId clsId = (ClsId)GNSS_UBX_CLSID(rawData[CLASS_POS],rawData[ID_POS]);
    return clsId;
}

uint8_t UBXFrame::findId(const QByteArray& rawData)
{
    return static_cast<uint8_t>(rawData[ID_POS]);
}

QByteArray UBXFrame::makePollMessage(ClsId clsId, const QByteArray& options )
{
    QByteArray message;
    message.push_back(SYNC_CHAR_1);
    message.push_back(SYNC_CHAR_2);

    message.push_back(GNSS_UBX_CLS(clsId));
    message.push_back(GNSS_UBX_ID(clsId));

    message.push_back(static_cast<int8_t>(options.length() & 0xFF));
    message.push_back(static_cast<int8_t>((options.length()>>8) & 0xFF));
    for( auto it : options )
    {
        message.push_back(it);
    }

    message.push_back('\0');
    message.push_back('\0');

    ChkSum sum = checksum(message);
    message[message.length()-2] = sum.a;
    message[message.length()-1] = sum.b;

    return message;
}

void UBXFrame::checksumCheck(const QByteArray& rawData)
{
    ChkSum sum = checksum(rawData);
    m_valid = (sum.a == rawData[rawData.size()-CKA_ENDPOS] && sum.a == rawData[rawData.size()-CKB_ENDPOS]);
}

UBXFrame::ChkSum UBXFrame::checksum(const QByteArray& message)
{
    ChkSum sum;
    for(int i=CHKSUM_PROCESS_START_POS; i<(message.length()-CHKSUM_PROCESS_END_POSEND); i++)
    {
        sum.a += message[i];
        sum.b += sum.a;
    }
    return sum;
}

uint32_t UBXFrame::payload_LE_U4(int index) const
{
    return static_cast<int32_t>(static_cast<uint8_t>(m_payLoad[index]))          |
           static_cast<int32_t>(static_cast<uint8_t>(m_payLoad[index+1]))  << 8  |
           static_cast<int32_t>(static_cast<uint8_t>(m_payLoad[index+2]))  << 16 |
           static_cast<int32_t>(static_cast<uint8_t>(m_payLoad[index+3]))  << 24 ;
}
