#include<bits/stdc++.h>
#define MAX 100000


using namespace std;

struct Node
{
    int x, y;
};

struct Edge
{
    int node;
    int length;
    Edge() {};
    Edge(int n, int l) : node(n), length(l) {};
};

struct Path {
    int last_node;
    int length;
    Path() {};
    Path(int n, int l) : last_node(n), length(l) {};
    bool operator < (const Path &other) const {
        return length > other.length;
    }
};


int node_cnt, edge_cnt;
Node node[MAX];
vector<Edge> adjacent_edges[MAX]; // list of adjacent edges of each node i
int dist[MAX]; // distance from node i to node j
int orders[MAX];
int order_cnt;

void readOrder()
{
    FILE *f = freopen("order.txt", "r", stdin);;
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

void readMap()
{
    FILE *f = freopen("map.txt", "r", stdin);
    if (f == NULL)
    {
        printf("Can not open this file\n");
    }
    else
    {
        fscanf(f, "%d %d", &node_cnt, &edge_cnt);
        for (int i = 0; i < node_cnt; i++)
        {
            fscanf(f, "%d %d", &node[i].x, &node[i].y);
        }

        for (int i = 0; i < edge_cnt; i++)
        {
            int node1, node2, length;
            cin >> node1 >> node2 >> length;
            // add adjacent edges
            adjacent_edges[node1 - 1].push_back(Edge(node2 - 1, length));
            adjacent_edges[node2 - 1].push_back(Edge(node1 - 1, length));
        }
    }
    fclose(f);
}


void dijkstra(int startnode, int endnode,int *count_node, int *distance)
{
    long long visited_node_cnt = 0;
    startnode = startnode - 1;
    endnode = endnode - 1;
    // Init
    priority_queue<Path> q;
    for(int i = 0; i < node_cnt; ++i)
        dist[i] = INT_MAX;
    // Start from startnode
    dist[startnode] = 0;
    q.push(Path(startnode, dist[startnode]));
    // Start Algorithm
    while(!q.empty()) {
        int cur_node = q.top().last_node;
        int cur_length = q.top().length;
        q.pop();
        //Exit if found destination node
        if(cur_node == endnode) {
            break;
        }
        // Skip if path come to node was change after we push the old path to priority queue
        if (dist[cur_node] != cur_length) continue;
        // Traverse list of adjacent edges
        for(int i = 0; i < adjacent_edges[cur_node].size(); ++i) {
            visited_node_cnt ++;
            Edge e = adjacent_edges[cur_node][i];
            if (dist[e.node] > cur_length + e.length) {
                dist[e.node] = cur_length + e.length;
                q.push(Path(e.node, dist[e.node]));
            }
        }
    }
    *count_node = visited_node_cnt;
    *distance = dist[endnode];
}


int main()
{
    readMap();
    readOrder();
    FILE *fp = fopen("Dj.txt", "w");

    int x,y;
    int count_node = 0;
    int time_limit = 0;
    int start = 1;
    int count = 1;
    int time_work = 8*60;
    dijkstra(start,orders[0],&x,&y);
    queue<int> q;
    q.push(start);
    q.push(orders[0]);
    q.push(y);
    count_node += x;
    time_limit += y;
    printf("%d\n", x);
    if(time_limit < time_work){
        for(int i = 0; i < order_cnt; i++){
            dijkstra(orders[i],orders[i+1],&x,&y);
            count_node += x;
            time_limit += y;
            if(time_limit < time_work){
                printf("%d\n", x);
                if(i != order_cnt - 1) {
                    count++;
                    q.push(orders[i]);
                    q.push(orders[i+1]);
                    q.push(y);
                }
                else break;
            }
            else {
                count_node -= x;
                break;
            }
        }
    }
    //printf("%d", count_node);

    //Print to file out
    fprintf(fp, "%d\n", count);
    while (!q.empty())
    {
        for (int i = 0; i < 3 ; i++ ){
            fprintf(fp, "%d " , q.front());
            q.pop();
        }
        fprintf(fp,"\n");
    }
    
    fclose(fp);
    return 0;
}