#include "cmap.h"

CMap::CMap(const QString& qmlUrl, QWidget* parent) : QQuickWidget(parent)
{
    setSource(QUrl(qmlUrl));
    rootContext()->setContextProperty(parent->objectName(),parent);
    setResizeMode(QQuickWidget::SizeRootObjectToView);
}

void CMap::onNMEAFrameGLL_created(GNSS::NMEAFrameGLL gll)
{
    /*QQmlEngine engine;
    QQmlComponent component(&engine,"qrc:/Map.qml");
    QObject* object = component.create();

    QMetaObject::invokeMethod(object,"onNMEAFrameGLL",Q_ARG(QVariant,gll.getLat().toFloat()),Q_ARG(QVariant,gll.getLon().toFloat()));
*/
    rootObject()->setProperty("lat",gll.getLat());
    rootObject()->setProperty("lon",gll.getLon());
}
