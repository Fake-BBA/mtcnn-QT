#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bbaMain=new BBA_MainThread();

    bbaMain->cp_ui=ui;
    bbaMain->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}
