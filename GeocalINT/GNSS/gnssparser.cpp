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
        case FrameType::UBX :
            default : std::cout << "UNKOWN "; break;
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
    switch( UBXFrame::findClass(rawData) )
    {
        case UBXFrame::Class::ACK : break;
        case UBXFrame::Class::NAV :
            switch( static_cast<UBXFrameNAV::Id>(UBXFrameNAV::findId(rawData)) )
            {
                case UBXFrameNAV::Id::ODO : emit UBXFrameNAV_ODO_created(UBXFrameNAV_ODO(rawData)); break;
                default: break;
            }
        break;
        default: break;
    }
}

