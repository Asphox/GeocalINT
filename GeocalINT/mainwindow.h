#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "serialmanager.h"
#include "cstatusbar.h"
#include "cmap.h"
#include <GNSS/gnssparser.h>
#include <GNSS/gnss.h>
#include <GNSS/satmanager.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//======================================
//  Main Widget
//======================================


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void testEPH( GNSS::UBXFrameAID_EPH );

private:
    Ui::MainWindow *ui;

    SerialManager m_serialManager;
    GNSS::Parser  m_gnssParser;
    GNSS::SatManager* m_satManager;
    CStatusBar*   m_statusBar;
    CMap*         m_map;
};
#endif // MAINWINDOW_H
