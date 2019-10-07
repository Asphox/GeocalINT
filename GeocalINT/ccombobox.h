#ifndef CCOMBOBOX_H
#define CCOMBOBOX_H

#include <QComboBox>

//============================
//  Custom combobox with clicked event added
//============================
class CComboBox : public QComboBox
{
    Q_OBJECT
public:
    CComboBox(QWidget* parent = nullptr);
    void showPopup() override;

signals:
    void clicked();
};

#endif // CCOMBOBOX_H
