#include<bits/stdc++.h>

using namespace std;

int random(int l, int r) {
    return l + (rand() % (r - l + 1));
}

int main() {
    ofstream out("order.input");
    srand(time(NULL));
    int n = random(1000, 2000);
    out<<n<<endl;
    for(int i = 1 ; i<=n ; i++) {
        int id = random(1,100);
        out<<id<<" ";
    }
    return 0;
}
