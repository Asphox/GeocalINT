#include "nmeaframe.h"

using namespace GNSS;

NMEAFrame::NMEAFrame(const QByteArray& rawData, const QList<QString>* fieldNames) : fieldNames(fieldNames)
{
    talker = findTalker(rawData);
    type = findType(rawData);

    if( hasChecksum(rawData) )
    {
        bHasChecksum = true;
        checksum(rawData);
    }

    fillData(rawData);
}

NMEAFrame::Type NMEAFrame::findType(const QByteArray& rawData)
{
    if( rawData.contains("GLL") )
        return Type::GLL;
    else
        return Type::UNKNOWN;
}

NMEAFrame::Talker NMEAFrame::findTalker(const QByteArray& rawData)
{
    if( rawData.contains("$GP") )
        return Talker::GP;
    else if( rawData.contains("$GL") )
        return Talker::GL;
    else if( rawData.contains("$GN") )
        return Talker::GN;
    else
        return Talker::UNKNOWN;
}

bool NMEAFrame::hasChecksum(const QByteArray& rawData)
{
    return rawData[rawData.size()-3] == '*';
}

void NMEAFrame::checksum(const QByteArray& rawData)
{
    //  checksum excluding initial $ and *CC
    int checksumValue = 0;
    for( int i=1; i<rawData.size()-3; i++  )
    {
        checksumValue ^= rawData[i];
    }
    valid = rawData.right(2).toInt(nullptr,16) == checksumValue;
}

void NMEAFrame::fillData(const QByteArray& rawData)
{
   data = rawData.left(rawData.size()-3).split(',');
   data.pop_front();
}







NMEAFrameGLL::NMEAFrameGLL(const QByteArray& rawData) : NMEAFrame(rawData,&fieldNames_GLL)
{
    if( fieldNames->size() != data.size() ) valid = false;
}
