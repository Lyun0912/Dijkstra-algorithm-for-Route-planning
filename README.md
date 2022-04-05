# Dijkstra Application
利用Dijkstra算法规划乘车人及拼车人路线。  
界面采用Qt框架，通过记录前驱的方式使Dijkstra运行后能够记录下路线所经过的点。  

# 算法的思路

Dijkstra算法采用的是一种贪心的策略，声明一个数组dis来保存源点到各个顶点的最短距离和一个保存已经找到了最短路径的顶点的集合：T，初始时，原点 s 的路径权重被赋为 0 （dis[s] = 0）。
若对于顶点 s 存在能直接到达的边（s,m），则把dis[m]设为w（s, m）,同时把所有其他（s不能直接到达的）顶点的路径长度设为无穷大。初始时，集合T只有顶点s。
然后，从dis数组选择最小值，则该值就是源点s到该值对应的顶点的最短路径，并且把该点加入到T中，OK，此时完成一个顶点，
然后，我们需要看看新加入的顶点是否可以到达其他顶点并且看看通过该顶点到达其他点的路径长度是否比源点直接到达短，如果是，那么就替换这些顶点在dis中的值。
然后，又从dis中找出最小值，重复上述动作，直到T中包含了图的所有顶点。

运行图：

![image](https://github.com/xiepl1997/Dijkstra-Application/blob/master/images/pic2.png)

![image](https://github.com/xiepl1997/Dijkstra-Application/blob/master/images/pic1.png)
