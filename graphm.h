// ------------------------------------------------bintree.h-------------------------------------------------------
//
// Programmer Name: Aviv Weinstein
// Course Section Number: CSS 502 A
// Creation Date: 
// Date of Last Modification:
// Instructor Name: Professor Dong Si
// --------------------------------------------------------------------------------------------------------------------
// Purpose - 
// --------------------------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions: 
// --------------------------------------------------------------------------------------------------------------------

#ifndef Graph_M                                 
#define Graph_M
#include "nodedata.h"
#define MAXNODES 101
//We have inlcuded iostream in nodedata.h

using namespace std;

class GraphM{
    public:
        GraphM();
        bool buildGraph(ifstream& infile);
        bool insertEdge(int fromNode, int toNode, int weight);
        bool removeEdge(int fromNode, int toNode);
        void displayAll();
        void display(int fromNode, int toNode);
        void findShortestPath();

    private:
        struct TableType {
            bool visited;   //Whether the node has been visited.
            int dist;       //Shortest distance from source known so far. Current best distance.
            int path;       //Previous node in the path to this specific node.
        };

        NodeData data[MAXNODES];            //data for graph nodes.
        int C[MAXNODES][MAXNODES];          //cost/weight array, the adjacency matrix
        int size;                           //number of nodes in the graph
        TableType T[MAXNODES][MAXNODES];    //stores visited, distance, path

        //Utility Functions
        void printAdjMatrix(); //This is just a utility function for me to see the entire adjacency matrix for a graph. Used for debug purposes.
        void getPath(int source, int dest);        //This is a utility function that calculates the path taken to reach a certain edge.
        void getWeight(int source, int dest);
  
};

#endif
