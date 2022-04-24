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
}

MainWindow::~MainWindow()
{
    delete ui;
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

    brush.setColor(QColor(0,0,255));
    painter.setBrush(brush);

        cor = rand()%4;
          //cout << cor << endl;

        if(cor == 0){
            brush.setColor(QColor(0,0,255));
            painter.setBrush(brush);
        }else if(cor == 1){
            brush.setColor(QColor(0,255,0));
            painter.setBrush(brush);
        }else if(cor == 2){
            brush.setColor(QColor(255,0,0));
            painter.setBrush(brush);
        }else if(cor == 3){
            brush.setColor(QColor(255,255,0));
            painter.setBrush(brush);
        }

        x_location = rand()%(x_bigger-x_smaller+1) + x_smaller;
        y_location = rand()%(y_bigger-y_smaller+1) + y_smaller;

        painter.drawEllipse(x_location,y_location,90,90);
        gettimeofday(&tempo_inicial, NULL);


    QWidget::paintEvent(e);

}

void MainWindow::keyPressEvent(QKeyEvent *k)
{

    tecla = k->key();
    if(tecla == 'w' || tecla == 'W' && cor == 2){
        score+=1;
        //cout << "vermelho" << endl;
    }else if(tecla == 'a' || tecla == 'A' && cor == 1){
        score+=1;
        //cout <<"verde"<<endl;
    }else if(tecla == 'd' || tecla == 'D' && cor == 0){
        score+=1;
        //cout << "azul"<<endl;
    }else if(tecla == 's' || tecla == 'S' && cor == 3){
        score+=1;
        //cout<<"amarelo"<<endl;
    }else{
        score-=1;
    }

    gettimeofday(&tempo_final, NULL);
    tmili = (int) (1000 * (tempo_final.tv_sec - tempo_inicial.tv_sec) + (tempo_final.tv_usec - tempo_inicial.tv_usec) / 1000); // para transformar em milissegundos
    tmili_final = (float) tmili/1000;
    cout << tmili_final <<endl;
    QString b;
    b.setNum(tmili_final);
    ui->textBrowser_time->setText(b);

    ui->lcdNumber->display(score);
    //cout << tecla << endl;

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

