#ifndef CSTATUSLABEL_H
#define CSTATUSLABEL_H

#include <QLabel>

class CSerialStatus : public QLabel
{
public:
    enum class STATUS
    {
        DISCONNECTED,
        CONNECTED,
        TRANSFERING
    };

    CSerialStatus(QWidget* parent = nullptr);

    inline void setStatus( STATUS status ){ this->status = status; update(); }
    inline STATUS getStatus() const { return status; }

private:
    STATUS status = STATUS::DISCONNECTED;

    void update();
};

#endif // CSTATUSLABEL_H
