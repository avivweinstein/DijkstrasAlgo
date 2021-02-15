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

// ---------------------------------~GraphL()--------------------------------------------------
// Description: Destructor for the GraphL class. This is needed as we are using dynamic memory to represent this graph.
// ---------------------------------------------------------------------------------------------------
GraphL::~GraphL(){
    
    cleanGraph();
}

// ---------------------------------buildGraph--------------------------------------------------
// Description: Builds the graph from a given input text file.
// ---------------------------------------------------------------------------------------------------
void GraphL::buildGraph(ifstream& infile){

    string graphData = ""; //
    infile >> size;                                     //Storing the size of the we are creating.

    //Because index 0 is not being used, I am started at i = 1 and going until i == graphSize.
    //Not sure why I cannot start at 1. When I do, I enter an infinite loop.
    for(int i = 0; i <= size; i++){                        //Here I am creating the data (graph.data) array.
        getline(infile, graphData);                       //Grabbing full line to use as the name of the node
        NodeData* nodeData = new NodeData(graphData);      //Creating a new NodeData to store the name of the node
        graphNodes[i].data = nodeData; 
    }

    cout << "" << endl;         //Formatting

    //these two variables will be for storing the edges in my grpah.
    int source = 0;
    int destination = 0;

    for( ;  ;){
        infile >> source >> destination;

        if((source && destination) == 0){       //break condition for my graph. When we get to these values in the input file, we break.
            break;
        }

        if(infile.eof()){                       //Or if we somehow reach the end of file.
            break;
        }

        if(graphNodes[source].edgeHead == nullptr){         //If there is no node in our array of nodes representing the graph.
            EdgeNode* node = new EdgeNode;                  //create a new node
            node->adjGraphNode = destination;               //set the adjacentgraphnode location to the destination we have read in from the infile
            graphNodes[source].edgeHead = node;             //Update our array representing the graph
            graphNodes[source].edgeHead->nextEdge = nullptr;        //
            
        }
        else{
            EdgeNode* node = new EdgeNode;
            node->adjGraphNode = destination;
            node->nextEdge = graphNodes[source].edgeHead;
            graphNodes[source].edgeHead = node;
        }
    }
    cout << "" << endl;         //Formatting
}

// ---------------------------------depthFirstSearch()--------------------------------------------------
// Description: For a given graphL object, performs a depth first search of the nodes in the graph.
// ---------------------------------------------------------------------------------------------------
void GraphL::depthFirstSearch(){
    cout << "Depth-first ordering:";

    for (int i = 1; i <= size; i++){                //Looping through all graph nodes. We call the DFS helper function on the nodes we have yet to visit.
        if (graphNodes[i].visited == false){
            dfsHelper(i);                           //Call the depth first search helper funciton
        }
    }
}

// ---------------------------------dfsHelper--------------------------------------------------
// Description: This is a recursive function that helps perform a depth first search of the grpah.
// ---------------------------------------------------------------------------------------------------
void GraphL::dfsHelper(int node){
    cout << "  " << node; 
    graphNodes[node].visited = true;                                        //We mark each node we visit as true.
    EdgeNode* currentNode = graphNodes[node].edgeHead;                      //Creating a pointer to traverse our grpah.

    while (currentNode != nullptr){                                         //While we still have locations to travel to in our graph, keep going.
        if (graphNodes[currentNode->adjGraphNode].visited == false){        //we only visit unvisited nodes.
            dfsHelper(currentNode->adjGraphNode);                           //recursive call again
        }
        currentNode = currentNode->nextEdge;                                //Move to the next node.
    }
}


// ---------------------------------displayGraph--------------------------------------------------
// Description: Fucntion to display the current GraphL object graph. Also display the 
//              nodes and connections that each graph has.
// ---------------------------------------------------------------------------------------------------
void GraphL::displayGraph(){
    cout << "Graph: " << endl;

    for (int i = 1; i <= size; i++){
        cout << "Node" << i << "\t\t" << *graphNodes[i].data << endl;

        EdgeNode* currentNode = graphNodes[i].edgeHead;

        for( ; ;){
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

// ---------------------------------cleanGraph--------------------------------------------------
// Description: This is a helper function for cleaning up the pointers used with the GraphL class.
//              Additionally, this function de-allocates memory used in the GraphL class.
// ---------------------------------------------------------------------------------------------------
void GraphL::cleanGraph(){
    for (int i = 1; i <= size; i++){
        //This block of code loops through all the nodes we have allocated in the current
        //graph and cleans up the pointers/memory we have allocated.
        graphNodes[i].visited = false;
        delete graphNodes[i].data;
        graphNodes[i].data = nullptr; 

        if (graphNodes[i].edgeHead != nullptr){                 //This if statement checks for one of the linked lists we have created
            EdgeNode* nodeToDelete = graphNodes[i].edgeHead;    //We create a pointer to traverse our linked list.

            while (nodeToDelete != nullptr){                    //While we still have a list, we loop.
                graphNodes[i].edgeHead = graphNodes[i].edgeHead->nextEdge;  //increment our linked list to point to the next item
                delete nodeToDelete;                                        //Delete the node we are currently at.
                nodeToDelete = nullptr;                                     //set our node to nullptr
                //nodeToDelete = graphNodes[i].edgeHead;                    //NOT SURE IF i NEED THIS
            }
        }
    }

}