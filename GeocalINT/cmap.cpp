#include "cmap.h"

CMap::CMap(const QString& qmlUrl, QWidget* parent) : QQuickWidget(parent)
{
    setSource(QUrl(qmlUrl));
    rootContext()->setContextProperty(parent->objectName(),parent);
    setResizeMode(QQuickWidget::SizeRootObjectToView);
}

void CMap::onNMEAFrameGLLCreated(GNSS::NMEAFrameGLL gll)
{

    rootObject()->setProperty("lat",gll.getLat());
    rootObject()->setProperty("lon",gll.getLon());
}
