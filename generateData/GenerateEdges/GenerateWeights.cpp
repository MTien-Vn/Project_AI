#include<bits/stdc++.h>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <fstream>
#define MAX 100
#define RANDOM 20
#define MAX_DIST 100
using namespace std;

typedef pair<int, int> ii;


int i = 1;
int check[1000000];
vector<ii> edges;
vector<ii> vertices;
int a[10] = {5 , 10, 15 , 20, 25, 30 ,35,40, 45, 60 };
fstream inVerticesfile,inEdgefile, outfile;

void input(){
    // Read vertices
    inVerticesfile.open("../GenerateVertices/vertices.txt", ios::in);
     while(!inVerticesfile.eof()){
        int x,y;
        inVerticesfile >> x >> y;
        vertices.push_back(ii(x,y));
        cout << x<< " " << y << endl;
    }
    inVerticesfile.close();

    // Read Edge
    inEdgefile.open("./SortedLine.txt", ios::in);
     while(!inEdgefile.eof()){
        int x,y;
        inEdgefile >> x >> y;
        edges.push_back(ii(x,y));
        //cout << x<< " " << y << endl;
    }
    inEdgefile.close();
}

double Distance(ii a , ii b){
    return sqrt((pow(a.first - b.first, 2) + pow(a.second - b.second,2))*1.0);
}

void generateWeight(){
    outfile.open("./output.txt", ios::app);
    outfile << MAX << " " << edges.size() << "\n";
    for (int i = 0; i < vertices.size(); i++ ){
        outfile << vertices[i].first << " " << vertices[i].second << endl;
    }
    for (int i = 0 ; i < edges.size(); i++){
        int x = edges[i].first;
        int y = edges[i].second;
        double dist = sqrt(Distance(vertices[x-1], vertices[y-1]));
        int actual_dist = rand()%(60-5+1)+5;
        outfile << x <<" " << y << " " << (int)(actual_dist)<< endl;
    }
    outfile.close();
}

int main(){
    srand(time(NULL));
    input();
    generateWeight();
    return 0;
}




