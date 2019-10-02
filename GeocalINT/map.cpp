#include "map.h"

Map::Map(QUrl url, QWidget* parent):QQuickWidget(parent)
{
    rootContext()->setContextProperty(parent->objectName(), parent);
    setSource(QUrl(url));
}
