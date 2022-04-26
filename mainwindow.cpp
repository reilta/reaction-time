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

    ui->lcdNumber->display(score);

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

    // habilita o anti-aliasing para que as
    // linhas sejam desenhadas sem serrilhados
    painter.setRenderHint(QPainter::Antialiasing);

    // define as props do preenchimento
    brush.setColor(QColor(255,255,255));
    brush.setStyle(Qt::SolidPattern);

    // comunica as mudancas ao objeto painter
    painter.setBrush(brush);
    // desenha um retangulo
    painter.drawRect(20,60,761, 361);

    color = rand()%4;

    vcolor[aux] = color;

    cout << "color atual: " << vcolor[aux] << endl;
    cout << "color anterior: " << vcolor[aux-1] << endl;

    if(vcolor[aux] == vcolor[aux-1]){
        vcolor[aux] = vcolor[aux-2];
    }

    if(vcolor[aux] == 0 && vcolor[aux-1] != 0){
        brush.setColor(QColor(0,0,255));
        painter.setBrush(brush);
    }else if(vcolor[aux] == 1 && vcolor[aux-1] != 1){
        brush.setColor(QColor(0,255,0));
        painter.setBrush(brush);
    }else if(vcolor[aux] == 2 && vcolor[aux-1] != 2 ){
        brush.setColor(QColor(255,0,0));
        painter.setBrush(brush);
    } else if(vcolor[aux] == 3 && vcolor[aux-1] != 3 ) {
        brush.setColor(QColor(255,255,0));
        painter.setBrush(brush);
    }

    x_location = rand()%(x_bigger-x_smaller+1) + x_smaller;
    y_location = rand()%(y_bigger-y_smaller+1) + y_smaller;

    painter.drawEllipse(x_location,y_location,90,90);
    gettimeofday(&init_time, NULL);

    QWidget::paintEvent(e);

    aux++;
}

void MainWindow::keyPressEvent(QKeyEvent *k)
{
    key = k->key();
    if(key == 'w' || key == 'W' && color == 2){
        score+=1;
    }else if(key == 'a' || key == 'A' && color == 1){
        score+=1;
    }else if(key == 'd' || key == 'D' && color == 0){
        score+=1;
    }else if(key == 's' || key == 'S' && color == 3){
        score+=1;
    }else{
        score-=1;
    }

    gettimeofday(&final_time, NULL);
    tmili = (int) (1000 * (final_time.tv_sec - init_time.tv_sec) + (final_time.tv_usec - init_time.tv_usec) / 1000); // para transformar em milissegundos
    tmili_final = (float) tmili/1000;

    QString b;
    b.setNum(tmili_final);
    ui->textBrowser_time->setText(b);

    ui->lcdNumber->display(score);
    sum += tmili_final;
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

