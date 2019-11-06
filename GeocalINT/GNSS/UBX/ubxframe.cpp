#include "ubxframe.h"

using namespace GNSS;

UBXFrame::UBXFrame(const QByteArray& rawData)
{
    checksum(rawData);
    m_clsId = (ClsId)GNSS_UBX_CLSID(rawData[CLASS_POS],rawData[ID_POS]);
    m_payLoad = (rawData.chopped(2)).mid(6);
}

UBXFrame::ClsId UBXFrame::findClass(const QByteArray& rawData)
{
    return static_cast<ClsId>(rawData[CLASS_POS]);
}

uint8_t UBXFrame::findId(const QByteArray& rawData)
{
    return static_cast<uint8_t>(rawData[ID_POS]);
}

QByteArray UBXFrame::makePollMessage(ClsId clsId, const QByteArray& options )
{
    QByteArray message = {SYNC_CHAR_1,SYNC_CHAR_2};
    QPair<int8_t,int8_t> ck = checksum(options);
    message += GNSS_UBX_CLS(clsId);
    message += GNSS_UBX_ID(clsId);
    message += static_cast<int8_t>(options.length());
    for( auto it : options )
    {
        message += it;
    }
    message += ck.first;
    message += ck.second;

    return message;
}

void UBXFrame::checksumCheck(const QByteArray& rawData)
{
    QPair<int8_t,int8_t> ck = checksum(rawData);
    m_valid = (ck.first == rawData[rawData.size()-CKA_ENDPOS] && ck.second == rawData[rawData.size()-CKB_ENDPOS]);
}

QPair<int8_t,int8_t> UBXFrame::checksum(const QByteArray& rawData)
{
    int8_t CK_A=0, CK_B=0;
    for( int i=CK_PROCESS_START_POS; i<=rawData.size()-CK_PROCESS_END_POSEND; i++)
    {
        CK_A += rawData[i];
        CK_B += CK_A;
    }
    return QPair<int8_t,int8_t>(CK_A,CK_B);
}

uint32_t UBXFrame::plleToUint32(int index) const
{
    return static_cast<uint32_t>(m_payLoad[index])          |
           static_cast<uint32_t>(m_payLoad[index+1])  << 8  |
           static_cast<uint32_t>(m_payLoad[index+2])  << 16 |
           static_cast<uint32_t>(m_payLoad[index+3])  << 24 ;
}
