#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "video.h"
#include "webrtcwebpage.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setFixedSize(400,400);
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

void MainWindow::on_pushButton1_clicked()
{
    addVideoChat("1.html");
}

void MainWindow::on_pushButton2_clicked()
{
    addVideoChat("2.html");
}

void MainWindow::on_pushButton3_clicked()
{
    addVideoChat("3.html");
}

void MainWindow::on_pushButton4_clicked()
{
    addVideoChat("4.html");
}

void MainWindow::webAllow(QUrl q, QWebEnginePage::Feature f) {
    ui->videoChat->page()->setFeaturePermission(q, f,
    QWebEnginePage::PermissionGrantedByUser);
}

void MainWindow::addVideoChat(QString path)
{
    QString fullPath = QString("https://huatedianshang.com:8443/demos/demo_multiparty%1").arg(path);
    ui->stackedWidget->setCurrentWidget(ui->videoChatPage);
    ui->videoChatPage->layout()->setMargin(0);

    WebRTCWebPage *page = new WebRTCWebPage(this);
    ui->videoChat->setPage(page);
    connect(ui->videoChat->page(), SIGNAL(featurePermissionRequested(QUrl,QWebEnginePage::Feature)),SLOT(webAllow(QUrl,QWebEnginePage::Feature)));
    ui->videoChat->setUrl(QUrl(fullPath));
    ui->back->raise();
}

void MainWindow::on_back_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
    ui->videoChat->page()->deleteLater();
}
