#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    statusBar = new CStatusBar(&serialManager,this);
    setStatusBar(statusBar);
}


MainWindow::~MainWindow()
{
    delete ui;
}

