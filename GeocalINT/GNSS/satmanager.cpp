#include "satmanager.h"

using namespace GNSS;
using Eigen::Matrix3d;
using Eigen::Vector3d;

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

        updatePos();
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

    double phik = 0;
    double du = 0;
    double dr = 0;
    double di = 0;

    std::vector<Vector3d> cartesianSatsPos;

    for( auto& eph : m_detectedSatEphemeris )
    {
        std::cout << std::endl << eph.getSVID() << std::endl;
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
        cic = eph.getScaledCic();
        cis = eph.getScaledCis();
        i0 = eph.getScaledI0();
        idot = eph.getScaledIDOT();
        toe = eph.getScaledTOE();

        //Temps dans l'ephemeride
        Tk = m_currentGPSTime - toe;

        if( Tk > 302400 )
            Tk -= 604800;
        else if( Tk < -302400 )
            Tk += 604800;

        //Anomalie moyenne
        Mk = m0 + (sqrt(mu)/sqrt(pow(a,3))+dn)*Tk;
        //Anomalie eccentricité avec resolution Kepler
        Ek = solveKepler2(Mk,e);
        //Vraie anomalie
        Vk = atan2((sqrt(1-e*e)*sin(Ek)/(1-e*cos(Ek))),(cos(Ek)-e)/(1-e*cos(Ek)));

        phik = w+Vk;
        //Corrections harmoniques
        du = cuc*cos(2*phik) + cus*sin(2*phik);
        dr = crc*cos(2*phik) + crs*sin(2*phik);
        di = cic*cos(2*phik) + cis*sin(2*phik);


        Uk = phik + du;
        Rk = a*(1-e*cos(Ek)) + dr;
        Ik = i0 + idot*Tk + di;

        //Inclinaison
        Lk = w0 + (wdot-we)*Tk - we*toe;

        double Xp = Rk*cos(Uk);
        double Yp = Rk*sin(Uk);

        //Position du sat dans le referentiel WGS 84 ECEF
        double X = Xp*cos(Lk) - Yp*cos(Ik)*sin(Lk);
        double Y = Xp*sin(Lk) + Yp*cos(Ik)*cos(Lk);
        double Z = Yp*sin(Ik);

            std::cout << "X : " << X/1000.0 << std::endl;
            std::cout << "Y : " << Y/1000.0 << std::endl;
            std::cout << "Z : " << Z/1000.0 << std::endl;
     }


}

double SatManager::solveKepler(double Mk, double e)
{
    double Ek = 0;
    double Y = 0.0;

    do
    {
        Y = keplerEccFunction(Mk,e,Ek);
        Ek -= Y/keplerEccDerivative(e,Ek);
    }while( abs(Y) > cpow(10,-12));

    return Ek;
}

double SatManager::solveKepler2(double Mk, double e)
{
    double Ek = 0;
    for(int i=0; i<10; i++)
    {
        Ek = Mk + e*sin(Ek);
    }
    return Ek;
}

Vector3d SatManager::calcCartesianSatPos(double theta1, double theta2, double theta3, double rk)
{
    Matrix3d R1,R31,R32;
    Vector3d V(rk,0,0);
    Vector3d ret;

    R1(0,0) = 1;
    R1(1,1) = cos(theta2);
    R1(1,2) = sin(theta2);
    R1(2,1) = -sin(theta2);
    R1(2,2) = cos(theta2);

    R32(0,0) = cos(theta3);
    R32(0,1) = sin(theta3);
    R32(1,0) = -sin(theta3);
    R32(1,1) = cos(theta3);
    R32(2,2) = 1;

    R31(0,0) = cos(theta1);
    R31(0,1) = sin(theta1);
    R31(1,0) = -sin(theta1);
    R31(1,1) = cos(theta1);
    R31(2,2) = 1;

    ret = R31*R1*R32*V;

    return ret;
}
