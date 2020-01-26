#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_statusBar = new CStatusBar(&m_serialManager,this);
    setStatusBar(m_statusBar);

    m_map = new CMap("qrc:/MainWindow.qml",this);

    m_satManager = new GNSS::SatManager(m_map,m_serialManager,this);

    setCentralWidget(m_map);

   // ui->TW_mainTabs->addTab(m_map,tr("MainWindow"));

    connect(&m_serialManager,SIGNAL(dataReceived(QByteArray)),&m_gnssParser,SLOT(parseData(QByteArray)));
    connect(&m_gnssParser,&GNSS::Parser::NMEAFrameGLL_created,m_map,&CMap::onNMEAFrameGLLCreated);
    //connect(&m_gnssParser,&GNSS::Parser::UBXFrameAID_EPH_created,m_map,&CMap::onUBXFrameAID_EPHCreated);
    connect(&m_gnssParser,&GNSS::Parser::UBXFrameAID_EPH_created,m_satManager,&GNSS::SatManager::onUBX_EPH);
    connect(&m_gnssParser,&GNSS::Parser::UBXFrameNAV_TIMEGPS_created,m_satManager,&GNSS::SatManager::onNAV_TIMEGPS);

}

void MainWindow::testEPH( GNSS::UBXFrameAID_EPH frame )
{
}

MainWindow::~MainWindow()
{
    delete ui;
}

