#include <iostream>
#include <vector>
#include <stdio.h>
#include "read.h"
#include "Group.h"
#include "Graph.h"
#include "write.h"

using namespace std;

int main(){
	//读取gridtopo信息
    int Vertex_num = 0, Edge_num = 0;//读取txt文件中第一行的顶点数和链路数后赋值给此变量
    Graph grid;//建立一个图对象
    //读取request信息
    RequestVec requestinfo;//建立业务请求结构体

    //读取信息，并赋值给grid和requestinfo
    int Request_num, Road_num;
    Read_From_File(grid, Vertex_num, Edge_num, requestinfo, Request_num, Road_num);

    //建立遗传算法对象，开始遗传算法
    Group g;
    g.re	= requestinfo;
    g.evolution(grid);

    cout<<g.best_one.value<<endl;
    cout<<g.best_gen<<endl;
    write(g.best_one,requestinfo);
//    cout<<requestinfo[999].Road_3[0];

	return 0;
}
