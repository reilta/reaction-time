#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/time.h>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->quitButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(encerra()));
    connect(ui->resetButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(reset()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reset()
{
    score = 0;
    sum = 0;
    average = 0;
    cont = 1;
    fail = 0;

    ui->lcdNumber->display(score);
    ui->lcdNumber_2->display(fail);

    QString c;
    c.setNum(sum);
    ui->textBrowser_time->setText(c);
    c.setNum(average);
    ui->textBrowser_average->setText(c);
    QWidget ::update();
}

void MainWindow::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    QBrush brush;
    int x_location,y_location;
    int x_bigger = 690;
    int x_smaller = 21;
    int y_bigger = 330;
    int y_smaller = 61;

    painter.setRenderHint(QPainter::Antialiasing);

    brush.setColor(QColor(255,255,255));
    brush.setStyle(Qt::SolidPattern);

    painter.setBrush(brush);
    painter.drawRect(20,60,761, 361);

    brush.setColor(QColor(0,0,255));
    painter.setBrush(brush);

    color = rand()%4;

    if(color == 0){
        brush.setColor(QColor(0,0,255));
        painter.setBrush(brush);
    }else if(color == 1){
        brush.setColor(QColor(0,255,0));
        painter.setBrush(brush);
    }else if(color == 2){
        brush.setColor(QColor(255,0,0));
        painter.setBrush(brush);
    }else if(color == 3){
        brush.setColor(QColor(255,255,0));
        painter.setBrush(brush);
    }

    x_location = rand()%(x_bigger-x_smaller+1) + x_smaller;
    y_location = rand()%(y_bigger-y_smaller+1) + y_smaller;

    painter.drawEllipse(x_location,y_location,90,90);
    gettimeofday(&init_time, NULL);

    QWidget::paintEvent(e);
}

void MainWindow::keyPressEvent(QKeyEvent *k)
{
    key = k->key();
    gettimeofday(&final_time, NULL);
    if(key == 'w' || key == 'W' && color == 2){
        score+=1;
    }else if(key == 'a' || key == 'A' && color == 1){
        score+=1;
    }else if(key == 'd' || key == 'D' && color == 0){
        score+=1;
    }else if(key == 's' || key == 'S' && color == 3){
        score+=1;
    }else{
        fail+=1;
    }

    tmili = (int) (1000 * (final_time.tv_sec - init_time.tv_sec) + (final_time.tv_usec - init_time.tv_usec) / 1000);
    tsec = (float) tmili/1000;

    QString b;
    b.setNum(tsec);
    ui->textBrowser_time->setText(b);

    ui->lcdNumber->display(score);
    ui->lcdNumber_2->display(fail);
    sum += tsec;
    average = sum/cont++;

    QString c;
    c.setNum(average);
    ui->textBrowser_average->setText(c);
    QWidget ::update();
}

void MainWindow::encerra()
{
    exit(0);
}

