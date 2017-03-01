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

    void addVideoChat(QString path);

private slots:
    void on_pushButton_clicked();

    void on_pushButton1_clicked();

    void on_pushButton2_clicked();

    void on_pushButton3_clicked();

    void on_pushButton4_clicked();

    void on_back_clicked();

    void webAllow(QUrl q, QWebEnginePage::Feature f);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
