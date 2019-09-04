//
// Created by Aleksei Keisel on 2019-06-01.
//

#include <iostream>
#include <vector>
using namespace std;

#ifndef AISD_PROJECT_3_GRAPH_H
#define AISD_PROJECT_3_GRAPH_H


class Graph{

public:

    Graph(int V, char * input);
    ~Graph();

    bool get_result();

private:
    int ** adj_matrix;
    char * input;
    int V;
    int max_nodes;

    vector<vector<int>> connected;
    vector<int> num_of_nodes;
    vector<int> graph_num_of_nodes;
    int * visited;

    bool result;

    void input_to_matrix();

    void custom_split(int start_v, int graph_num);

    bool is_full(int order);
    bool is_cycle(int order);

    void find_all_graphs();
    void find_max_node();
    void find_num_of_colors();

};


#endif //AISD_PROJECT_3_GRAPH_H
