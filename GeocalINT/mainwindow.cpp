#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initMainWidget();

    statusBar = new CStatusBar(&serialManager,this);
    setStatusBar(statusBar);

}

void MainWindow::initMainWidget()
{
    ui->quickWidget->rootContext()->setContextProperty("w", this);
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

