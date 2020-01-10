#include "gnssparser.h"

using namespace GNSS;

Parser::Parser(QObject *parent) : QObject(parent)
{

}

void Parser::parseData(QByteArray rawData)
{
    QList<QByteArray> list = rawData.split('\n');
    for( auto it : list )
    {
        it.remove(it.indexOf('\r'),1);
        switch( findFrameTypeFromRaw(it) )
        {
            case FrameType::NMEA : createNMEAFrame(it); break;
        case FrameType::UBX :   createUBXFrame(it); break;
            default : std::cout << "UNKOWN " << std::endl; break;
        }
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
    switch( UBXFrame::findClassId(rawData) )
    {
        case UBXFrame::ClsId::AID_EPH :
            emit UBXFrameAID_EPH_created( UBXFrameAID_EPH(rawData) ); break;
        default: break;
    }
}

