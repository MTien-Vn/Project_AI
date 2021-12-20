#include<bits/stdc++.h>

using namespace std;

struct Edge {
    int node;
    double length;
    Edge() {};
    Edge(int n, double l) : node(n), length(l) {};
};

struct Path {
    int last_node;
    double point;
    Path() {};
    Path(int n, int p) : last_node(n), point(p) {};
    bool operator < (const Path &other) const {
        return point > other.point;
    }
};

struct NodeDetails {
    double f, g, h;
    int parent_node;
    bool is_closed;
    NodeDetails() {
        f = g = h = FLT_MAX;
        parent_node = -1;
        is_closed = false;
    };
    NodeDetails(double _f, double _g, double _h, int _parent, bool _closed) {
        f = _f;
        g = _g;
        h = _h;
        parent_node = _parent;
        is_closed = _closed;
    };
};

const int MAXN = 1e5+10;

int node_cnt, edge_cnt, order_cnt;
vector<Edge> adjacent_edges[MAXN]; // list of adjacent edges of each node i
pair<int,int> coord[MAXN]; // Coordinate of nodes
int order_des[MAXN]; // Destinations of orders
vector<vector<pair<int,double> > > result; // Output data
NodeDetails node_details[MAXN]; // details info of nodes


void read_input(){
    ifstream map_inp("map.txt");
    ifstream order_inp("order.txt");

    map_inp >> node_cnt >> edge_cnt;
    for(int i = 1; i <= node_cnt; ++i) {
        int x, y;
        map_inp >> x >> y;
        coord[i] = make_pair(x,y);
    }

    for(int i = 1; i <= edge_cnt; ++i) {
        int node1, node2;
        double length;
        map_inp >> node1 >> node2 >> length;
        // add adjacent edges
        adjacent_edges[node1].push_back(Edge(node2, length));
        adjacent_edges[node2].push_back(Edge(node1, length));
    }

    map_inp.close();

    order_inp >> order_cnt;
    for(int i = 1; i <= order_cnt; ++i)
        order_inp >> order_des[i];
    order_inp.close();
}

double sqr(double x) {
    return x*x;
}

//Using angle deviation to find h(n)
// void init_heuristic(int start, int dest) {
//     pair<double, double> base_vector = make_pair(coord[start].first - coord[dest].first, coord[start].second - coord[dest].second);
//     double pi = 2 * acos(0.0);

//     for(int i = 1; i<= node_cnt; ++i) {
//         if (i == start || i == dest) {
//             node_details[i].h = 0;
//             continue;
//         }

//         pair<double, double> current_vector = make_pair(coord[i].first - coord[dest].first, coord[i].second - coord[dest].second);
//         double cos_value = (
//             (base_vector.first * current_vector.first + base_vector.second * current_vector.second)
//             / sqrt(sqr(base_vector.first) + sqr(base_vector.second))
//             / sqrt(sqr(current_vector.first) + sqr(current_vector.second))
//         );

//         double angle = acos(cos_value) * 180.0 / pi;
//         node_details[i].h = 0.15*angle;
//     }
// }

// Using Euclid Distance to find h(n)
void init_heuristic(int start, int dest) {
    for(int i = 1; i<= node_cnt; ++i) {
        node_details[i].h = 0.01*sqrt(sqr(coord[i].first - coord[dest].first) + sqr(coord[i].second - coord[dest].second));
    }
}

long long a_star(int start, int dest) {
    // Init
    long long visited_nodes_count = 0;
    priority_queue<Path> q;
    for(int i = 1; i <= node_cnt; ++i)
        node_details[i] = NodeDetails();
    // Start from node 1
    node_details[start] = NodeDetails(0,0,0,start,false);
    q.push(Path(start, 0));
    // Init H function
    init_heuristic(start, dest);
    // Start Algorithm
    while(!q.empty()) {
        int cur_node = q.top().last_node;
        q.pop();
        // Exit if found destination
        if (cur_node == dest) return visited_nodes_count;
        // Skip path if node is closed
        if (node_details[cur_node].is_closed) continue;
        node_details[cur_node].is_closed = true;
        // Traverse list of adjacent edges
        for(int i = 0; i < adjacent_edges[cur_node].size(); ++i) {
            visited_nodes_count ++;
            Edge e = adjacent_edges[cur_node][i];
            double g_new = node_details[cur_node].g + e.length;
            double h_new = node_details[e.node].h;
            double f_new = g_new + h_new;
            if (!node_details[e.node].is_closed && node_details[e.node].f > f_new) {
                node_details[e.node] = NodeDetails(f_new, g_new, h_new, cur_node, false);
                q.push(Path(e.node, f_new));
            }
        }
    }
    return visited_nodes_count;
}

void print_result() {
    // Output result
    ofstream out("result.txt");
    out << result.size() << endl;
    order_des[0] = 1;
    for (int i = 0; i < result.size(); ++i) {
        out << order_des[i] << " " << order_des[i+1] << " " << result[i].size()-1 <<" "<<result[i][0].second << endl;
        for(int j = result[i].size()-1; j > 0; --j) {
            int from = result[i][j].first;
            int to = result[i][j-1].first;
            double cost = result[i][j-1].second - result[i][j].second;
            out<<from<<" "<<to<<" "<<cost<<endl;
        }
        out<<endl;
    }
    out.close();
}

int main() {
    clock_t time_req = clock();
    read_input();

    int i = 1, start = 1, total_time = 0;
    while(i <= order_cnt) {
        a_star(start, order_des[i]);

        if (total_time + node_details[order_des[i]].g > 8*60)
            break;

        result.push_back(vector<pair<int,double> >());
        int node = order_des[i];
        while(node > 0) {
            result[result.size()-1].push_back(make_pair(node, node_details[node].g));
            if (node == node_details[node].parent_node) break;
            node = node_details[node].parent_node;
        }

        total_time += node_details[order_des[i]].g;
        start = order_des[i];
        i++;
    }

    time_req = clock() - time_req;
    cerr<<"Execution time: "<<(float)time_req/CLOCKS_PER_SEC<<endl;

    print_result();
    return 0;
}
