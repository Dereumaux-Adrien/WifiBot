#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
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


private:
    Ui::MainWindow *ui;
    RobotControl robot;
    short speed ;
};

#endif // MAINWINDOW_H
