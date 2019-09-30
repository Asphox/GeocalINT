#include "cstatuslabel.h"

CStatusLabel::CStatusLabel(QWidget* parent)
    :QLabel(parent)
{
    setText("●");
    setFont(QFont("Arial",20,QFont::Bold));
    update();
}

void CStatusLabel::update()
{
    QColor color;
    switch(status)
    {
        case STATUS::DISCONNECTED: color = Qt::red; break;
        case STATUS::CONNECTED: color = Qt::green; break;
        case STATUS::TRANSFERING: color = Qt::green; break;
    }
    QPalette tmpPalette = palette();
    tmpPalette.setColor( foregroundRole(), color );
    setPalette(tmpPalette);
}
