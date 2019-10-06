#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "serialmanager.h"
#include "cstatusbar.h"
#include "cmap.h"
#include "gnssparser.h"
#include "gnss.h"

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

    SerialManager serialManager;
    GNSS::Parser  gnssParser;
    CStatusBar*   statusBar;
    CMap*         map;

    void initMainWidget();

public slots:
};
#endif // MAINWINDOW_H
