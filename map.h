#include <vector>

#ifndef __MAP_H__
#define __MAP_H__

#define EMPTY_MAP_ERROR -1
#define NOT_EXITST_NODE -2
#define CREATE_MAP_ERROR 0
#define CREATE_MAP_SUCCESS 1

using namespace std;

struct Node
{
    int coX;
    int coY;
    double distance;
    double time;
    int id;
};

int createMap(char *fileName, vector<Node> map[]);
void printMap(vector<Node> map[], int numberNode);
int countNumberNodeInMap(char fileName[]);

#endif