#pragma once

#include <math.h>
#include <stdlib.h>
#include <string>
#include <queue>
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
vector<vector<string> > maze;
vector<vector<int> > visited;

int is_loop(int x, int y){
    visited[x][y] = 1;
    int ans = 1;
    if (x-1>=0 && visited[x-1][y] == 0 && maze[x-1][y] == "."){
        ans+= is_loop(x-1,y);
    }
    if (y-1>=0 && visited[x][y-1] == 0 && maze[x][y-1] == "."){
        ans+= is_loop(x,y-1);
    }
    if (x+1<24 && visited[x+1][y] == 0 && maze[x+1][y] == "."){
        ans+= is_loop(x+1,y);
    }
    if (y+1<24 && visited[x][y+1] == 0 && maze[x][y+1] == "."){
        ans+= is_loop(x,y+1);
    }
    return ans;
}


string generator(){
    srand( time(NULL));
    vector<vector<string> > t1 = maze;
    vector<vector<int> > t2 = visited;
    vector<string> temp;
    vector<vector<int> > temp3;
    vector<int> temp2;
    for(int i = 0;i<24;i++){
        temp2.push_back(0);
    }
    for(int i = 0;i<24;i++){
        temp3.push_back(temp2);
    }
    visited = temp3;
    for(int i = 0;i<24;i++){
        temp.push_back(".");
    }
    for(int i = 0;i<24;i++){
        maze.push_back(temp);
    }
    for (int i = 0;i<24;i++){
        maze[0][i] = "#";
        maze[23][i] = "#";
        if (i == 12){continue;}
        maze[i][0] = "#";
        maze[i][23] = "#";  
    }
    int j = 0;
    while (j<140){
        int x = rand()%22 + 1;
        int y = rand()%22 + 1;
        if (maze[x][y] == "#"){continue;}
        maze[x][y] = "#";
        visited = temp3;
        if(is_loop(12,0) != 485-j){
            maze[x][y] = ".";
            continue;
        }
        j+=1;
    }
    int  q = 0;
    while(q<6){
        int y = rand()%22 + 1;
        int x = rand()%22 + 1;
        if(maze[y][x]== "#"){continue;}
        maze[y][x] = "C";
        q=q+1;        
    }
    string out;
    for (auto j: maze){
        for (auto i :j){
            out += i;
        }
    }
    for (int i = 0;i<24;i++){
        for (int j = 0;j<24;j++){
            cout<< maze[i][j]<<",";
        }
        cout<<endl;
    }
    maze = t1;
    visited = t2;
    return out;
}