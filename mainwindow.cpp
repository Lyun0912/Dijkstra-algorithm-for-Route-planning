#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "city.h"
#include "mapform.h"
#include "QMessageBox"
#include "math.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mapform = new MapForm(this);
    mapform->show();
    ui->scrollArea->setWidget(mapform);

}

MainWindow::~MainWindow()
{
    delete ui;
}

int result_path[14]; //result_path用于存储起点到终点最短路径所经过的点

//触发路线规划
void MainWindow::on_pushButton_clicked()
{
    int f1 = 0;//标记乘车人是否添加偏好，0未添加，1添加
    int f2 = 0;//标记拼车人是否被加入，0未加入，1加入
    QString str1 = ui->comboBox->currentText(); //乘车人的起点
    QString str2 = ui->comboBox_2->currentText(); //乘车人的终点
    QString str3 = ui->comboBox_3->currentText(); //拼车人的起点
    QString str4 = ui->comboBox_4->currentText();//拼车人的总点
    QString str5 = ui->comboBox_5->currentText();//偏好
    //如果终点和起点一致
    if(str1 == str2)
    {
        QMessageBox::about(NULL, "提示", "乘车人存在起点和终点一致的情况，请重新选择!");
        return;
    }
    //如果乘车人有偏好
    if(str5 != "None")
    {
        f1 = 1;
        hobby = str5.toInt(); //用hobby保存乘车人的必经点
    }
    //必经点不能为起点或者终点
    if(str5 == str1 || str5 == str2)
    {
        QMessageBox::about(NULL, "提示", "乘车人偏好与起点或终点相同，请重新选择!");
        return;
    }
    //如果拼车人的的起点或者终点没有填写输出提示
    if((str3 == "None"&&str4 != "None") ||(str3 != "None" && str4 == "None"))
    {
        QMessageBox::about(NULL, "提示", "拼车人起点终点未输入完全!");
        return;
    }
    //拼车人的起点和终点也不能一致
    if(str3 == str4 && str3 != "None" && str4 != "None")
    {
        QMessageBox::about(NULL, "提示", "拼车人存在起点和终点一致的情况，请重新选择!");
        return;
    }
    //拼车人已上车
    if(str3 != "None" && str4 != "None")
    {
        f2 = 1; //有拼车人
        start2 = str3.toInt(); //保存拼车人的起点
        end2 = str4.toInt(); //保存拼车人的终点
    }


    start1 = str1.toInt(); // 乘车人起点
    end1 = str2.toInt(); //乘车人终点

    if(f1 == 0) //无偏好
    {
        dijkstra(start1-1, end1-1); //直接计算起点到终点的最短路径
        //所有值设置为0
        memset(result_path, 0, sizeof(result_path));
        //result_path[0] = end1;

        int m = start1 - 1;
        int n = end1 - 1;
        int temp[14];
        //所有值设置为0
        memset(temp, 0, sizeof(temp));
        temp[0] = end1;
        //获取路径：根据path从终点往起点推算经过的节点
        for(int i = 1; i < 14; i++)
        {
            if(m == n)
            {
                //result_path[i] = start1 + 1;
                break;
            }
            temp[i] = path[m][n] + 1;
            n = path[m][n];
        }
        int cnt = 0;
        for(int i = 14-1; i >= 0; i--) //将顺序调正
        {
            if(temp[i] != 0)
            {
                result_path[cnt++] = temp[i];
            }
        }
    }

    if(f1 == 1) //有偏好:将偏好点设置为中间站，首先规划起点和偏好点的路线，再规划偏好点和终点的路线，最后连接。
    {
        dijkstra(start1-1, hobby-1);
        memset(result_path, 0, sizeof(result_path));
        //result_path[0] = end1;

        int temp1[14]; //第一段路径
        memset(temp1, 0, sizeof(temp1));
        //temp1[0] = hobby;

        int m = start1 - 1;
        int n = hobby - 1;
        for(int i = 0; i < 14; i++)
        {
            if(m == n)
            {
                break;
            }
            temp1[i] = path[m][n] + 1;
            n = path[m][n];
        }

        dijkstra(hobby-1, end1-1);

        int temp2[14];//第二段路径
        memset(temp2, 0, sizeof(temp2));
        temp2[0] = end1;

        m = hobby - 1;
        n = end1 - 1;
        for(int i = 1; i < 14; i++)
        {
            if(m == n)
            {
                break;
            }
            temp2[i] = path[m][n] + 1;
            n = path[m][n];
        }

        //拼接路线
        int cnt = 0;
        for(int i = 14-1; i >= 0; i--)
        {
            if(temp1[i] !=0)
            {
                result_path[cnt++] = temp1[i];
            }
        }
        for(int i = 14-1; i >= 0; i--)
        {
            if(temp2[i] != 0)
            {
                result_path[cnt++] = temp2[i];
            }
        }
    }

    int isInRouting=0; //1表示拼车人起点和终点在路线上，0 表示不在
    if(f2 == 1)//有拼车:拼车起点和终点必须在路线上，不在路线上则提示，在路线上则改变颜色
    {
        isInRouting = 0;
        for(int i = 0; i < 14; i++)
        {
            if(result_path[i] == 0)
            {
                break;
            }
            if(start2 == result_path[i])
            {
                for(int j = 0; j < 14; j++)
                {
                    if(end2 == result_path[j])
                    {
                        isInRouting = 1; //拼车人路线在乘车人路线上
                        break;
                    }
                }
            }
            if(isInRouting == 1)
                break;
        }
        if(isInRouting == 0)
        {
            QMessageBox::about(NULL, "提示", "拼车人路线不在乘车人路线上，无法拼车!");
        }
    }

    //重绘图示，将该路径在图示中标红，若有拼车路线，则将拼车路线标黄
    //先将颜色设为黑色
    for(int i = 0; i < 14; i++)
    {
        mapform->citys[i].color = "black";
    }
    for(int i = 0; i < 18; i++)
    {
        mapform->roads[i].color = "black";
    }
    //m = start1 - 1;
    for(int i = 0; ; i++)
    {
        if(result_path[i] == 0)
            break;
        //该路径中的地点标红
        mapform->citys[result_path[i]-1].color = "red";
        //该路径中的道路标红
        if(result_path[i+1] != 0)
        {
            for(int j = 0; j < 18; j++){
                int c1 = mapform->roads[j].city1.name;
                int c2 = mapform->roads[j].city2.name;
                if((c1 == result_path[i] && c2 == result_path[i+1]) || (c1 == result_path[i+1] && c2 == result_path[i]))
                {
                    mapform->roads[j].color = "red";
                    break;
                }
            }
        }
    }
    //如果有拼车路线，将点和路线标黄
    if(isInRouting == 1)
    {
        int j=0;
        //记录开始下标
        for(int i = 0; ; i++)
        {
            if(result_path[i] == start2)
            {
                j = i;
                break;
            }
        }
        //将点和路线标黄
        for(;;j++)
        {
            mapform->citys[result_path[j]-1].color = "yellow";
            if(result_path[j] != end2)
            {
                for(int k = 0; k < 18; k++){
                    int c1 = mapform->roads[k].city1.name;
                    int c2 = mapform->roads[k].city2.name;
                    if((c1 == result_path[j] && c2 == result_path[j+1]) || (c1 == result_path[j+1] && c2 == result_path[j]))
                    {
                        mapform->roads[k].color = "yellow";
                        break;
                    }
                }
            }
            else
            {
                mapform->citys[result_path[j]-1].color = "yellow";
                break;
            }
        }
    }
    //刷新图示
    mapform->update();

}

