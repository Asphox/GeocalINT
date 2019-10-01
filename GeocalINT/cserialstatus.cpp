#include "cserialstatus.h"

CSerialStatus::CSerialStatus(QWidget* parent)
    :QLabel(parent)
{
    setText("●");
    setFont(QFont("Arial",20,QFont::Bold));
    update();
}

void CSerialStatus::update()
{
    QColor color;
    switch(status)
    {
        case STATUS::DISCONNECTED: color = Qt::red; break;
        case STATUS::CONNECTED: color = Qt::yellow; break;
        case STATUS::TRANSFERING:
            color = Qt::green;
            QTimer::singleShot(100,this,SLOT(onTransferingTimerEnded())); break;
    }
    QPalette tmpPalette = palette();
    tmpPalette.setColor( foregroundRole(), color );
    setPalette(tmpPalette);
}

void CSerialStatus::onTransferingTimerEnded()
{
    setStatus(STATUS::CONNECTED);
    update();
}
