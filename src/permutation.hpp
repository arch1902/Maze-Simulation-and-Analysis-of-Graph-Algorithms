#pragma once

#include <math.h>
#include <string>
#include <queue>
#include <iostream>
#include <vector>
#include <ctime>
#include "global.hpp"
#include <queue>
#include <string>
#include <algorithm>
#include "dijkstra.hpp"
#include <map> 
using namespace std;
extern Point Steiner[6];
extern vector<vector<Point>> all_paths;
extern map<string,vector<Point>> all_mutual_paths;

void get_all_mutual_paths(){
    cout<<"In here"<<endl;
    for (int i =0;i<6;i++){
        for(int j = 0;j<6;j++){
            all_mutual_paths[to_string(i)+to_string(j)] = getpath(Steiner[i],Steiner[j]);
        }
    }
}

void make_permute(){
    string  n = "12345";
    get_all_mutual_paths();
    //cout<<"In here22"<<endl;
    while (next_permutation(n.begin(), n.end())){
        vector<Point> l;
        //cout<<n<<endl;
        string v = "0" + n + "0";
        for (int i = 1;i<7;i++){
            string z = v.substr(i-1,2);
            //cout<<"\n"<<"Z    =   "<<z<<endl;
            vector<Point> temp = all_mutual_paths[z];
            for (auto j : temp){
                //cout<< "Point  "<<j.y<<" "<<j.x<<endl;
                l.push_back(j);
            }
        }
        all_paths.push_back(l);
    }


}



