#include <vector>

#pragma once

using namespace std;

//typedef struct request *Request;


typedef struct request//业务请求结构体
{
	int id,bw;//业务请求id号，请求带宽
	vector<int> Road_1;
	vector<int> Road_2;
	vector<int> Road_3;
}Request;

//typedef struct request  Request;
typedef vector<Request> RequestVec;//简化定义业务结构体及业务容器
