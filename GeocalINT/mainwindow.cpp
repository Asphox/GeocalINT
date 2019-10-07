#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_statusBar = new CStatusBar(&m_serialManager,this);
    setStatusBar(m_statusBar);

    m_map = new CMap("qrc:/Map.qml",this);
    ui->TW_mainTabs->addTab(m_map,tr("Map"));

    connect(&m_serialManager,SIGNAL(dataReceived(QByteArray)),&m_gnssParser,SLOT(parseData(QByteArray)));
    connect(&m_gnssParser,&GNSS::Parser::NMEAFrameGLL_created,m_map,&CMap::onNMEAFrameGLLCreated);

}

MainWindow::~MainWindow()
{
    delete ui;
}

