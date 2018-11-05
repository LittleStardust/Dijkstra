#include <algorithm>
#include <math.h>
#include <vector>
#include "Graph.h"
#include "request.h"

#define  re_num			1000	//编码为1000个1~3的整数
#define  unit_num		50		//群体规模
#define  ps				0.6		//进行选择的时候保存的比列
#define  pc				0.9		//交叉概率为0.9
//#define  pv			0.1		//变异概率为0.1
#define  genmax			500		//最大迭代次数
#define  threshold		300		//迭代超过300次的时候，变异概率增加
#define  pv_multiple	2		//迭代超过300次的时候，变异概率增加的倍数



//定义个体
typedef struct unit{
	int path[re_num]; //每个个体由1000位1~3的整数组成
	double value;     //每个个体的最大链路利用率
}Unit;

//定义种群group
class Group{
public:
	Unit group[unit_num];	//种群变量group
	Unit best_one;			//记录最佳方案
	int  best_gen;			//最好的一代
	Graph _grid;			//将main函数中读取了txt文件里的topo信息后建立的图传进来
	RequestVec re;			//将main函数中读取了txt文件里的request信息后的容器传进来

	//构造函数，初始化
	Group();

	//计算每个个体的适应度值
	void assess();

	//对种群中的每个个体，根据其适应度的值进行排序
	void unit_sort();

	//交叉
	Unit cross(Unit &Father, Unit &Mother);

	//突变
	void mutation(Unit &t);

	//进化
	void evolution();
};

//生成一个1~3的随机整数
int Random_Integer();

//适应度函数,参数分别为topo图，当前基因对应的图，图的行数和列数
double evaluate(Graph tu, Graph working_tu, int R_num, int C_num);

//建立working_tu
void build_working_tu(Graph &temp_tu, Unit &plan, RequestVec re);