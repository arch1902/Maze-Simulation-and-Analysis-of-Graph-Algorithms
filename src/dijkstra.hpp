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
using namespace std;
extern string s;

string mape[24][24];


void to_vector(string ss){
    for(int i= 0;i<24;i++){
        for(int j = 0;j<24;j++){
            mape[i][j] = ss[24*i+j];
        }
        cout<<i<<endl;
    }
}
// path from P1 to P2
vector<Point> getpath(Point p1, Point p2){
    cout<<"here1";
    to_vector(s);
    cout<<"here2";
    int dist[24][24];
    bool visited[24][24];
    int max_dis = 1000000;
    for(int i= 0;i<24;i++){
        for(int j = 0;j<24;j++){
            dist[i][j] = max_dis;
            visited[i][j] = false;
        }
    }
    dist[p1.y][p1.x] = 0;
    visited[p1.y][p1.x] = true;
    const Point dirs[4] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    queue<Point> que;
    que.push(p1);
    bool fg = false;
    while (!que.empty()) {
      const Point p = que.front();
      que.pop();
      int d = dist[p.y][p.x] + 1;
      for (const Point &dir : dirs) {
        const Point e = p + dir;
        if (e.x < 0 || e.x >= 24 || e.y < 0 || e.y >= 24 || visited[e.y][e.x] || mape[e.y][e.x] == "#") {
          continue;
        }
        visited[e.y][e.x] = true;
        dist[e.y][e.x] = d;
        if (e == p2){
            fg = true;
            break;
        }
        que.push(e);
      }
      if (fg){break;}
    }
    vector<Point> out;
    Point j = p2;
    out.push_back(j);
    while(dist[j.y][j.x]!= 0){
        for (const Point &dir : dirs) {
            const Point e = j + dir;
            if (dist[e.y][e.x] == dist[j.y][j.x]-1){
                j = e;
                out.push_back(j);
                break;
            }
        }
    }
    reverse(out.begin(),out.end());
    return out;
}