double dis[14]; //存储估计值
int flag[14]; //flag[i]代表i这个点有没有被当做源点去搜索过，1为有，0为没有
//最短路径算法，用path[][]记录最短路线前驱
void MainWindow::dijkstra(int u, int v)
{
    QString str = "";
    for(int i = 0; i < 14; i++)
    {
        dis[i] = 0x3f3f3f3f;
    }
    for(int i = 0; i < 14; i++)
    {
        for(int j = 0; j < 14; j++)
        {
            path[i][j] = 0;
        }
    }
    memset(flag, 0, sizeof(flag));
    int start = u; //从源点搜索
    flag[start] = 1;
    dis[start] = 0;

    for(int i = 0; i < 14; i++)
    {
        if(i != start)
        {
            if(dis[i] > mapform->matrix[u][i]) //记录前驱
            {
                path[u][i] = u;
            }
            dis[i] = qMin(dis[i], mapform->matrix[u][i]);
        }
    }

    for(int i = 0; i < 14-1; i++)
    {
        int minn = 0x3f3f3f3f;
        //int temp = start;
        for(int j = 0; j < 14; j++)
        {
            if(flag[j] == 0 && minn > dis[j])
            {
                minn = dis[j];
                start = j;
            }
            if(i == 0)
            {
                path[u][start] = u;
            }
        }
        flag[start] = 1;
        //path[u][start] = temp;
        for(int j = 0; j < 14; j++)
        {
            if(flag[j] == 0)
            {
                if(dis[j] > dis[start] + mapform->matrix[start][j]) //记录前驱
                {
                    path[u][j] = start;
                }
                dis[j] = qMin(dis[j], dis[start] + mapform->matrix[start][j]);
            }
        }
    }
}






















