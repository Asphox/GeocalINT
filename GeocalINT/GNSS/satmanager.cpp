#include "satmanager.h"

using namespace GNSS;

SatManager::SatManager(CMap* map, SerialManager& serialManager, QObject *parent) : QObject(parent), m_map(map), m_serialManager(serialManager)
{
    QObject::connect(&m_timerGPSTime,SIGNAL(timeout()),this,SLOT(updateGPSTime()));
    m_timerGPSTime.setInterval(1000);
    m_timerGPSTime.start();

    QObject::connect(&m_timerEph,SIGNAL(timeout()),this,SLOT(updateEphemeris()));
    m_timerEph.setInterval(10000);
    m_timerEph.start();
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

void SatManager::onNAV_TIMEGPS(UBXFrameNAV_TIMEGPS time)
{
    std::cout << time.getTimeGPS() << "s" << std::endl;
    m_currentGPSTime = time.getTimeGPS();
}

void SatManager::updateQML()
{
    m_map->updateSatQML(m_detectedSatEphemeris);
}

void SatManager::updateGPSTime()
{
    auto tmp = GNSS::UBXFrame::makePollMessage(GNSS::UBXFrame::ClsId::NAV_TIMEGPS);
    m_serialManager.write(tmp);
}

void SatManager::updateEphemeris()
{
    QByteArray params;
    for(int i=1; i<=33; i++)
    {
        params.push_back(i);
        auto tmp = GNSS::UBXFrame::makePollMessage(GNSS::UBXFrame::ClsId::AID_EPH,params);
        m_serialManager.write(tmp);
        params.clear();
    }
}

void SatManager::updatePos()
{
    if( m_detectedSatEphemeris.size() < 4 )
    {
        std::cerr << "Nombre sat insuffisant : " << m_detectedSatEphemeris.size() << "/4" << std::endl;
        return;
    }
    std::cout << "Nombre sat suffisant : " << m_detectedSatEphemeris.size() << "/4" << std::endl;

    double Tk = 0;
    double Mk = 0;
    double Ek = 0;
    double Vk = 0;
    double Uk = 0;
    double Rk = 0;
    double Ik = 0;
    double Lk = 0;

    double m0 = 0;
    double dn = 0;
    double w = 0;
    double w0 = 0;
    double wdot = 0;
    double cuc = 0;
    double cus = 0;
    double crc = 0;
    double crs = 0;
    double cic = 0;
    double cis = 0;
    double e = 0;
    double a = 0;
    double i0 = 0;
    double idot = 0;
    double toe = 0;

    for( auto& eph : m_detectedSatEphemeris )
    {
        m0 = eph.getScaledM0();
        dn = eph.getScaledDN();
        a = eph.getScaledSqrtA()*eph.getScaledSqrtA();
        e = eph.getScaledE();
        w = eph.getScaledOMEGA();
        w0 = eph.getScaledOMEGA0();
        wdot = eph.getScaledOMEGAP();
        cuc = eph.getScaledCUC();
        cus = eph.getScaledCUS();
        crc = eph.getScaledCrc();
        crs = eph.getScaledCRS();
        i0 = eph.getScaledI0();
        idot = eph.getScaledIDOT();
        toe = eph.getScaledTOE();


        Tk = m_currentGPSTime - toe;
        if( Tk > 302400 )
            Tk -= 604800;
        else if( Tk < -302400 )
            Tk += 604800;

        Mk = m0 + (sqrt(mu)/sqrt(pow(a,3))+dn)*Tk;

        Ek = solveKepler(Mk,e);

        Vk = atan((sqrt(1-e*e)*sin(Ek))/(cos(Ek)-e));

        Uk = w + Vk + cuc*cos(2*(w+Vk)) + cus*sin(2*(w+Vk));

        Rk = a*(1-e*cos(Ek)) + crc*cos(2*(w+Vk)) + crs*sin(2*(w+Vk));

        Ik = i0 + idot*Tk + cic*cos(2*(w+Vk)) + cis*sin(2*(w+Vk));

        Lk = w0 + (wdot-we)*Tk - we*toe;



    }


}

double SatManager::solveKepler(double Mk, double e)
{
    double Ek = 0.0;
    double Y = 0.0;

    do
    {
        Y = keplerEccFunction(Mk,e,Ek);
        Ek -= Y/keplerEccDerivative(e,Ek);
    }while(Y > cpow(10,-12));

    return Ek;
}
