#include "cmap.h"

CMap::CMap(const QString& qmlUrl, QWidget* parent) : QQuickWidget(parent)
{
    setSource(QUrl(qmlUrl));
    rootContext()->setContextProperty(parent->objectName(),parent);
    setResizeMode(QQuickWidget::SizeRootObjectToView);
}

void CMap::onNMEAFrameGLLCreated(GNSS::NMEAFrameGLL gll)
{

    rootObject()->setProperty("latNMEA",gll.getLat());
    rootObject()->setProperty("lonNMEA",gll.getLon());
}

void CMap::onUBXFrameAID_EPHCreated(GNSS::UBXFrameAID_EPH eph)
{
    if( eph.hasEphemeris() )
    {
        std::cout << "ENVOIE" << std::endl;
        QStringList test;
        test.append("caca1");
        test.append("caca2");
        rootObject()->setProperty("listeSatellites",test);
    }
}
