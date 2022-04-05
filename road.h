#ifndef ROAD_H
#define ROAD_H
#include<QPointF>
#include<QColor>
#include<QlineF>
#include<city.h>
class Road
{
public:
    City city1, city2;
    QLineF line;//起始、终点坐标
    double length;//长度
    QString color;
    int isCrowd; //是否拥堵，0不堵，1拥堵

    Road();
    Road(City c1,City c2,int crowd);

};

#endif // ROAD_H
