#include<bits/stdc++.h>

#define IO_ERROR -2
#define IO_SUCCESS -1

#define ACCURACY_ERROR 2
#define ACCURACY_SUCCESS 3

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
    int numberRowAStart = dataAStart.size() - 1;
    if(numberRowAStart == 0){
        return (float)IO_ERROR;
    }

    vector<int> dataDj = readFile(fileNameDj); 
    int numberRowDj = dataDj.size() - 1;
    if(numberRowDj == 0){
        return (float)IO_ERROR;
    }
    float expect = 0;
    if(numberRowAStart < numberRowDj){
        for (int i = 0; i < numberRowAStart; i++)
        {
            float result = dataAStart[i] - dataDj[i];
            if((result / dataDj[i]) > 1){
                printf("Time difference using A* greater than Dijitra algorithm:: %lf times, at line: %d\n", result / dataDj[i], i+2);
            }
            if(result < 0){
                printf("Data error, row: %d in file result\n", i+1);
                return ACCURACY_ERROR;
            }
            expect += result / dataDj[i];
        }
        
        return (expect / numberRowAStart)*100;
    }
    else{
        printf("Number row in A* > number row in Dj\n");
        return (float)ACCURACY_ERROR;
    }
}


int main(int argc, char const *argv[])
{
    char fileNameAStart[] = "aStart.txt";
    char fileNameDj[] = "dj.txt";
    float result = accuracy(fileNameAStart, fileNameDj);
    if(result == IO_ERROR){
        printf("There are error in read file\n");
    }
    else if(result == ACCURACY_ERROR){
        printf("There are error in accuracy function\n");
    }
    else{
        printf("Average Difference betwwen A* and Dijitra algorithm: %lf percent\n", result);
        printf("*Note: The smaller percentage of Difference betwwen A* and Dijitra algorithm, the more accuracy\n");
    }
    return 0;
}