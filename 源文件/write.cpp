#include <fstream>
#include <iostream>
#include <stdio.h>
#include "write.h"
#include "Group.h"
#include "request.h"

using namespace std;

void write(Unit w, RequestVec z){
    remove("result.txt");
    ofstream outfile;
    outfile.open("result.txt",ios::out);
    outfile<<w.value<<" "<<w.first<<" "<<w.second<<"\n";
    for(int i = 0; i < re_num; i++){
        outfile<<z[i].id<<" "<<z[i].bw<<"\n";
//        cerr<<z[i].id<<" "<<z[i].bw<<"111"<<endl;
        if(w.path[i] == 1){
            for(unsigned int j = 0; j < z[i].Road_1.size(); j++){
                if(j < z[i].Road_1.size()-1){
                    outfile<<z[i].Road_1[j]<<" ";
//                    cerr<<z[i].Road_1[j]<<" "<<"222";
                }
                else{
                    outfile<<z[i].Road_1[j]<<"\n";
//                    cerr<<z[i].Road_1[j]<<"333"<<endl;
                }
            }
        }


        if(w.path[i] == 2){
            for(unsigned int j = 0; j < z[i].Road_2.size(); j++){
                if(j < z[i].Road_2.size()-1){
                    outfile<<z[i].Road_2[j]<<" ";
                }
                else{
                    outfile<<z[i].Road_2[j]<<"\n";
                }
            }
        }

        if(w.path[i] == 3){
            for(unsigned int j = 0; j < z[i].Road_3.size(); j++){
                if(j < z[i].Road_3.size()-1){
                    outfile<<z[i].Road_3[j]<<" ";
                }
                else{
                    outfile<<z[i].Road_3[j]<<"\n";
                }
            }
        }

    }
    return;
}
