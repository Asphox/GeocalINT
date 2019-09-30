#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initStatusBar();

    initQtConnections();

}

void MainWindow::initStatusBar()
{
    CB_serialPortList = new CComboBox(this);
    updateSerialPortList();
    CB_serialPortList->addItems(serialManager.getAvailablePorts(true));
    ui->statusbar->addWidget(CB_serialPortList);

    CB_serialBaudRate = new QComboBox(this);
    CB_serialBaudRate->addItems(serialManager.getAvailableBaudrates());
    ui->statusbar->addWidget(CB_serialBaudRate);

    PB_serialConnect = new QPushButton(this);
    updatePB_serialConnect();
    PB_serialConnect->setText(tr("connect"));
    ui->statusbar->addWidget(PB_serialConnect);

    LB_serialStatus = new CStatusLabel(this);
    ui->statusbar->addPermanentWidget(LB_serialStatus);
}


void MainWindow::initQtConnections()
{
    connect(CB_serialPortList,SIGNAL(clicked()),this,SLOT(updateSerialPortList()));
    connect(CB_serialPortList,SIGNAL(currentIndexChanged(int)),this,SLOT(updatePB_serialConnect()));
    connect(PB_serialConnect,SIGNAL(clicked()),this,SLOT(updateSerialPortList()));
    connect(PB_serialConnect,SIGNAL(clicked()),this,SLOT(serialConnect()));
}

void MainWindow::updatePB_serialConnect()
{
    PB_serialConnect->setEnabled( CB_serialPortList->currentIndex() >= 0 );
}

void MainWindow::updateSerialPortList()
{
    CB_serialPortList->clear();
    CB_serialPortList->addItems(serialManager.getAvailablePorts(true));
}

void MainWindow::serialConnect()
{
    if( LB_serialStatus->getStatus() == CStatusLabel::STATUS::CONNECTED )
    {
        PB_serialConnect->setText(tr("connect"));
        CB_serialBaudRate->setEnabled(true);
        CB_serialPortList->setEnabled(true);
        LB_serialStatus->setStatus(CStatusLabel::STATUS::DISCONNECTED);
        serialManager.disconnect();
    }
    else
    {
        if( serialManager.connect(CB_serialPortList->currentText(),CB_serialBaudRate->currentText()) )
        {
            PB_serialConnect->setText(tr("disconnect"));
            CB_serialBaudRate->setEnabled(false);
            CB_serialPortList->setEnabled(false);
            LB_serialStatus->setStatus(CStatusLabel::STATUS::CONNECTED);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

