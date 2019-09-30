#include "ccombobox.h"

CComboBox::CComboBox(QWidget* parent)
    : QComboBox(parent)
{

}

void CComboBox::showPopup()
{
    emit clicked();
    QComboBox::showPopup();
}
