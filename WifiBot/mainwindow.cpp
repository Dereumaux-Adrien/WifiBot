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


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(MySlot()));
    timer->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::MySlot(){
    if(((float)robot.getBatterie())/1.70>100){
        ui->batLevel->setValue(100);
        ui->chargingLed->setStyleSheet("QWidget{background-color: #E42B2B;border-radius: 6px;}");
    }else {
        ui->chargingLed->setStyleSheet("QWidget{background-color: #333333;border-radius: 6px;}");
        if(((float)robot.getBatterie())/1.32>100)
            ui->batLevel->setValue(100);
        else
            ui->batLevel->setValue(((float)robot.getBatterie())/1.32);
    }

    ui->viewRightSpeed->display(robot.getRealSpeedR());
    ui->ViewLeftSpeed->display(robot.getRealSpeedL());
    ui->viewIRFL->setValue(robot.getIRFL());
    ui->viewIRBL->setValue(robot.getIRBL());
    ui->viewIRFR->setValue(robot.getIRFR());
    ui->viewIRBR->setValue(robot.getIRBR());
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
    ui->pushUp->setStyleSheet("QPushButton {background-color: #222222;border: 1px solid black;}");
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
    ui->pushUp->setStyleSheet("QPushButton {background-color: #333333;border: 1px solid black;}");
    upOn = false ;
    robot.setRightSpeed(0);
    robot.setLeftSpeed(0);
    robot.setCommandFlag(0);
}

// Tourner à droite
void MainWindow::on_pushRight_pressed()
{
    ui->pushRight->setStyleSheet("QPushButton {background-color: #222222;border: 1px solid black;}");
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
    ui->pushRight->setStyleSheet("QPushButton {background-color: #333333;border: 1px solid black;}");
    rightOn = false ;
    robot.setRightSpeed(0);
    robot.setLeftSpeed(0);
    robot.setCommandFlag(0);
}

// Tourner à gauche
void MainWindow::on_pushLeft_pressed()
{
    ui->pushLeft->setStyleSheet("QPushButton {background-color: #222222;border: 1px solid black;}");
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
    ui->pushLeft->setStyleSheet("QPushButton {background-color: #333333;border: 1px solid black;}");
    leftOn = false ;
    robot.setRightSpeed(0);
    robot.setLeftSpeed(0);
    robot.setCommandFlag(0);
}

// Reculer
void MainWindow::on_pushDown_pressed()
{
    ui->pushDown->setStyleSheet("QPushButton {background-color: #222222;border: 1px solid black;}");
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
    ui->pushDown->setStyleSheet("QPushButton {background-color: #333333;border: 1px solid black;}");
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
        on_pushCamUp_pressed();
    }
    else if (event->key() == Qt::Key_4)
    {
        on_pushCamLeft_pressed();
    }
    else if (event->key() == Qt::Key_5)
    {
        on_pushCamDown_pressed();
    }
    else if (event->key() == Qt::Key_6)
    {
        on_pushCamRight_pressed();
    }
    else if (event->key() == Qt::Key_9)
    {
        on_pushCamFront_pressed();
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
        on_pushCamUp_released();
    }
    else if (event->key() == Qt::Key_4)
    {
        on_pushCamLeft_released();
    }
    else if (event->key() == Qt::Key_5)
    {
        on_pushCamDown_released();
    }
    else if (event->key() == Qt::Key_6)
    {
        on_pushCamRight_released();
    }
    else if (event->key() == Qt::Key_9)
    {
        on_pushCamFront_released();
    }
    else {
        QMainWindow::keyPressEvent(event);
    }
}


void MainWindow::on_pushCamUp_pressed()
{
    ui->pushCamUp->setStyleSheet("QPushButton {background-color: #991058;border: 1px solid black;border-radius: 15px;}");
    robot.moveCamera('U');
}

void MainWindow::on_pushCamLeft_pressed()
{
    ui->pushCamLeft->setStyleSheet("QPushButton {background-color: #991058;border: 1px solid black;border-radius: 15px;}");
    robot.moveCamera('L');
}

void MainWindow::on_pushCamDown_pressed()
{
    ui->pushCamDown->setStyleSheet("QPushButton {background-color: #991058;border: 1px solid black;border-radius: 15px;}");
    robot.moveCamera('D');
}

void MainWindow::on_pushCamRight_pressed()
{
    ui->pushCamRight->setStyleSheet("QPushButton {background-color: #991058;border: 1px solid black;border-radius: 15px;}");
    robot.moveCamera('R');
}

void MainWindow::on_pushCamFront_pressed()
{
    ui->pushCamFront->setStyleSheet("QPushButton {background-color: #991058;border: 1px solid black;border-radius: 15px;}");
    robot.moveCamera('F');
}

void MainWindow::on_pushConnect_pressed()
{
    QString ip=ui->lineEdit->text();
    robot.setIP(ip);
    robot.connexion();
}

void MainWindow::on_pushCamUp_released()
{
    ui->pushCamUp->setStyleSheet("QPushButton {background-color: #AA2169;border: 1px solid black;border-radius: 15px;}");
}

void MainWindow::on_pushCamLeft_released()
{
    ui->pushCamLeft->setStyleSheet("QPushButton {background-color: #AA2169;border: 1px solid black;border-radius: 15px;}");
}

void MainWindow::on_pushCamDown_released()
{
    ui->pushCamDown->setStyleSheet("QPushButton {background-color: #AA2169;border: 1px solid black;border-radius: 15px;}");
}

void MainWindow::on_pushCamRight_released()
{
    ui->pushCamRight->setStyleSheet("QPushButton {background-color: #AA2169;border: 1px solid black;border-radius: 15px;}");
}

void MainWindow::on_pushCamFront_released()
{
    ui->pushCamFront->setStyleSheet("QPushButton {background-color: #AA2169;border: 1px solid black;border-radius: 15px;}");
}

void MainWindow::on_cameraSpeed_valueChanged(int value)
{
    QString s = "Vitesse : " + QString::number(value);
    ui->viewSpeedCamera->setText(s);
    robot.setCameraSpeed(value);
}
