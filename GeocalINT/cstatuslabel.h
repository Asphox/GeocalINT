#ifndef CSTATUSLABEL_H
#define CSTATUSLABEL_H

#include <QLabel>

class CStatusLabel : public QLabel
{

public:
    enum class STATUS
    {
        DISCONNECTED,
        CONNECTED,
        TRANSFERING
    };

    CStatusLabel(QWidget* parent = nullptr);

    inline void setStatus( STATUS status ){ this->status = status; update(); }
    inline STATUS getStatus() const { return status; }

private:
    STATUS status = STATUS::DISCONNECTED;

    void update();
};

#endif // CSTATUSLABEL_H
