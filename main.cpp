#include "mainwindow.h"
#include <QApplication>
#include <QtSerialPort/QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Example use QSerialPortInfo
      foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
          qDebug() << "Name        : " << info.portName();
          qDebug() << "Description : " << info.description();
          qDebug() << "Manufacturer: " << info.manufacturer();

          // Example use QSerialPort
          QSerialPort serial;
          serial.setPort(info);
          if (serial.open(QIODevice::ReadWrite))
              serial.close();
      }
    MainWindow w;
    w.show();

    return a.exec();
}
