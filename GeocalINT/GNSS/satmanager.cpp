#include "satmanager.h"

using namespace GNSS;

SatManager::SatManager(CMap* map, QObject *parent) : QObject(parent), m_map(map)
{

}

void SatManager::onUBX_EPH(UBXFrameAID_EPH eph)
{
    auto it = m_detectedSatEphemeris.find(eph.getSVID());
    if( !eph.hasEphemeris() )
    {
        if( it == m_detectedSatEphemeris.end() )
        {
            m_detectedSatEphemeris.remove(eph.getSVID());
        }
    }
    else
    {
        m_detectedSatEphemeris.remove(eph.getSVID());
        m_detectedSatEphemeris.insert(eph.getSVID(),eph);
    }
    updateQML();
}

void SatManager::updateQML()
{
    m_map->updateSatQML(m_detectedSatEphemeris);
}
