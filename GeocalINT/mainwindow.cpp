#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    statusBar = new CStatusBar(&serialManager,this);
    setStatusBar(statusBar);

    map = new CMap("qrc:/Map.qml",this);
    ui->TW_mainTabs->addTab(map,tr("Map"));
    connect(&serialManager,SIGNAL(dataReceived(QByteArray)),&gnssParser,SLOT(parseData(QByteArray)));
    connect(&gnssParser,&GNSS::Parser::NMEAFrameGLL_created,this,&MainWindow::onNMEAGLLreceived);

}

MainWindow::~MainWindow()
{
    delete ui;
}

