#ifndef SATMANAGER_H
#define SATMANAGER_H

#include <QObject>
#include <QMap>
#include <QPair>
#include <GNSS/UBX/AID/ubxframeaid_eph.h>
#include <cmap.h>

namespace GNSS
{
    class SatManager : public QObject
    {
        Q_OBJECT
    public:
        explicit SatManager(CMap* m_map, QObject *parent = nullptr);

    signals:

    public slots:
        void onUBX_EPH(GNSS::UBXFrameAID_EPH);
    private:
        CMap* m_map;
        QMap<uint32_t,GNSS::UBXFrameAID_EPH> m_detectedSatEphemeris;
        void updateQML();
    };
}

#endif // SATMANAGER_H
