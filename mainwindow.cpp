#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "video.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(400,400);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QUrl url= QUrl("http://106.184.6.152:8080/demos/demo_audio_video_simple.html");
//    QUrl url = QUrl("https://106.184.6.152:8081/demos/demo_audio_video_simple.html");
//    QUrl url = QUrl("https://opentokrtc.com/111");
    Video *browser = new Video(url);
    browser->show();
    browser->setWindowTitle("视频通话");
    browser->setFixedSize(1000,400);
//    Video *w = new Video();
//    w->show();
    this->hide();
}
//Requested video size of 640x480 but got size of 2x2
//等待接入
//接通用户
