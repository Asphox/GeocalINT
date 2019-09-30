#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QPalette>

#include "ccombobox.h"
#include "cstatuslabel.h"
#include "serialmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CComboBox* CB_serialPortList = nullptr;
    QComboBox* CB_serialBaudRate = nullptr;
    QPushButton* PB_serialConnect = nullptr;
    CStatusLabel* LB_serialStatus = nullptr;

    SerialManager serialManager;

    void initStatusBar();
    void initQtConnections();

public slots:
    void updateSerialPortList();
    void updatePB_serialConnect();
    void serialConnect();
};
#endif // MAINWINDOW_H
