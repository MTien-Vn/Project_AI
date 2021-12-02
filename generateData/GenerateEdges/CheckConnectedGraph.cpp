#include<bits/stdc++.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#define MAX 100
using namespace std;

typedef pair<int, int> ii;
vector<ii> edges;

int i = 1;
int visit[1000000];
vector<int> a[10001];
fstream infile,outfile;

int comp(ii a , ii b){
   if(a.first < b.first ){
      return 1;
   }else if (a.first == b.first){
      return a.second < b.second;
   }else{
       return 0;
   }
}


void input(){
    infile.open("./SortedLine.txt", ios::in);
    while(!infile.eof()){
        int x,y;
        infile >> x >> y;
        a[x].push_back(y);
        a[y].push_back(x);
        edges.push_back(ii(x,y));
    }
    infile.close();
}
void Try(int i){
    if(visit[i] == 0){
        visit[i] = 1;
        for (int x = 0; x < a[i].size(); x++){
            Try(a[i][x]);
        }
    }
}


int Distance(ii a , ii b){
    return pow(a.first - b.first, 2) + pow(a.second - b.second,2);
}


void output(){
    outfile.open("./edges.txt", ios::app);
    for(int i = 1; i <= MAX ; i++){
        if(visit[i] == 0){
            outfile << 1 << " " << i << endl;
            cout << i << endl;
        }
    }
    outfile.close();
}

int main(){
    input();
    Try(1);
    //Sort();
    output();
    return 0;
}




