#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 10000
#define INFINITY 9999
#define TEMP 0
#define PERM 1

typedef struct node
{
    int id;
    int x, y;
} Node;

typedef struct edge
{
    Node start;
    Node end;
    int t_time;
} Edge;

int node_cnt, edge_cnt;
Node node[MAX];
Edge edge[MAX]; // list of adjacent edges of each node i
int G[MAX][MAX];
int orders[MAX];
int order_cnt;

void readMap(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Can not open this file\n");
    }
    else
    {
        char str[MAX];
        fscanf(f, "%d %d", &node_cnt, &edge_cnt);
        for (int i = 0; i < node_cnt; i++)
        {
            node[i].id = i + 1;
            fscanf(f, "%d %d", &node[i].x, &node[i].y);
        }

        for (int i = 0; i < edge_cnt; i++)
        {
            fscanf(f, "%d %d %d", &edge[i].start.id, &edge[i].end.id, &edge[i].t_time);
        }
    }
    fclose(f);
}

void printMatrix()
{
    for (int i = 0; i < node_cnt; i++)
    {
        for (int j = 0; j < node_cnt; j++)
        {
            G[i][j] = 0;
        }
    }

    for (int k = 0; k < edge_cnt; k++)
    {
        G[edge[k].start.id - 1][edge[k].end.id - 1] = edge[k].t_time;
        G[edge[k].end.id - 1][edge[k].start.id - 1] = edge[k].t_time;
    }

}

int dijkstra(int startnode, int endnode)
{
    startnode = startnode - 1;
    endnode = endnode - 1;
    int distance[MAX], pred[MAX];
    int visited[MAX], count, mindistance, nextnode, i, j;
    //pred[] stores the predecessor of each node
    //count gives the number of nodes seen so far
    //create the cost matrix
    for (i = 0; i < node_cnt; i++)
        for (j = 0; j < node_cnt; j++)
            if (G[i][j] == 0)
                G[i][j] = INFINITY;
            else
                G[i][j] = G[i][j];
    //initialize pred[],distance[] and visited[]
    for (i = 0; i < node_cnt; i++)
    {
        distance[i] = G[startnode][i];
        pred[i] = startnode;
        visited[i] = 0;
    }
    distance[startnode] = 0;
    visited[startnode] = 1;
    count = 1;
    while (count < node_cnt - 1)
    {
        mindistance = INFINITY;
        //nextnode gives the node at minimum distance
        for (i = 0; i < node_cnt; i++)
            if (distance[i] < mindistance && !visited[i])
            {
                mindistance = distance[i];
                nextnode = i;
            }
        //check if a better path exists through nextnode
        visited[nextnode] = 1;
        for (i = 0; i < node_cnt; i++)
            if (!visited[i])
                if (mindistance + G[nextnode][i] < distance[i])
                {
                    distance[i] = mindistance + G[nextnode][i];
                    pred[i] = nextnode;
                }
        count++;
    }

    //print the path and distance of each node
    
    // printf("\nDistance of node%d=%d", endnode + 1, distance[endnode]);
    // printf("\nPath=%d", endnode + 1);
    // j = endnode;
    // do
    // {
    //     j = pred[j];
    //     printf("<-%d", j + 1);
    // } while (j != startnode);
    // printf("\n");
    return distance[endnode];
}

void readOrder(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Can not open this file\n");
    }
    else
    {
        fscanf(f, "%d", &order_cnt);
        for (int i = 0; i < order_cnt; i++)
        {
            fscanf(f, "%d", &orders[i]);
        }
    }
    fclose(f);
}

void main()
{
    readMap("in.inp");
    readOrder("order.inp");
    printMatrix();
    FILE *fp = fopen("a.out", "w");

    int time_limit = 0;
    int start = 1;
    int count = 1;
    int time_work = 8*60;
    time_limit += dijkstra(start, orders[0]);
    fprintf(fp, "%d %d %d\n", start, orders[0], dijkstra(start, orders[0]));
    if(time_limit < time_work){
        for(int i = 0; i < order_cnt; i++){
            if(time_limit < time_work){
                if(i != order_cnt-1 ){
                    count++;
                    time_limit += dijkstra(orders[i],orders[i+1]);
                    fprintf(fp, "%d %d %d\n", orders[i], orders[i+1], dijkstra(orders[i],orders[i+1]));
                }
                else break;
            }
            else break;
        }
    }
    fprintf(fp, "Total order: %d\n", count);
    fclose(fp);
}