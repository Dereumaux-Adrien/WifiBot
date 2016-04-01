#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    speed = 120 ;
    upOn = false ;
    downOn = false ;
    leftOn = false ;
    rightOn = false ;
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
    upOn = true ;
    if(rightOn && !leftOn && !downOn){
        robot.setRightSpeed(speed/4);
        robot.setLeftSpeed(speed);
        robot.setCommandFlag(80);
    }else if(!rightOn && leftOn && !downOn){
        robot.setRightSpeed(speed);
        robot.setLeftSpeed(speed/4);
        robot.setCommandFlag(80);
    }else{
        robot.setRightSpeed(speed);
        robot.setLeftSpeed(speed);
        robot.setCommandFlag(80);
    }

}

void MainWindow::on_pushUp_released()
{
    upOn = false ;
    robot.setRightSpeed(0);
    robot.setLeftSpeed(0);
    robot.setCommandFlag(0);
}

// Tourner à droite
void MainWindow::on_pushRight_pressed()
{
    rightOn = true ;
    if(upOn && !downOn && !leftOn){
        robot.setRightSpeed(speed/4);
        robot.setLeftSpeed(speed);
        robot.setCommandFlag(80);
    }
    else if(!upOn && downOn && !leftOn){
        robot.setRightSpeed(speed/4);
        robot.setLeftSpeed(speed);
        robot.setCommandFlag(0);
    }
    else{
        robot.setRightSpeed(speed);
        robot.setLeftSpeed(speed);
        robot.setCommandFlag(64);
    }
}

    void MainWindow::on_pushRight_released()
    {
        rightOn = false ;
        robot.setRightSpeed(0);
        robot.setLeftSpeed(0);
        robot.setCommandFlag(0);
    }

    // Tourner à gauche
    void MainWindow::on_pushLeft_pressed()
    {
        leftOn = true ;
        if(upOn && !downOn && !rightOn){
            robot.setRightSpeed(speed);
            robot.setLeftSpeed(speed/4);
            robot.setCommandFlag(80);
        }else if(!upOn && downOn && !rightOn){
            robot.setRightSpeed(speed);
            robot.setLeftSpeed(speed/4);
            robot.setCommandFlag(0);
        }else{
            robot.setRightSpeed(speed);
            robot.setLeftSpeed(speed);
            robot.setCommandFlag(16);
        }
    }

    void MainWindow::on_pushLeft_released()
    {
        leftOn = false ;
        robot.setRightSpeed(0);
        robot.setLeftSpeed(0);
        robot.setCommandFlag(0);
    }

    // Reculer
    void MainWindow::on_pushDown_pressed()
    {
        downOn = true ;
        if(rightOn && !leftOn && !upOn){
            robot.setRightSpeed(speed/4);
            robot.setLeftSpeed(speed);
            robot.setCommandFlag(0);
        }else if(!rightOn && leftOn && !upOn){
            robot.setRightSpeed(speed);
            robot.setLeftSpeed(speed/4);
            robot.setCommandFlag(0);
        }else{
            robot.setRightSpeed(speed);
            robot.setLeftSpeed(speed);
            robot.setCommandFlag(0);
        }
    }

    void MainWindow::on_pushDown_released()
    {
        downOn = false ;
        robot.setRightSpeed(0);
        robot.setLeftSpeed(0);
        robot.setCommandFlag(0);
    }

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Q)
    {
        on_pushLeft_pressed();
    }
    else if (event->key() == Qt::Key_Z)
    {
        on_pushUp_pressed();
    }
    else if (event->key() == Qt::Key_D)
    {
       on_pushRight_pressed();
    }
    else if (event->key() == Qt::Key_S)
    {
        on_pushDown_pressed();
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

void MainWindow::keyReleaseEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Q)
    {
        on_pushLeft_released();
    }
    else if (event->key() == Qt::Key_Z)
    {
        on_pushUp_released();
    }
    else if (event->key() == Qt::Key_D)
    {
        on_pushRight_released();
    }
    else if (event->key() == Qt::Key_S)
    {
        on_pushDown_released();
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


void MainWindow::on_pushCamUp_pressed()
{
    robot.moveCamera('U');
}

void MainWindow::on_pushCamLeft_pressed()
{

}

void MainWindow::on_pushCamDown_pressed()
{

}

void MainWindow::on_pushCamRight_pressed()
{

}
