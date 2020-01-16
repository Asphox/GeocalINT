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
        QVariantList list;
        list << eph.getSVID() << eph.getIOCD() << eph.getTgd() << eph.getToc() << eph.getF0()
             << eph.getF1() << eph.getF2() << eph.getIODE() << eph.getScaledCRS() << eph.getScaledDN()
             << eph.getScaledM0() << eph.getScaledCUC() << eph.getScaledE() << eph.getScaledSqrtA()
             << eph.getScaledTOE() << eph.getFIT() << eph.getScaledCic() << eph.getScaledOMEGA0()
             << eph.getScaledI0() << eph.getScaledCRS() << eph.getScaledOMEGA() << eph.getScaledIDOT();
        //rootObject()->setProperty("listeSatellites",test);
    }
}

void CMap::test()
{
    QVariantList list;
    list << 2 << 123 << 2.5 << 1892 << -1829
         << 2901809 << -19821 <<12 << 12980.192 << 12.990
         << 121.0 << 2190.11 << 1.0001 << 5283
         << 12111 << 0 << 21111 << 31333
         << 1412 << 99100.11 << 1991.00 << 42;
}
