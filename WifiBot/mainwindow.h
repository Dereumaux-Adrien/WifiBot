#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QtCore>
#include "robotcontrol.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_verticalSlider_valueChanged(int value);

    void on_pushUp_pressed();

    void on_pushRight_pressed();

    void on_pushLeft_pressed();

    void on_pushDown_pressed();

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);


    void on_pushUp_released();

    void on_pushLeft_released();

    void on_pushDown_released();

    void on_pushRight_released();

    void on_pushCamUp_pressed();

    void on_pushCamLeft_pressed();

    void on_pushCamDown_pressed();

    void on_pushCamRight_pressed();

    void on_pushConnect_pressed();

    void on_pushCamFront_pressed();

    void on_pushCamUp_released();

    void on_pushCamLeft_released();

    void on_pushCamDown_released();

    void on_pushCamRight_released();

    void on_pushCamFront_released();

    void on_cameraSpeed_valueChanged(int value);

public slots:
    void MySlot();

private:
    Ui::MainWindow *ui;
    RobotControl robot;
    QTimer *timer ;
    short speed ;
    bool upOn ;
    bool downOn ;
    bool rightOn ;
    bool leftOn ;
};

#endif // MAINWINDOW_H
