// ------------------------------------------------graphm.cpp-------------------------------------------------------
// Programmer Name: Aviv Weinstein
// Course Section Number: CSS 502 A
// Creation Date: 
// Date of Last Modification:
// Instructor Name: Professor Dong Si
// --------------------------------------------------------------------------------------------------------------------
// Purpose - 
// --------------------------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions: 
//      INDEX 0 is not used!
// --------------------------------------------------------------------------------------------------------------------
//Making useless chnages for github! More fucking changes.
#include "graphl.h"
#define MAXNODES_L 101
#define inf 10000

// ---------------------------------Basic Constructor--------------------------------------------------
// Description: Basic constructor for the GraphL class.
// ---------------------------------------------------------------------------------------------------

GraphL::GraphL(){

    for (int i = 1; i < MAXNODES_L; i++){           //This loop initializes the adjacency list array to NULL values for the pointers.
        graphNodes[i].visited = false;              //We also mark each node as false for visited.
        graphNodes[i].edgeHead = nullptr;
        graphNodes[i].data = nullptr;
    }

    size = 0;                                       //The size of our graph is 0 when we construct it.
}

GraphL::~GraphL(){
    
    cleanGraph();
}


void GraphL::buildGraph(ifstream& infile){

    int graphSize = 0;
    string graphData = "";

    infile >> graphSize;
    size = graphSize;

    //Because index 0 is not being used, I am started at i = 1 and going until i == graphSize
    for(int i = 0; i <= graphSize; i++){ //Here I am creating the data (graph.data) array.
        getline(infile, graphData);
        NodeData* nodeData = new NodeData(graphData);
        graphNodes[i].data = nodeData;
        //delete nodeData;
        nodeData = nullptr;
        delete nodeData;
    }

    cout << "" << endl;

    int source = 0;
    int destination = 0;

    for( ;  ;){
        infile >> source >> destination;

        if((source && destination) == 0){
            break;
        }

        if(infile.eof()){
            break;
        }

        if(graphNodes[source].edgeHead == nullptr){
            EdgeNode* node = new EdgeNode;
            node->adjGraphNode = destination;
            graphNodes[source].edgeHead = node;
            graphNodes[source].edgeHead->nextEdge = nullptr;
            
        }
        else{
            EdgeNode* node = new EdgeNode;
            node->adjGraphNode = destination;
            node->nextEdge = graphNodes[source].edgeHead;
            graphNodes[source].edgeHead = node;
        }
    }
    cout << "" << endl;
}

void GraphL::depthFirstSearch(){
    cout << "Depth-first ordering:";

    for (int i = 1; i <= size; i++){
        if (graphNodes[i].visited == false){
            dfsHelper(i);
        }
    }
}

void GraphL::dfsHelper(int node){
    cout << "  " << node; 
    graphNodes[node].visited = true;
    EdgeNode* currentNode = graphNodes[node].edgeHead;

    while (currentNode != nullptr){
        if (!graphNodes[currentNode->adjGraphNode].visited){
            dfsHelper(currentNode->adjGraphNode);
        }
        currentNode = currentNode->nextEdge;
    }
}

void GraphL::displayGraph(){
    cout << "Graph: " << endl;

    for (int i = 1; i <= size; i++){
        cout << "Node" << i << "\t\t" << *graphNodes[i].data << endl;

        EdgeNode* currentNode = graphNodes[i].edgeHead;

        for( ; ;){
            //cout << "did we enter?" << endl;

            if (currentNode == nullptr){
                break;
            }
            else{
                cout << "\t edge " << i << "  " << currentNode->adjGraphNode << endl;
                currentNode = currentNode->nextEdge;  
            }          
        }
        cout << "" << endl; //For space between each Node we print
    }
}

void GraphL::cleanGraph(){

    for (int i = 1; i <= size; i++){
        graphNodes[i].visited = false;
        delete graphNodes[i].data;  // delete edge name
        graphNodes[i].data = nullptr;  // set edge name to NULL

        if (graphNodes[i].edgeHead != nullptr){
            EdgeNode* del = graphNodes[i].edgeHead;

            while (del != NULL){
                graphNodes[i].edgeHead = graphNodes[i].edgeHead->nextEdge;
                delete del; // delete node
                del = nullptr; // set node to NULL
                del = graphNodes[i].edgeHead;   // move head
            }
        }
    }

}