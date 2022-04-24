#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *k);
    int cor;
    int score = 0;
    char tecla = 0;
    int cont = 1;
    float tmili = 0.0;
    float tmili_final = 0.0;
    float sum = 0.0;
    float average = 0.0;
    struct timeval tempo_inicial, tempo_final;
    ~MainWindow();

public slots:
    void encerra();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
