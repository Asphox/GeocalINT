#ifndef MAP_H
#define MAP_H

#include <QQuickWidget>
#include <QSettings>
#include <QQmlContext>

class Map : public QQuickWidget
{
public:
    Map(QUrl url, QWidget* parent);

    void test();
};

#endif // MAP_H
