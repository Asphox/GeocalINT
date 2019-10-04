#ifndef CMAP_H
#define CMAP_H

#include <QQuickWidget>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQmlComponent>
#include "nmeaframe.h"

class CMap : public QQuickWidget
{
    Q_OBJECT
public:
    CMap(const QString& qmlUrl, QWidget* parent = nullptr);

public slots:
    void onNMEAFrameGLL_created(GNSS::NMEAFrameGLL);
};

#endif // CMAP_H
