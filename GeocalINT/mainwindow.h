#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QtQuick>
#include <QQuickWidget>
#include <QSettings>
#include <QQmlContext>

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
    QComboBox* CB_serialPortList = nullptr;
    QComboBox* CB_serialBaudRate = nullptr;
    QPushButton* PB_serialConnect = nullptr;
    QQuickWidget* QW_mainWidget = nullptr;

    SerialManager serialManager;

    void initStatusBar();
    void initQtConnections();
    void initMainWidget();

public slots:
    void updateSerialPortList();
};
#endif // MAINWINDOW_H
