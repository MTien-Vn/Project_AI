#include<bits/stdc++.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#define MAX 50
using namespace std;



int n;
vector <int> check;
fstream outfile;

int Test(int x){
    for (int i = 0; i < check.size(); i++){
        if (x == check[i]){
            return 1;
        }
    }
    return 0;
}


void input(){
    srand(time(NULL));
    outfile.open("./order.txt", ios::app);
    outfile<< MAX <<"\n";
    outfile.close();
    for(int i = 1; i <= MAX ; i++){
        outfile.open("./order.txt", ios::app);
        int x = rand()%(MAX-1+1)+1;
        if (Test(x) == 1){
            i--;
        }else{
            check.push_back(x);
            outfile<< x <<" ";
        }
        outfile.close();

    }
}


int main(){
    input();
    return 0;
}




