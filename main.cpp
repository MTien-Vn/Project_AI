#include <iostream>
#include<vector>
#include<string.h>
#include "map.h"

using namespace std;

int main(int argc, char const *argv[])
{
    char fileName[] = "map.txt";
    int numberNodeInMap = countNumberNodeInMap(fileName);
    vector<Node> map[numberNodeInMap];
    if(createMap(fileName, map) == CREATE_MAP_ERROR){
        cout << "Create Map error" << endl;
    }else{
        printMap(map, numberNodeInMap);
    }

    return 0;
}
