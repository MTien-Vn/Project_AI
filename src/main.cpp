#include<bits/stdc++.h>

#include "accuracy.h"

using namespace std;

int main(int argc, char const *argv[])
{
    char fileNameAStart[] = "aStart.txt";
    char fileNameDj[] = "Dj.txt";
    float result = accuracy(fileNameAStart, fileNameDj);
    if(result == IO_ERROR){
        printf("There are error in read file\n");
    }
    else if(result == ACCURACY_ERROR){
        printf("There are error in accuracy function\n");
    }
    else{
        printf("Accuracy: %lf %", result);
    }
    return 0;
}
