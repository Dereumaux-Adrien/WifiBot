#include "mainwindow.h"
#include "socket.h"
#include <QApplication>
#include <QPushButton>
#include <QAbstractButton>
#include <QWidget>
#include <QGridLayout>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //"192.168.1.106"
    Socket s;
    s.connectSocket();
    s.send();
    return a.exec();
}
