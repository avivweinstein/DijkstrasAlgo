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

    infile >> size; 						//Storing the size of the we are creating in the private "size" variable
    string nodeName = "";
    getline(infile, nodeName); 

    for (int i = 1; i <= size; i++){ 					//Here I am creating the data (graph.data) array.
    
        getline(infile, nodeName);						//Grabbing full line to use as the name of the node
        NodeData* newNode = new NodeData(nodeName);     //Creating a new NodeData to store the name of the node
        graphNodes[i].data = newNode;
    }

    int source, destination;

    while (infile >> source >> destination){
        if (source == 0){
            break;
        }

        if (graphNodes[source].edgeHead == nullptr){ //If there is no node in our array of nodes representing the graph.
            EdgeNode* graphNode = new EdgeNode;  			  //create a new node
            graphNode->adjGraphNode = destination;            //set the adjacentgraphnode location to the destination we have read in from the infile
            graphNodes[source].edgeHead = graphNode;   		  //Update our array representing the graph
            graphNodes[source].edgeHead->nextEdge  = nullptr;
        }
        else{
            EdgeNode* graphNode = new EdgeNode;
            graphNode->adjGraphNode = destination;            
            graphNode->nextEdge = graphNodes[source].edgeHead; 
            graphNodes[source].edgeHead = graphNode;  
        }
    }
	
    cout << "" << endl;         					//Formatting
}

// ---------------------------------depthFirstSearch()--------------------------------------------------
// Description: For a given graphL object, performs a depth first search of the nodes in the graph.
// ---------------------------------------------------------------------------------------------------
void GraphL::depthFirstSearch(){
    cout << "Depth-first ordering:";    

    for (int i = 1; i <= size; i++){
        if (graphNodes[i].visited == false){
            dfsHelper(i);  //Call the depth first search helper funciton
        }
    }
    cout << endl;
}

// ---------------------------------dfsHelper--------------------------------------------------
// Description: This is a recursive function that helps perform a depth first search of the grpah.
// ---------------------------------------------------------------------------------------------------
void GraphL::dfsHelper(int node){
    cout << "  " << node; 
    graphNodes[node].visited = true;						//We mark each node we visit as true.
    EdgeNode* currentNode = graphNodes[node].edgeHead; 		//Creating a pointer to traverse our grpah.

    for(;;){
        if(currentNode == nullptr){
            break;
        }
        
        if (graphNodes[currentNode->adjGraphNode].visited == false){		//we only visit unvisited nodes.
            dfsHelper(currentNode->adjGraphNode);				//recursive call again if we can keep going
        }

        currentNode = currentNode->nextEdge;			//Move to the next node.
    }
}


// ---------------------------------displayGraph--------------------------------------------------
// Description: Fucntion to display the current GraphL object graph. Also display the 
//              nodes and connections that each graph has.
// ---------------------------------------------------------------------------------------------------
void GraphL::displayGraph(){
    cout << "Graph:" << endl;

    for (int i = 1; i <= size; i++){
        // print index and name of the node
        cout << "Node" << i << "\t\t" << *graphNodes[i].data /*<< endl*/ << endl;

        EdgeNode* currentNode = graphNodes[i].edgeHead; // assign to current

        for(;;){
            if(currentNode == nullptr){
                break;
            }
            
            cout << "\t edge " << i << "  " << currentNode->adjGraphNode << endl;
            currentNode = currentNode->nextEdge;
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

        //This if statement checks for one of the linked lists we have created
        if (graphNodes[i].edgeHead != nullptr){
			
            //We create a pointer to traverse our linked list.
            EdgeNode* nodeToDelete = graphNodes[i].edgeHead; 
			
            while (nodeToDelete != nullptr){    //While we still have a list, we loop.
				
                 //increment our linked list to point to the next item
                graphNodes[i].edgeHead = graphNodes[i].edgeHead->nextEdge; 
                delete nodeToDelete;            //Delete the node we are currently at.
                nodeToDelete = nullptr;         //set our node to nullptr
                //Not sure if I need this. Will not having this introduce a memory leak?
                //nodeToDelete = graphNodes[i].edgeHead;
            }
        }
    }
}