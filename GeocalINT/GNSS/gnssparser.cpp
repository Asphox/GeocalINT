#include "gnssparser.h"

using namespace GNSS;

Parser::Parser(QObject *parent) : QObject(parent)
{

}

void Parser::parseData(QByteArray rawData)
{
    if( findFrameTypeFromRaw(rawData) == FrameType::NMEA )
    {
        rawData.remove(rawData.size()-2,2);
        QList<QByteArray> list = rawData.split('\n');
        for( auto it : list )
        {
            it.remove(it.indexOf('\r'),1);
            createNMEAFrame(it);
        }
    }
    else if( findFrameTypeFromRaw(rawData) == FrameType::UBX )
    {
        createUBXFrame(rawData);
    }
    else
    {
        std::cout << "UNKNOWN" << std::endl;
    }
}

void Parser::createNMEAFrame(const QByteArray& rawData)
{
    switch( NMEAFrame::findType(rawData) )
    {
        case NMEAFrame::Type::GLL : emit NMEAFrameGLL_created( NMEAFrameGLL(rawData) ); break;
        default: break;
    }
}

void Parser::createUBXFrame(const QByteArray& rawData)
{
        displayQByteArray(rawData,std::hex);
    switch( UBXFrame::findClassId(rawData) )
    {
        case UBXFrame::ClsId::AID_EPH :
            emit UBXFrameAID_EPH_created( UBXFrameAID_EPH(rawData) ); break;
        default: break;
    }
}

