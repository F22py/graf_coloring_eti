//
// Created by Aleksei Keisel on 2019-06-01.
//

#include "Graph.h"

Graph::Graph(int V, char * input){
    this->V = V;
    this->input = input;
    this->max_nodes = 0;

    this->adj_matrix = new int * [this->V];
    for (int k =0; k < this->V; k++)
        adj_matrix[k] = new int[this->V];

    this->visited = new int[this->V];
    for (int i = 0; i < this->V; i++)
        this->visited[i] = false;


    this->input_to_matrix();
    this->find_all_graphs();

}

Graph::~Graph(){
    for (int k =0; k < this->V; k++){
        delete[] this->adj_matrix[k];
        this->adj_matrix[k] = nullptr;
    }


    delete[] this->adj_matrix;
    this->adj_matrix = nullptr;

    delete[] this->visited;
    this->visited = nullptr;
}

bool Graph::get_result(){
    return this->result;
}


void Graph::input_to_matrix(){
    int counter = 0;
    for (int j =0; j < this->V; j++){
        int pairs = 0;
        for (int k =0; k < this->V; k++){
            this->adj_matrix[j][k] = (this->input[counter++] - 48);
            if (this->adj_matrix[j][k] == 1){
                pairs++;
            }
        }
        this->num_of_nodes.push_back(pairs);
    }
}

bool Graph::is_full(int order){
    for (int i = 0; i < this->connected[order].size(); i++){
        int current_vertex = this->connected[order][i];
        if (this->num_of_nodes[current_vertex] != this->connected[order].size() - 1){
            return false;
        }
    }
    return true;
}

bool Graph::is_cycle(int order){
    if (this->connected[order].size() % 2 == 0){
        return false;
    }
    for (int i = 0; i < this->connected[order].size(); i++){
        int current_vertex = this->connected[order][i];
        if (this->num_of_nodes[current_vertex] != 2){
            return false;
        }
    }
    return true;
}


void Graph::find_all_graphs(){
    int num = 0;
    int g_num = 0;

    while (!this->visited[num]){
        this->connected.resize(this->connected.size() + 1);
        this->custom_split(num, g_num);

        if (this->connected[g_num].size() != this->V){
            for (int i = 0; i < this->V; ++i){
                if (!this->visited[i]){
                    num = i;
                    break;
                }
            }
        }
        g_num++;
    }

    this->find_max_node();
    this->find_num_of_colors();

}

void Graph::find_max_node(){
    for (int i = 0; i < this->V; i++){
        if (this->num_of_nodes[i] > this->max_nodes){
            this->max_nodes = this->num_of_nodes[i];
        }
    }

    for (int i = 0; i < this->connected.size(); i++){
        int max = 0;
        for (int k = 0; k < this->connected[i].size(); k++){
            int curr_vertex = this->connected[i][k];
            if (this->num_of_nodes[curr_vertex] > max){
                max = this->num_of_nodes[curr_vertex];
            }
        }
        this->graph_num_of_nodes.push_back(max);
    }
}

void Graph::find_num_of_colors(){
    vector<int> colors;

    for (int i = 0; i < this->connected.size(); ++i){
        if (is_full(i) || is_cycle(i)){
            colors.push_back(this->graph_num_of_nodes[i] + 1);
        }else{
            colors.push_back(this->graph_num_of_nodes[i]);
        }
    }


    for (int j = 0; j < colors.size(); ++j) {
        if (colors[j] > this->max_nodes){
            this->result = true;
            return;
        }
    }
    this->result = false;
}

void Graph::custom_split(int start_v, int graph_num){
    visited[start_v] = true;
    this->connected[graph_num].push_back(start_v);

    for (int i =0; i < this->V; i++){
        if (this->adj_matrix[start_v][i] == 1){
            if (!visited[i]){
                this->custom_split(i, graph_num);
            }
        }
    }
}

