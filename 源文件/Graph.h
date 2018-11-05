//#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

#define MAXVEX	500

using namespace std;

class Graph
{
public:
//    int vexs[MAXVEX][MAXVEX];
    vector<vector<int> > vexs;
    Graph();
    ~Graph();
};

#endif // GRAPH_H
