#ifndef CITY_H
#define CITY_H
#include<QPointF>
#include<QColor>

class City
{
public:
    QPointF addr;
    int name;//编号
    QString color;

    City();
    City(int n, QPointF a);
};


#endif // CITY_H
