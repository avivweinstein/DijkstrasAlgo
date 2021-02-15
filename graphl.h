// ------------------------------------------------graphl.h-------------------------------------------------------
//
// Programmer Name: Aviv Weinstein
// Course Section Number: CSS 502 A
// Creation Date: 2/10/21
// Date of Last Modification: 2/14/21
// Instructor Name: Professor Dong Si
// --------------------------------------------------------------------------------------------------------------------
// Purpose - This is the header file for graphl.cpp. This header file was made based on the information included
//           in the assignment 3 instructions.
// --------------------------------------------------------------------------------------------------------------------
#ifndef Graph_L
#define Graph_L
#include "nodedata.h"
#define MAXNODES 101

using namespace std;

class GraphL{
    public:
        GraphL();                   //Basic constructor for GraphL
        ~GraphL();                  //Destructor
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
        void cleanGraph();          //Utility function to help deallocate memory
        void dfsHelper(int node);   //Helps with Depth first search.
};

#endif