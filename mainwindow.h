#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include "mapform.h"
#include "city.h"
#include "road.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void dijkstra(int u, int v);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    MapForm *mapform;

    int start1 = -1;//乘车人起点
    int end1 = -1;//乘车人终点
    int hobby = -1; //乘车人偏好
    int start2 = -1;//拼车人起点
    int end2 = -1;//拼车人终点
    int path[14][14]; //path[i][j]记录i到j路径上，顶点j的前驱。

};

#endif // MAINWINDOW_H
