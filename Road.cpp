#include "road.h"
#include "qmath.h"
#include "QLineF"
#include "city.h"

Road::Road(City c1,City c2,int crowd)
{
    city1 = c1;
    city2 = c2;
    isCrowd = crowd;
    line = QLineF(c1.addr, c2.addr);
    if(isCrowd == 1)
        //拥塞路段为正常路段的五倍
        length = line.length() * 5;   //如果拥堵，则长度*5
    else
        length = line.length();
    //color = QColor(0,0x00,0);
    color = "black";
}
Road::Road()
{

}
