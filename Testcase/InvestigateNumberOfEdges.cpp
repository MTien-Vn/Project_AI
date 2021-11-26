#include <bits/stdc++.h>
#include <string.h>
#include <vector>
using namespace std;

int check[1000000];
vector<int> a[1000000];
int n,m;
int Count[1000000];
void input(){

   cin >> n >> m;
   for (int i = 1; i <= m ; i++){
     int x,y;
     cin >> x >> y;
     a[x].push_back(y);
     a[y].push_back(x);
   }

}



void number_path_from_i_to_f(int index,int i, int f){
    for (int j = 0 ; j < a[i].size() ; j ++){
        if(a[i][j] == f){
            Count[index]++;
            //cout << "Count[" << index<<"] = " << Count[index] << endl;
        }else {
            if(check[a[i][j]] == 0){
                check[a[i][j]] = 1;
                number_path_from_i_to_f(index,a[i][j],f);
                check[a[i][j]] = 0;
            }
        }
    }
}


void ans(){
    for(int i = 1; i < n ;i++){
        for(int j = i+1; j <= n; j++){
            fill(check, check+n, 0);
            check[i] = 1;
            number_path_from_i_to_f(i,i,j);
        }
    }
    double res = 0;
   for(int i = 1; i < n ;i++){
        res += Count[i];
    }
    cout << res*2/(n*(n-1));
}

/*
20 24
1 3
2 3
3 4
3 5
3 20
4 5
4 6
5 6
5 7
5 16
5 20
6 7
7 11
7 14
8 9
9 10
9 11
12 14
13 14
14 16
15 16
17 18
18 20
19 20

*/


int main(){
    input();
    ans();
    return 0;
}
