#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    initStatusBar();

    initQtConnections();

    initMainWidget();

}

void MainWindow::initMainWidget()
{
    ui->quickWidget->rootContext()->setContextProperty("w", this);
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
}

void MainWindow::initStatusBar()
{
    CB_serialPortList = new QComboBox(this);
    CB_serialPortList->addItems(serialManager.getAvailablePorts(true));
    ui->statusbar->addWidget(CB_serialPortList);

    CB_serialBaudRate = new QComboBox(this);
    CB_serialBaudRate->addItems(serialManager.getAvailableBaudrates());
    ui->statusbar->addWidget(CB_serialBaudRate);

    PB_serialConnect = new QPushButton(this);
    PB_serialConnect->setText(tr("connect"));
    ui->statusbar->addWidget(PB_serialConnect);
}


void MainWindow::initQtConnections()
{
    connect(CB_serialPortList,SIGNAL(activated(int)),this,SLOT(updateSerialPortList()));
}

void MainWindow::updateSerialPortList()
{
    CB_serialPortList->clear();
    CB_serialPortList->addItems(serialManager.getAvailablePorts(true));
}

MainWindow::~MainWindow()
{
    delete ui;
}

