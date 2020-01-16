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

    setCentralWidget(m_map);

   // ui->TW_mainTabs->addTab(m_map,tr("MainWindow"));

    connect(&m_serialManager,SIGNAL(dataReceived(QByteArray)),&m_gnssParser,SLOT(parseData(QByteArray)));
    connect(&m_gnssParser,&GNSS::Parser::NMEAFrameGLL_created,m_map,&CMap::onNMEAFrameGLLCreated);
    connect(&m_gnssParser,&GNSS::Parser::UBXFrameAID_EPH_created,this,&MainWindow::testEPH);
    connect(&m_gnssParser,&GNSS::Parser::UBXFrameAID_EPH_created,m_map,&CMap::onUBXFrameAID_EPHCreated);

}

void MainWindow::testEPH( GNSS::UBXFrameAID_EPH frame )
{
    m_map->test();
    std::cout << "====================================" << std::endl;
    std::cout << std::dec << "svid : " << frame.getSVID() << std::endl;
    std::cout << "has ephemeris : " << frame.hasEphemeris() << std::endl;
    if( frame.hasEphemeris() )
    {
        std::cout << "Week time : " << frame.getWeekTime() << std::endl;
        std::cout << "L2 code : " << frame.getL2Code() << std::endl;
        std::cout << "URA : " << frame.getURA() << std::endl;
        std::cout << "Sat Health : " << (uint16_t)frame.getSVHealth() << std::endl;
        std::cout << "IODC : " << frame.getIOCD() << std::endl;
        std::cout << "TGD : " << (float)frame.getTgd() << std::endl;
        std::cout << "TOC : " << frame.getToc() << std::endl;
        std::cout << "AF0 : " << frame.getF0() << std::endl;
        std::cout << "AF1 : " << frame.getF1() << std::endl;
        std::cout << "AF2 : " <<  (float)frame.getF2() << std::endl;
        std::cout << "IODE : " << (float)frame.getIODE() << std::endl;
        std::cout << "Crs : " << frame.getScaledCRS() << std::endl;
        std::cout << "Dn : " << frame.getScaledDN() << std::endl;
        std::cout << "M0 : " << frame.getScaledM0() << std::endl;
        std::cout << "Cuc : " << frame.getScaledCUC() << std::endl;
        std::cout << "E : " << frame.getScaledE() << std::endl;
        std::cout << "sqrtA : " << frame.getScaledSqrtA() << std::endl;
        std::cout << "TOE : " << frame.getScaledTOE() << std::endl;
        std::cout << "FIT : " << (frame.getFIT()) << std::endl;
        std::cout << "ADAO : " << (float)frame.getAODO() << std::endl;
        std::cout << "CIC : " << frame.getScaledCic() << std::endl;
        std::cout << "OMEGA0 : " << frame.getScaledOMEGA0() << std::endl;
        std::cout << "I0 : " << frame.getScaledI0() << std::endl;
        std::cout << "CRC : " << frame.getScaledCrc() << std::endl;
        std::cout << "OMEGA : " << frame.getScaledOMEGA() << std::endl;
        std::cout << "OMEGAP : " << frame.getScaledOMEGAP() << std::endl;
        std::cout << "IDOT : " << frame.getScaledIDOT() << std::endl;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

