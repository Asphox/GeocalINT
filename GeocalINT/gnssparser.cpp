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

