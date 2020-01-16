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

}

void CMap::updateSatQML(const QMap<uint32_t, GNSS::UBXFrameAID_EPH>& m_map)
{
    QMetaObject::invokeMethod(rootObject(), "clearData");
    QVariantList list;
    for( auto it : m_map )
    {
        list << it.getSVID() << it.getIOCD() << it.getTgd() << it.getToc() << it.getF0()
             << it.getF1() << it.getF2() << it.getIODE() << it.getScaledCRS() << it.getScaledDN()
             << it.getScaledM0() << it.getScaledCUC() << it.getScaledE() << it.getScaledSqrtA()
             << it.getScaledTOE() << it.getFIT() << it.getScaledCic() << it.getScaledOMEGA0()
             << it.getScaledI0() << it.getScaledCrc() << it.getScaledOMEGA() << it.getScaledOMEGAP() << it.getScaledIDOT();
        QMetaObject::invokeMethod(rootObject(), "addData",Q_ARG(QVariant, QVariant::fromValue(list)));
        list.clear();
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

    //QMetaObject::invokeMethod(rootObject(), "addData",Q_ARG(QVariant, QVariant::fromValue(list)));
}
