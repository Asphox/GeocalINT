#ifndef CCOMBOBOX_H
#define CCOMBOBOX_H

#include <QComboBox>

//Modified QComboBox : clicked signal added

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
