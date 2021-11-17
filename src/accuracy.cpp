#include<bits/stdc++.h>

#include "accuracy.h"

using namespace std;

vector<int> readFile(char* fileName){
    FILE* fp;
    vector<int> data;
    fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf("Cant read file\n");
        return data;
    }
    else
    {
        char dataRow[10];
        while (fgets(dataRow, 100, fp) != NULL)
        {
            int node1, node2, value;
            fscanf(fp, "%d %d %d", &node1, &node2, &value);
            data.push_back(value);
            
        }
        fclose(fp);
        return data;
    }
}

float accuracy(char* fileNameAStart, char* fileNameDj){
    vector<int> dataAStart = readFile(fileNameAStart); 
    int numberRowAStart = dataAStart.size();
    if(numberRowAStart == 0){
        return (float)IO_ERROR;
    }

    vector<int> dataDj = readFile(fileNameDj); 
    int numberRowDj = dataDj.size();
    if(numberRowDj == 0){
        return (float)IO_ERROR;
    }
    float expect = 0;
    if(numberRowAStart < numberRowDj){
        for (int i = 0; i < numberRowAStart; i++)
        {
            float result = dataAStart[i] - dataDj[i];
            if(result < 0){
                printf("Data error, row: %d in file result\n", i+1);
                return ACCURACY_ERROR;
            }
            expect += result / dataDj[i];
        }
        
        return (1- expect / numberRowAStart)*100;
    }
    else{
        printf("Number row in A* > number row in Dj\n");
        return (float)ACCURACY_ERROR;
    }
}