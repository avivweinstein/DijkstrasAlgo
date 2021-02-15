// ------------------------------------------------graphm.cpp-------------------------------------------------------
// Programmer Name: Aviv Weinstein
// Course Section Number: CSS 502 A
// Creation Date: 2/1/21
// Date of Last Modification: 2/14/21
// Instructor Name: Professor Dong Si
// --------------------------------------------------------------------------------------------------------------------
// Purpose - 
// --------------------------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions: 
//      INDEX 0 is not used!
// --------------------------------------------------------------------------------------------------------------------
#include "graphl.h"
#define MAXNODES 101
#define inf 10000
#include <iomanip>

// ---------------------------------Basic Constructor--------------------------------------------------
// Description: Basic constructor for the GraphL class.
// ---------------------------------------------------------------------------------------------------

GraphL::GraphL(){

    for (int i = 1; i < MAXNODES; i++){           //This loop initializes the adjacency list array to NULL values for the pointers.
        graphNodes[i].visited = false;              //We also mark each node as false for visited.
        graphNodes[i].edgeHead = nullptr;
        graphNodes[i].data = nullptr;
    }
    size = 0;                                       //The size of our graph is 0 when we construct it.
}

// ---------------------------------~GraphL()--------------------------------------------------
// Description: Destructor for the GraphL class. This is needed as we are using dynamic memory to represent this graph.
// ---------------------------------------------------------------------------------------------------
GraphL::~GraphL(){
    cleanGraph();       //Call helper function to deallocate memory we used in this class.
}

// ---------------------------------buildGraph--------------------------------------------------
// Description: Builds the graph from a given input text file.
// ---------------------------------------------------------------------------------------------------
void GraphL::buildGraph(ifstream& infile){

      // read from data file
    infile >> size;            // sets the size
    string nodeName = "";       // name of each node
    getline(infile, nodeName); // read line

    for (int i = 1; i <= size; ++i) // insert edge names
    {
        getline(infile, nodeName);
        NodeData* tmp = new NodeData(nodeName);
        graphNodes[i].data = tmp;   // insert into array
    }

    int from, to;

    while (infile >> from >> to)   // fill linked list
    {
        if (from == 0)
        {
            break;
        }

        if (graphNodes[from].edgeHead == NULL)  // first node at array index
        {
            EdgeNode* node = new EdgeNode;
            node->adjGraphNode = to;            // insert adjacent
            graphNodes[from].edgeHead = node;   // point to head
            graphNodes[from].edgeHead->nextEdge  = NULL;
        }
        else    // additional nodes in linked list
        {
            EdgeNode* node = new EdgeNode;
            node->adjGraphNode = to;            // insert adjacent
            node->nextEdge = graphNodes[from].edgeHead;  // move pointer
            graphNodes[from].edgeHead = node;  // assign as head
        }
    }
    cout << "" << endl;         //Formatting
}

// ---------------------------------depthFirstSearch()--------------------------------------------------
// Description: For a given graphL object, performs a depth first search of the nodes in the graph.
// ---------------------------------------------------------------------------------------------------
void GraphL::depthFirstSearch(){
    cout << "Depth-first ordering:";    

    for (int v = 1; v <= size; ++v) // loop through size
    {
        if (graphNodes[v].visited == false)   // check if node has been visited
        {
            dfsHelper(v);  // call helper
        }
    }

    cout << endl;
}

// ---------------------------------dfsHelper--------------------------------------------------
// Description: This is a recursive function that helps perform a depth first search of the grpah.
// ---------------------------------------------------------------------------------------------------
void GraphL::dfsHelper(int node){
    cout << setw(2) << node;   // print node
    graphNodes[node].visited = true;   // mark visited
    EdgeNode* current = graphNodes[node].edgeHead; // move pointer to head

    while (current != NULL) // loop till end of linked list
    {
        if (!graphNodes[current->adjGraphNode].visited) // check if visited
        {
            dfsHelper(current->adjGraphNode);  // call helper
        }

        current = current->nextEdge;    // move pointer to next node in linked list
    }
}


// ---------------------------------displayGraph--------------------------------------------------
// Description: Fucntion to display the current GraphL object graph. Also display the 
//              nodes and connections that each graph has.
// ---------------------------------------------------------------------------------------------------
void GraphL::displayGraph(){

    cout << "Graph:" << endl;

    for (int i = 1; i <= size; ++i) // print array info
    {
        // print index and name of the node
        cout << "Node" << i << "      " << *graphNodes[i].data << endl << endl;

        EdgeNode* current = graphNodes[i].edgeHead; // assign to current

        while (current != NULL) // check for linked list
        {
            // print linked list
            cout << setw(7) << "edge " << i << setw(2) << current->adjGraphNode << endl;
            current = current->nextEdge;  // move pointer to next node in linked list
        }
    }
}

// ---------------------------------cleanGraph--------------------------------------------------
// Description: This is a helper function for cleaning up the pointers used with the GraphL class.
//              Additionally, this function de-allocates memory used in the GraphL class.
// ---------------------------------------------------------------------------------------------------
void GraphL::cleanGraph(){
    for (int x = 1; x <= size; ++x)
    {
        graphNodes[x].visited = false;
        delete graphNodes[x].data;  // delete edge name
        graphNodes[x].data = NULL;  // set edge name to NULL

        if (graphNodes[x].edgeHead != NULL) // check for linked list in array index
        {
            EdgeNode* del = graphNodes[x].edgeHead;

            while (del != NULL) // traverse linked list
            {
                graphNodes[x].edgeHead = graphNodes[x].edgeHead->nextEdge;
                delete del; // delete node
                del = NULL; // set node to NULL
                del = graphNodes[x].edgeHead;   // move head
            }
        }
    }
}