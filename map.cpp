#include <iostream>
#include <vector>
#include "reader.h"
#include "map.h"

using namespace std;

int const sizeMap = 16;
int mapArr[sizeMap][sizeMap];
int nodeId = 0;
int numberNodeInMap;

extern int lineNo;
extern int colNo;
extern int currentChar;

//read data of file into arr
int scan(char fileName[]){
    if (openInputStream(fileName) == IO_ERROR)
        return IO_ERROR;
    while (currentChar != EOF)  
    {   
        char value[1] = {(char)currentChar};
        mapArr[lineNo][colNo] = atoi(value);
        currentChar = readChar();
    }
    closeInputStream();
    return IO_SUCCESS;
}

int countNumberNodeInMap(char fileName[]){
    if (openInputStream(fileName) == IO_ERROR)
        return EMPTY_MAP_ERROR;
    int count = 0;
    while (currentChar != EOF)  
    {
        if(currentChar == 49){
            count++; // value = 1 --> a node
        }
        currentChar = readChar();
    }
    closeInputStream();
    return count;
}

// check (x,y) is allocate ID or not
bool isExitstNodeId(vector<Node> map[], int x, int y){
    for (int i = 0; i < numberNodeInMap; i++)
    {
        for (auto node : map[i])
        {
            if(node.coX == x && node.coY == y){
                return true;
            }
        }
        
    }
    return false;
}

// A utility function to add an edge in an
// undirected graph.
void addEdge(vector<Node> map[], Node u, Node v)
{
    u.distance = rand() % 70 + 30; // random distance in [30;100]
    u.time = rand() % 50 + 10; // random time in [10;50]
    if(!isExitstNodeId(map, u.coX, u.coY)){
        u.id = nodeId;
        nodeId++;
    }

    v.distance = u.distance; // distance from u->v = v->u
    v.time = u.time; // time from u->v = v->u
    if(!isExitstNodeId(map, v.coX, v.coY)){
        v.id = nodeId;
        nodeId++;
    }

    map[u.id].push_back(v);
    map[v.id].push_back(u);
}

int createMap(char fileName[], vector<Node> map[]){
    if(scan(fileName) == IO_ERROR){
        return CREATE_MAP_ERROR;
    }
    else{
        numberNodeInMap = countNumberNodeInMap(fileName);
        for (int row = 0; row < sizeMap; row++)
        {
            int isCreateRightEdge = 0;
            int preCoX;
            for (int col = 0; col < sizeMap; col++)
            {
                if(mapArr[row][col] == 1){
                    isCreateRightEdge ++;
                    // if detect 2 node adj
                    if(isCreateRightEdge > 1){
                        Node u,v; // u: previous node, v: current node
                        u.coX = preCoX;
                        u.coY = row; //u, v in same row

                        v.coX = col;
                        v.coY = row; // u, v in same row

                        addEdge(map, u, v);
                    }

                    preCoX = col;

                    for (int dowDirect = row + 1; dowDirect < sizeMap; dowDirect++) // detect node in next row
                    {
                        if(mapArr[dowDirect][col] == 1){
                            Node u, v;
                            u.coX = col; //u, v in same col
                            u.coY = row;

                            v.coX = col; //u, v in same col
                            v.coY = dowDirect;

                            addEdge(map, u, v);
                            break;
                        }
                    }
                    
                }
            }
            
        }
        return CREATE_MAP_SUCCESS;
    }
}

void printMap(vector<Node> map[], int numberNode){
    for (int i = 0; i < numberNode; i++)
    {
        cout << "\n Adjacency list of vertex "
             << i << "\n head ";
        for (auto node : map[i])
        {
            cout << "-> " << node.id << "(" << node.coX << ","<< node.coY << ","<< node.distance << ","<< node.time << ")" << endl;
        }
        
    }
    
}
