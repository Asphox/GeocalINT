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
#include <QtQuickWidgets>
#include <QLayout>

#include "serialmanager.h"
#include "cstatusbar.h"
#include "cmap.h"

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
    CStatusBar*   statusBar;
    CMap*         map;

    void initMainWidget();

};
#endif // MAINWINDOW_H
