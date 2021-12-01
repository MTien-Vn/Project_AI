#include<bits/stdc++.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#define MAX 100
#define Iteration 120
using namespace std;

typedef pair<int, int> ii;


int n;
vector <ii> check;
int visit[10001];
fstream outfile;

int Test(){
    for (int i = 1; i <= MAX ; i++){
        if (visit[i] == 0) return 0;
    }
    return 1;
}

void input(){
    srand(time(NULL));
    for(int i = 1; i <= Iteration ; i++){
        outfile.open("./edges.txt", ios::app);
        int y = rand()%(MAX-1+1)+1;
        int x = rand()%(MAX-1+1)+1;
        if (x == y){
            i--;
        }else{
            check.push_back(ii(x,y));
            outfile<< x <<" "<<y <<"\n";
            visit[x] = 1;
            visit[y] = 1;
        }
        outfile.close();
    }
    for (int i = 1; i <= MAX; i++){
        if(visit[i] == 0){
            int x = i;
            int y;
            do {
                y = rand()%(MAX-1+1)+1;
            }while(x == y);
            outfile.open("./edges.txt", ios::app);
            check.push_back(ii(x,y));
            outfile<< x <<" "<<y <<"\n";
            outfile.close();
            visit[i] = 1;
            visit[y] = 1;
        }
    }


}


int main(){
    input();
    cout << Test() << endl;
    cout << check.size()<<endl;
    return 0;
}




