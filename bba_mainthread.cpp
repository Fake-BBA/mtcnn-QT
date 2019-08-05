#include "bba_mainthread.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <QImage>
#include <iostream>
#include <qdebug.h>
#include <QTime>
#include "MTCNN-light/src/network.h"
#include "MTCNN-light/src/mtcnn.h"
#include <time.h>


using namespace std;
using namespace cv;
BBA_MainThread::BBA_MainThread()
{

}

void BBA_MainThread::run()
{
    Ui::MainWindow *ui=(Ui::MainWindow*)this->cp_ui;

    //Mat image = imread("4.jpg");
    //mtcnn find(image.rows, image.cols);
    clock_t start;
    start = clock();

    //find.findFace(image);

    VideoCapture capture(0);    // 打开摄像头
    if(!capture.isOpened())    // 判断是否打开成功
    {
        cout << "open camera failed. " << endl;

    }

    //用于计时
    QTime head,tail;
    int finishTime=0,sum=0,count=0;

    Mat mat,matShow,matTemp,matTemp2;

    QImage Img;

    capture>>mat;
    mtcnn find(mat.rows, mat.cols);
    cout<<"rows:"<<mat.rows<<"cols:"<<mat.cols<<endl;
    //单线程便于控制程序执行时间,有利于模拟嵌入式处理能力
    while(1)
    {
        head=QTime::currentTime();
        capture>>mat;
        //image.copyTo(matTemp);

        mat.copyTo(matTemp);
        find.findFace(matTemp);
        cvtColor(matTemp, matShow, COLOR_BGR2RGB);//颜色空间转换
        if (mat.channels() == 3)//RGB Img
        {
            Img = QImage((const uchar*)(matShow.data), matShow.cols, matShow.rows, matShow.cols * matShow.channels(), QImage::Format_RGB888);
        }
        else//Gray Img
        {
            Img = QImage((const uchar*)(matShow.data), matShow.cols, matShow.rows, matShow.cols*matShow.channels(), QImage::Format_Indexed8);
        }
        ui->ImageShow->setPixmap(QPixmap::fromImage(Img));

        tail=QTime::currentTime();
        finishTime=1000 * (tail.second()-head.second())+ (tail.msec()-head.msec());
        finishTime=1000/finishTime;
        sum+=finishTime;
        if(++count>=10)
        {
            count=0;
            sum=sum/10;
            QString str=QString::number(sum,10);
            ui->m_FPS->setText(str);
            sum=0;
        }
    }
}
