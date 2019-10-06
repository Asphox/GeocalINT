#include "cmap.h"

CMap::CMap(const QString& qmlUrl, QWidget* parent) : QQuickWidget(parent)
{
    setSource(QUrl(qmlUrl));
    rootContext()->setContextProperty(parent->objectName(),parent);
    setResizeMode(QQuickWidget::SizeRootObjectToView);
    QTimer::singleShot(2000,this,&CMap::test);
}

void CMap::test()
{
    //QObject* it = rootObject()->findChild<QQuickItem*>("circle");
    QObject* it = rootObject();
    it->setProperty("lat",80);
}

void CMap::onNMEAFrameGLL_created(GNSS::NMEAFrameGLL gll)
{
    /*QQmlEngine engine;
    QQmlComponent component(&engine,"qrc:/Map.qml");
    QObject* object = component.create();

    QMetaObject::invokeMethod(object,"onNMEAFrameGLL",Q_ARG(QVariant,gll.getLat().toFloat()),Q_ARG(QVariant,gll.getLon().toFloat()));
*/
    rootObject()->setProperty("lat",QString(gll.getLat()).toDouble()/100.0);
    rootObject()->setProperty("lon",QString(gll.getLon()).toDouble()/100.0);
}
