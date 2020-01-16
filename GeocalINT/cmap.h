#ifndef CMAP_H
#define CMAP_H

#include <QQuickWidget>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQuickItem>
#include <QTimer>
#include <GNSS/NMEA/nmeaframe.h>
#include <GNSS/UBX/AID/ubxframeaid_eph.h>
#include <QList>

//=========================
//  Custom widget handling the QML based geomap
//=========================
class CMap : public QQuickWidget
{
    Q_OBJECT
public:
    CMap(const QString& qmlUrl, QWidget* parent = nullptr);

public slots:
    //===========================
    // Slot called when an GLL NMEA Frame is constructed
    //===========================
    void onNMEAFrameGLLCreated(GNSS::NMEAFrameGLL);


    //===========================
    // Slot called when an UBX AID-EPH frame is constructed
    //===========================
    void onUBXFrameAID_EPHCreated(GNSS::UBXFrameAID_EPH);


    void updateSatQML(const QMap<uint32_t,GNSS::UBXFrameAID_EPH>&);
    void test();
};

#endif // CMAP_H
