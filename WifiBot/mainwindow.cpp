#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    speed = value ;
    QString s = QString::number(speed) ;
    ui->viewSpeed->setText("Vitesse : " + s);
}

// Avancer
void MainWindow::on_pushUp_pressed()
{

}

// Tourner à droite
void MainWindow::on_pushRight_pressed()
{

}

// Tourner à gauche
void MainWindow::on_pushLeft_pressed()
{

}

// Reculer
void MainWindow::on_pushDown_pressed()
{

}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Q)
    {
        ui->pushLeft->animateClick();
    }
    else if (event->key() == Qt::Key_Z)
    {
        ui->pushUp->animateClick();
    }
    else if (event->key() == Qt::Key_D)
    {
        ui->pushRight->animateClick();
    }
    else if (event->key() == Qt::Key_S)
    {
        ui->pushDown->animateClick();
    }
    else if (event->key() == Qt::Key_8)
    {
        ui->pushCamUp->animateClick();
    }
    else if (event->key() == Qt::Key_4)
    {
        ui->pushCamLeft->animateClick();
    }
    else if (event->key() == Qt::Key_5)
    {
        ui->pushCamDown->animateClick();
    }
    else if (event->key() == Qt::Key_6)
    {
        ui->pushCamRight->animateClick();
    }
    else {
        QMainWindow::keyPressEvent(event);
    }
}
