#ifndef SATMANAGER_H
#define SATMANAGER_H

#include <QObject>
#include <QMap>
#include <QPair>
#include <QElapsedTimer>
#include <GNSS/UBX/AID/ubxframeaid_eph.h>
#include <serialmanager.h>
#include <Utils/mathphy.h>
#include <Eigen/Dense>
#include <cmap.h>


namespace GNSS
{
    class SatManager : public QObject
    {
        Q_OBJECT
    public:
        explicit SatManager(CMap* map, SerialManager& serialManager, QObject *parent = nullptr);

    signals:

    public slots:
        void onUBX_EPH(GNSS::UBXFrameAID_EPH);
        void onNAV_TIMEGPS(GNSS::UBXFrameNAV_TIMEGPS);
        void updateEphemeris();
        void updateGPSTime();

    private:

        double m_currentGPSTime = 0.0;
      //  QElapsedTimer m_elapsedTimeSinceLastEphUpdate;
        QTimer m_timerEph;
        QTimer m_timerGPSTime;
        CMap* m_map;
        SerialManager& m_serialManager;
        QMap<uint32_t,GNSS::UBXFrameAID_EPH> m_detectedSatEphemeris;
        void updateQML();

        void updatePos();

        Eigen::Vector3d calcCartesianSatPos(double theta1, double theta2, double theta3, double rk);

        double solveKepler(double Mk, double e);

        double solveKepler2(double Mk, double e);

        double keplerEccFunction(double Mk, double e, double x)
        {
            return Mk + e*sin(x) - x;
        }

        double keplerEccDerivative(double e, double x)
        {
            return e*cos(x) - 1;
        }
    };
}

#endif // SATMANAGER_H
