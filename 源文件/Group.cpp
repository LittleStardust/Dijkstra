#include <string.h>
#include <iostream>
#include "Group.h"

using namespace std;

double pv = 0.1;				//变异概率为0.1

//生成一个1~3的随机整数
int Random_Integer(){
	return rand()%3 + 1;
}


//目标函数
void evaluate(Graph &tu,Graph &working_tu, int R_num, int C_num, Unit &one){
    double value = 0.0000;
	for(int i = 0; i < R_num; i++){
		for(int j = 0; j < C_num; j++){
			if(tu.vexs[i][j] != 0){
                double temp_value = ((double)working_tu.vexs[i][j])/(tu.vexs[i][j]);
                if(value > temp_value){
                    one.first = i;
                    one.second = j;
                }
                value = (value>temp_value ? value : temp_value);
			}
		}
	}
    one.value = value*100;
    return;
}


//初始化种群函数，随机生成一个种群
Group::Group(){
    best_one.value = 100.00;
    best_gen = 0;
    best_one.first = 0;
    best_one.second = 0;
    for(int i = 0; i < unit_num; i++){
        for(int j = 0; j < re_num; j++){
            group[i].path[j] = Random_Integer();
        }
    }
}

//建立working_tu
void build_working_tu(Graph &temp_tu, Unit &plan, RequestVec re){
	for(int m = 0; m < re_num; m++){        //逐条处理每条业务
		if(plan.path[m] == 1){
            for(unsigned int n = 0; n < re[m].Road_1.size()-2; n++){
                temp_tu.vexs[re[m].Road_1[n]][re[m].Road_1[n+1]] += re[m].bw;
			}
		}
        if(plan.path[m] == 2){
            for(unsigned int n = 0; n < re[m].Road_2.size()-2; n++){
                temp_tu.vexs[re[m].Road_3[n]][re[m].Road_2[n+1]] += re[m].bw;
            }
        }
        if(plan.path[m] == 3){
            for(unsigned int n = 0; n < re[m].Road_3.size()-2; n++){
                temp_tu.vexs[re[m].Road_3[n]][re[m].Road_3[n+1]] += re[m].bw;
            }
        }
	}
    return;
}

void Group::assess(Graph &_grid){
    Graph working_grid;
    for(int k = 0; k < unit_num; k++){
        working_grid = Graph();
        build_working_tu(working_grid,group[k],re);
        evaluate(_grid, working_grid, MAXVEX, MAXVEX,group[k]);
    }
    return;
}

//对种群中的每个个体，根据其适应度的值进行排序
void Group::unit_sort(){
	for(int i = 0; i < unit_num; i++)
        {
            for(int j = i+1; j < unit_num; j++)
            {
				if(group[i].value > group[j].value)
                {
                    Unit temp;
                    memcpy(&temp, &group[i], sizeof(Unit));
                    memcpy(&group[i], &group[j], sizeof(Unit));
                    memcpy(&group[j], &temp, sizeof(Unit));
                }
            }
        }
    return;
}

//交叉
Unit Group::cross(Unit &Father, Unit &Mother){
	int l = rand()%re_num;
	int r = rand()%re_num;
	if(l > r)
		swap(l, r);
//	bool flag[re_num] = {};
//	for(int i = l; i <= r; i++){
//		flag[Father.path[i]] = true;
//	}
	//建立子代
	Unit son;
	int pos = 0;
	for(int i = 0; i < l; i++)
        {
//            while(flag[Mother.path[pos]])
//                pos++;
			son.path[i] = Mother.path[pos++];
        }

	for(int i = l; i <= r; i++)
		son.path[i] = Father.path[i];
	for(int i = r+1; i < re_num; i++)
        {
//			while(flag[Mother.path[pos]])
//                pos++;
			son.path[i] = Mother.path[pos++];
        }

        return son;
}

//突变
void Group::mutation(Unit &t){
	double proport = (rand() % 100)/100;

	if(proport > pv)
		return;
	int one = rand()%re_num;
	int two = rand()%re_num;

    while(two == one)
		two = rand()%re_num;

    swap(t.path[one], t.path[two]);
    return;
}

//进化
void Group::evolution(Graph &__grid){
	for(int i = 0; i < genmax; i++){        //进化genmax次

		if(i > threshold)
			pv *= pv_multiple;
		
        assess(__grid);							//评估

		unit_sort();						//根据评估结果排序

		if(best_one.value > group[0].value)
            {
                memcpy(&best_one, &group[0], sizeof(Unit));
                best_gen = i;
            }

		for(int j = 0; j+2 < unit_num; j+=3)
                group[j+2] = cross(group[j], group[j+1]);

//		for(int j = 0; j < re_num; j++)//变异(从1开始，保留最优)
//                mutation(group[j]);
        cout<<"gen num is:"<<i<<"      "<<best_one.value<<endl;
	}
    return;
}
