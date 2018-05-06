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
    if (ui->lineEdit->text().length() > 7) {
        serverIp = ui->lineEdit->text();
    }
}

void MainWindow::webAllow(QUrl q, QWebEnginePage::Feature f) {
    ui->videoChat->page()->setFeaturePermission(q, f,
    QWebEnginePage::PermissionGrantedByUser);
}

void MainWindow::addVideoChat(QString serverIp)
{
    ui->stackedWidget->setCurrentWidget(ui->videoChatPage);
    ui->videoChatPage->layout()->setMargin(0);

    WebRTCWebPage *page = new WebRTCWebPage(this);
    ui->videoChat->setPage(page);
    connect(ui->videoChat->page(), SIGNAL(featurePermissionRequested(QUrl,QWebEnginePage::Feature)),SLOT(webAllow(QUrl,QWebEnginePage::Feature)));
    ui->videoChat->setUrl(QUrl("https://" + serverIp + ":8443/demos/demo_multiparty.html"));

    ui->back->raise();
}

void MainWindow::addAudioChat(QString serverIp)
{
    ui->stackedWidget->setCurrentWidget(ui->videoChatPage);
    ui->videoChatPage->layout()->setMargin(0);

    WebRTCWebPage *page = new WebRTCWebPage(this);
    ui->videoChat->setPage(page);
    connect(ui->videoChat->page(), SIGNAL(featurePermissionRequested(QUrl,QWebEnginePage::Feature)),SLOT(webAllow(QUrl,QWebEnginePage::Feature)));
    ui->videoChat->setUrl(QUrl("https://" + serverIp + ":8443/demos/demo_multiparty_audio.html"));

    ui->back->raise();
}

void MainWindow::on_back_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
    ui->videoChat->page()->deleteLater();
}

void MainWindow::on_pushButton1_clicked()
{
    //join audio talk
    if (serverIp == NULL)
        return;
    addAudioChat(serverIp);
}

void MainWindow::on_pushButton2_clicked()
{
    //join video talk
    if (serverIp == NULL)
        return;
    addVideoChat(serverIp);
}
