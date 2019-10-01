#ifndef CMAP_H
#define CMAP_H

#include <QQuickWidget>
#include <QQmlContext>

class CMap : public QQuickWidget
{
public:
    CMap(const QString& qmlUrl, QWidget* parent = nullptr);
};

#endif // CMAP_H
