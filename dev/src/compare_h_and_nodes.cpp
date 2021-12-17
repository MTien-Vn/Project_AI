#include<bits/stdc++.h>

using namespace std;

void compare_nodes_count() {
    ifstream angle("visited_nodes_angle.txt");
    ifstream euclid("visited_nodes_euclid.txt");

    // read number of order
    int angle_order_cnt = 0, euclid_order_cnt = 0;
    angle >> angle_order_cnt;
    euclid >> euclid_order_cnt;

    int n = min(angle_order_cnt, euclid_order_cnt);
    int angle_better_cnt = 0, euclid_better_cnt = 0;
    double angle_sum = 0, euclid_sum = 0;
    for(int i = 0 ; i < n ; ++i) {
        long long angle_node_cnt = 0, euclid_node_cnt = 0;
        angle >> angle_node_cnt;
        euclid >> euclid_node_cnt;

        angle_sum += angle_node_cnt;
        euclid_sum += euclid_node_cnt;

        if (angle_node_cnt < euclid_node_cnt) angle_better_cnt++;
        if (angle_node_cnt > euclid_node_cnt) euclid_better_cnt++;
    }

    cerr<<"Total nodes were traveled of h with angle: "<< angle_sum << endl;
    cerr<<"Total nodes were traveled of h with euclid: "<< euclid_sum << endl;
    cerr<<"-----------------------\n";
    cerr<<"Average nodes were traveled of h with angle: "<< angle_sum/n << endl;
    cerr<<"Average nodes were traveled of h with euclid: "<< euclid_sum/n << endl;
    cerr<<"-----------------------\n";
    cerr<<"Number of times that H with angle traveled less nodes: "<<angle_better_cnt<<endl;
    cerr<<"Number of times that H with euclid traveled less nodes: "<<euclid_better_cnt<<endl;

    angle.close();
    euclid.close();
}

bool double_equal(double a, double b) {
    double ep = 1e-8;
    if (a > b - ep && a < b + ep) return true;
    return false;
}

void compare_h_function() {
    ifstream angle("h_angle.txt");
    ifstream euclid("h_euclid.txt");

    // read number of order
    int angle_order_cnt = 0, euclid_order_cnt = 0, node_count;
    angle >> angle_order_cnt >> node_count;
    euclid >> euclid_order_cnt >> node_count;

    // for each order, compare
    bool cannot_compare = false, found_angle_better = false, found_euclid_better = false;
    for(int i = 0 ; i<min(angle_order_cnt, euclid_order_cnt); ++i) {
        int compare = 0; // -1 if h_angle < h_euclid | 1 if h_angle > h_euclid, 0 if cannot compare
        bool angle_smaller = false, euclide_smaller = false;
        // traverse all element in h[]
        for(int j = 0; j < node_count; ++j) {
            double h_angle, h_euclid;
            angle >> h_angle;
            euclid >> h_euclid;
            if (!double_equal(h_angle, h_euclid)) {
                if (h_angle < h_euclid) angle_smaller = true;
                else euclide_smaller = true;
            }
        }
        if (!(angle_smaller && euclide_smaller)) {
            if (angle_smaller) compare = -1;
            if (euclide_smaller) compare = 1;
        }
        switch(compare) {
        case -1:
            found_angle_better = true;
            break;
        case 1:
            found_euclid_better = true;
            break;
        default:
            cannot_compare = true;
            break;
        }
    }
    if (found_angle_better && found_euclid_better) cannot_compare = true;

    if (cannot_compare)
        cerr<<"Cannot compare 2 h functions\n";
    else if (found_angle_better)
        cerr<<"H function of angle is smaller \n";
    else
        cerr<<"H function of euclid is smaller \n";

    angle.close();
    euclid.close();
}

int main(){
    compare_h_function();
    cerr<<"\n==============================\n\n";
    compare_nodes_count();
    return 0;
}
