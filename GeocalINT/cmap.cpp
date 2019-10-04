#include "cmap.h"

CMap::CMap(const QString& qmlUrl, QWidget* parent) : QQuickWidget(parent)
{
    setSource(QUrl(qmlUrl));
    rootContext()->setContextProperty(parent->objectName(),parent);
    setResizeMode(QQuickWidget::SizeRootObjectToView);
}

void CMap::onNMEAFrameGLL_created(GNSS::NMEAFrameGLL gll)
{
    QQmlEngine engine;
    QQmlComponent component(&engine,"qrc:/Map.qml");
    QObject* object = component.create();

    QVariant lat = 4500.0;
    QVariant lon = 200.0;
    QMetaObject::invokeMethod(object,"onNMEAFrameGLL",Q_ARG(QVariant,lat),Q_ARG(QVariant,lon));
}
