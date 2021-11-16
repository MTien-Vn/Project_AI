#include<bits/stdc++.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#define RANDOM 10000
using namespace std;

typedef pair<int, int> ii;


int n;
vector <ii> check;
fstream outfile;

int Test(int x, int y){
    for (int i = 0; i < check.size(); i++){
        if (check[i].first == x && y == check[i].second){
            return 1;
        }
    }
    return 0;
}


void input(){
    cin >> n;
    srand(time(NULL));
    for(int i = 1; i <= n ; i++){
        outfile.open("./vertices1.txt", ios::app);
        int x = rand()%(RANDOM-1+1)+1;
        int y = rand()%(RANDOM-1+1)+1;
        if (Test(x,y) == 1){
            i--;
        }else{
            check.push_back(ii(x,y));
            outfile<< x <<" "<<y <<"\n";
        }
        outfile.close();

    }
}


int main(){
    input();
    return 0;
}



