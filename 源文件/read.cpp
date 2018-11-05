#include "read.h"
#include <string.h>

using namespace std;

//从一个字符串里提取出里面的数字，数字间以空格分割，然后放入vector里
void string_to_num(string s, vector<int> &shu){
	const char *d = " ";
	char* data;
	char *p;
	int num;
	int len = s.length();
	data = (char *)malloc((len+1)*sizeof(char));
	s.copy(data,len,0);
    p = strtok(data,d);
	while(p){
		num = atoi(p);
		shu.push_back(num);
        p = strtok(NULL,d);
	}
	return;
}

void Read_From_File(Graph &g, int &a, int &b, RequestVec &c, int &d, int &e){
	ifstream infile;
    infile.open("grditopoAndRequest.txt",ios::in);//打开文件
	if(!infile.is_open())
		cout << "Open file failure" << endl;//如果文件打开失败，输出文字

	//读取gridtopo信息
	int Vertexnum,Edgenum;					//读取文件里的图的顶点数量和边的数量
	infile>>Vertexnum>>Edgenum;
	a = Vertexnum;
	b = Edgenum;
	int start,end,weight;//读取每行数据，start代表每条链路起点，end代表每条链路终点，weight代表权重
	for(int i = 0; i < Edgenum; i++){//给邻接矩阵图赋值
		infile>>start>>end>>weight;
		g.vexs[start][end] = weight;
		g.vexs[end][start] = weight;
	}

	//读取request信息
	int Requestnum,Roadnum;
	infile>>Requestnum>>Roadnum;
	d = Requestnum;
	e = Roadnum;
    Request rRequest;
	for(int j = 0; j < Requestnum; j++){//循环Requestnum次，读取所有业务请求
        int rid, rbw,temp;//读取id号和请求带宽
        infile>>rid>>rbw>>temp;
		rRequest.id = rid;
		rRequest.bw = rbw;
		string s1,s2,s3;//读取每个业务请求中的三个备用路径
		getline(infile,s1);
		getline(infile,s2);
		getline(infile,s3);
		string_to_num(s1,rRequest.Road_1);
		string_to_num(s2,rRequest.Road_2);
		string_to_num(s3,rRequest.Road_3);
        c.push_back(rRequest);
        memset(&rRequest, 0, sizeof(Request));
	}

	//关闭文件
	infile.close();
	return;
}
