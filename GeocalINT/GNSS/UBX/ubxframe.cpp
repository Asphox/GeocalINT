#include "ubxframe.h"

using namespace GNSS;

UBXFrame::UBXFrame(const QByteArray& rawData)
{
    checksum(rawData);
    m_class = static_cast<Class>(rawData[CLASS_POS]);
    m_id = static_cast<uint8_t>(rawData[ID_POS]);
    m_payLoad = (rawData.chopped(2)).mid(6);
}

UBXFrame::Class UBXFrame::findClass(const QByteArray& rawData)
{
    return static_cast<Class>(rawData[CLASS_POS]);
}

uint8_t UBXFrame::findId(const QByteArray& rawData)
{
    return static_cast<uint8_t>(rawData[ID_POS]);
}

void UBXFrame::checksum(const QByteArray& rawData)
{
    uint8_t CK_A=0, CK_B=0;
    for( int i=CK_PROCESS_START_POS; i<=rawData.size()-CK_PROCESS_END_POSEND; i++)
    {
        CK_A += rawData[i];
        CK_B += CK_A;
    }

    m_valid = (CK_A == rawData[rawData.size()-CKA_ENDPOS] && CK_B == rawData[rawData.size()-CKB_ENDPOS]);
}

uint32_t UBXFrame::plleToUint32(int index) const
{
    return static_cast<uint32_t>(m_payLoad[index])          |
           static_cast<uint32_t>(m_payLoad[index+1])  << 8  |
           static_cast<uint32_t>(m_payLoad[index+2])  << 16 |
           static_cast<uint32_t>(m_payLoad[index+3])  << 24 ;
}
