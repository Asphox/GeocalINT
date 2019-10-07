#ifndef CSTATUSLABEL_H
#define CSTATUSLABEL_H

#include <QLabel>
#include <QTimer>

//===============================
// Custom Label representing the connection status of the serial port
//===============================
class CSerialStatus : public QLabel
{
    Q_OBJECT
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

private slots:
    void onTransferingTimerEnded();
};

#endif // CSTATUSLABEL_H
