#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEnginePage>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addVideoChat(QString serverIp);
    void addAudioChat(QString serverIp);

private slots:
    void on_pushButton_clicked();

    void on_back_clicked();

    void webAllow(QUrl q, QWebEnginePage::Feature f);
    void on_pushButton1_clicked();

    void on_pushButton2_clicked();
private:
    QString serverIp = NULL;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
