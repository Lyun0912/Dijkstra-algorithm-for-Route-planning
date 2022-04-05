#include "city.h"
#include "QColor"

City::City(int n, QPointF a)
{
    name = n;
    addr = a;
    //color = QColor(0,0x00,0);
    color = "black";
}
City::City()
{

}
