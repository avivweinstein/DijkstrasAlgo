// ------------------------------------------------graphl.h-------------------------------------------------------
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

#ifndef Graph_L
#define Graph_L
#include "nodedata.h"
#define MAXNODES 101
#define MAXNODES_L 101
//We have inlcuded iostream in nodedata.h

using namespace std;

class GraphL{
    public:
        GraphL();
        ~GraphL();
        void buildGraph(ifstream& infile);
        void displayGraph();
        void depthFirstSearch();

    private:
        struct EdgeNode;            //forward reference for the compiler

        struct GraphNode{           //structs used for simplicity, use classes if desired
            EdgeNode* edgeHead;     //head of the list of edges
            NodeData* data;         //data information about each node
            bool visited;           
        };

        struct EdgeNode{
            int adjGraphNode;       //subscript of the adjacent grpah node
            EdgeNode* nextEdge;
        };

        int size;                   //size of the current graph we are searching.

        GraphNode graphNodes[MAXNODES_L];

        //Utility Functions
        void cleanGraph();
        void dfsHelper(int node);
  
};

#endif
