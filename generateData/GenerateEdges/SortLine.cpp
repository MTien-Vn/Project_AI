#include<bits/stdc++.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#define MAX 100
using namespace std;

typedef pair<int, int> ii;


int i = 1;
int check[1000000];
vector<ii> edges;
vector<ii> vertices;
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
    infile.open("./Line.txt", ios::in);
    while(!infile.eof()){
        int x,y;
        infile >> x >> y;
        check[x] = 1;
        check[y] = 1;
        if (x < y ){
            edges.push_back(ii(x,y));
        }else{
            edges.push_back(ii(y,x));
        }
        //cout << x<< " " << y << endl;
    }
    infile.close();
    infile.open("../GenerateVertices/vertices.txt", ios::in);
    while(!infile.eof()){
        int x,y;
        infile >> x >> y;
        vertices.push_back(ii(x,y));
        //cout << x<< " " << y << endl;
    }
    infile.close();
}


int Distance(ii a , ii b){
    return pow(a.first - b.first, 2) + pow(a.second - b.second,2);
}

void Sort(){
    while(i <= MAX){
        if (check[i] == 0){
            int index = i-1;
            ii x = vertices[index];
            int y;
            int min_dist = 1e9;
            for (int j = 0 ; j < vertices.size(); j++){
                int dist = Distance(x, vertices[j]);
                if(dist != 0 && min_dist > dist ){
                    min_dist = dist;
                    y = j+1;
                }
            }
            check[i] = 1;
            if(i > y){
                edges.push_back(ii(y,i));
            }else{
                edges.push_back(ii(i,y));
            }
        }
        i++;
    }
    sort(edges.begin(), edges.end(), comp);
    for (int v = 1; v <= MAX; v++ ){
        cout <<v <<" " << check[v] << endl;
    }
}

void output(){
    outfile.open("./SortedLine.txt", ios::app);
    for(int i = 0; i < edges.size() ; i++){
        outfile << edges[i].first << " " << edges[i].second << endl;
    }
    outfile.close();
}

int main(){
    input();
    Sort();
    output();
    return 0;
}




