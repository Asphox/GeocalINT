#ifndef CMAP_H
#define CMAP_H

#include <QQuickWidget>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQuickItem>
#include <QTimer>
#include <GNSS/NMEA/nmeaframe.h>

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
};

#endif // CMAP_H
