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
    connect(&m_gnssParser,&GNSS::Parser::UBXFrameAID_EPH_created,this,&MainWindow::testEPH);

}

void MainWindow::testEPH( GNSS::UBXFrameAID_EPH frame )
{
    std::cout << std::dec << "svid : " << frame.getSVID() << std::endl;
    std::cout << "has ephemeris : " << frame.hasEphemeris() << std::endl;
    if( frame.hasEphemeris() )
    {
        std::cout << "Week time : " << frame.getWeekTime() << std::endl;
        std::cout << "L2 code : " << frame.getL2Code() << std::endl;
        std::cout << "URA : " << frame.getURA() << std::endl;
        std::cout << "Sat Health : " << frame.getSVHealth() << std::endl;
        std::cout << "IODC : " << frame.getIOCD() << std::endl;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

