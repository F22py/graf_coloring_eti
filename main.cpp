#include "Graph.h"

using namespace std;

int main() {
    unsigned int rows;
    scanf("%u", &rows);

    for (unsigned int i =0; i < rows; i++){
        int vertex;
        scanf("%i", &vertex);

        char * matrix_input = new char[vertex*vertex];
        scanf("%s", matrix_input);

        Graph my_graph = Graph(vertex, matrix_input);

        delete[] matrix_input;
        matrix_input = nullptr;


        if (my_graph.get_result()){
            printf("True\n");
        }else{
            printf("False\n");
        }

    }

    return 0;
}