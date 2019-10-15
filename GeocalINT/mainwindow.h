#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "serialmanager.h"
#include "cstatusbar.h"
#include "cmap.h"
#include <GNSS/gnssparser.h>
#include <GNSS/gnss.h>

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

private:
    Ui::MainWindow *ui;

    SerialManager m_serialManager;
    GNSS::Parser  m_gnssParser;
    CStatusBar*   m_statusBar;
    CMap*         m_map;
};
#endif // MAINWINDOW_H
