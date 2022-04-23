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
    ~MainWindow();

public slots:
    void encerra();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
