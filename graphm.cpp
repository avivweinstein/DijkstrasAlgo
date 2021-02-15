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
#include "graphm.h"
#define MAXNODES 101
#define inf 10000

// ---------------------------------Basic Constructor--------------------------------------------------
// Description: Basic constructor for the GraphM class. Sets all the private data members to initial values for an empty graph
//              with predefinied inital values.
// ---------------------------------------------------------------------------------------------------
GraphM::GraphM(){
    size = 0;               //Size is 0 in a newly initialized GraphM

    TableType initial; //This variable is going to serve as the initial values for all the TableType varibles in T.
    initial.dist = inf;
    initial.path = 0;
    initial.visited = false;

    NodeData initialData("N/A"); //Initially, I will fill the graph with N/A values.

    for(int i = 0; i < MAXNODES; i++){ //Looping through all values in the array for data.

        data[i] = initialData;
    }

    for(int j = 0; j < MAXNODES; j++){ //I need to have these nested for loops to set the values of C and T to their "initial" values
        for(int q = 0; q < MAXNODES; q++){
            C[j][q] = inf;
            T[j][q] = initial;
        }
    }
}


// ---------------------------------buildGraph--------------------------------------------------
// Description: Builds the graph from a given input text file. Returns true if successful and false if something goes wrong.
// ---------------------------------------------------------------------------------------------------
bool GraphM::buildGraph(ifstream& infile){
    int graphSize = 0;
    string graphData;

    infile >> graphSize;
    this->size = graphSize;

    //Because index 0 is not being used, I am started at i = 1 and going until i == graphSize
    for(int i = 0; i <= graphSize; i++){ //Here I am creating the data (graph.data) array.
    //NEED TO CHECK WITH STACK OVERFLOW. BUT WHY DO I NEED TO START AT 0?
        //NodeData *ptr = new NodeData;
        //if(ptr->setData(infile)){
            //this->data[i] = *ptr;
        //}
        this->data[i].setData(infile);

        /*else{
            cout << "Couldn't set NodeData" << endl;
            return false;*/
    }

    cout << "" << endl;

    int source = 0;
    int destination = 0;
    int weight = 0;

    for( ;  ;){
        infile >> source >> destination >> weight;

        if((source && destination && weight) == 0){
            break;
        }

        if(infile.eof()){
            break;
        }

        C[source][destination] = weight; //This is where we build the adjacnecy matrix.
        //Remember, that all the locations in the adjacency matrix were initialized to our value of infinity
        //Infinity is 10000 in this code.
        
    }
    cout << "" << endl;

    //printAdjMatrix();
    return false;
}

bool GraphM::insertEdge(int fromNode, int toNode, int weight){

    if((fromNode || toNode) > size){ //Checking to make sure we cannot add an edge for nodes that do not exist.
        cout << "One of your nodes not exist. Therefore, an edge cannot be added." << endl;
        return false;
    }

    else if((fromNode || toNode) <= 0){ //Again, checking to make sure you cannot add an edge for nodes that do not exist.
        cout << "One of the edges you are trying to insert is between invalid nodes." << endl;
        return false;
    }
    else if(weight <0){ //If the weight of an edge is less than 0, it cannot be used with Dijkstra's, as a pre-condition is all weights are positive.
        cout << "The weight of an edge cannot be less than 0" << endl;
        return false;
    }

    C[fromNode][toNode] = weight;
    return true;
}

bool GraphM::removeEdge(int fromNode, int toNode){

    if((fromNode || toNode) > size){ //Checking to make sure we cannot add an edge for nodes that do not exist.
        cout << "That node does not exist. Therefore, an edge cannot be added." << endl;
        return false;
    }
    else if((fromNode || toNode) < 0){
        cout << "One of the edges you are trying to delete is less than 0 and therefore invalid." << endl;
        return false;
    }

    C[fromNode][toNode] = inf;
    return true;
}

// ---------------------------------display--------------------------------------------------
// Description:  uses couts to display the shortest distance with path info between the fromNode to toNode.
// ---------------------------------------------------------------------------------------------------
void GraphM::display(int fromNode, int toNode){

    if ((fromNode > size || toNode > size)||(fromNode<0 ||toNode < 0)){
        cout << "\t" << fromNode << "\t" << toNode << "\t     " << "----" << endl;
        //cout << "Either your start node or your destination node do not exist." << endl;
        return;  
    }

    if(C[fromNode][toNode] == inf){
        cout << "\t" << fromNode << "\t" << toNode << "\t     " << "----" << endl;
        return;
    }

    cout << "\t" << fromNode << "\t" << toNode << "\t     " << " " << T[fromNode][toNode].dist << "   \t";
    getPath(fromNode,toNode);
    cout << endl;
    getWeight(fromNode,toNode);
    cout << "" << endl;
    return;
}

// ---------------------------------findShortestPath--------------------------------------------------
// Description: Finds the shortest path between every node to every other node in the graph
//              i.e., TableType T is updated with shortest path information.
// ---------------------------------------------------------------------------------------------------
void GraphM::findShortestPath(){

    for(int source = 1; source <= size; source++){
        T[source][source].dist = 0;
       //T[source][source].visited = true; NOT SURE IF I NEED THIS OR NOT

        for(int i = 1; i <= size; i++){
            if(C[source][i] != inf){
                T[source][i].dist = C[source][i];
                T[source][i].path = source;
            }
        }
        int v = 0;      //This variable will be used to find the not visited, shortest distance away node from the current node.

        for( ; ;){

            v = 0;                                  //Here we reset v for each pass through the for loop.
            int minDist = inf;                      //Setting this variable to store the minimum distance between the current node and the closest node.
            for(int j = 1; j <= size; j++){             //This for loop will iterate through all nodes and find the node that is the shortest distance away.
                if((T[source][j].visited) == false){ //Our condisiton for updating v and minDist is if the node has not been visited
                    if(C[source][j] < minDist){     //We also need to check that the distance away from the unvisited node is shorter than what we currently have found.
                        minDist = C[source][j];     //Update with newest minimum distance
                        v = j;                      //Set v equal to the node we have found as closest AND unvisited.
                    }
                }
            }

            if(v == 0){ //This is our base case for the for loop. If we never set v, that means that there are no nodes adjacent to the current node.
                break;
            }
            //cout << "v: " << v << endl;

            T[source][v].visited = true; //Mark v as visited.

            for(int w = 1; w <= size; w++){ //This loop is looking for each w that is adjacent to v.

                if((T[source][w].visited == true) || (C[v][w] == inf) /*|| (v == w)*/){ //This is a complicated if statement.
                //The first thing we are checking is if the w node has been visited. If it has been visited, we continue.
                //OR, we are also checking to see if w is adjacent or not when we compare C[v][w]==inf. If this is true, then w is not adjacent to v.
                //OR, we are checking if we are pointing to ourself. We want to iterate through that. This isnt needed, as if v==w, then C[v][w] should be == to inf.
                //NOT SURE IF I NEED THIS ONE. It would be good to remove.
                    continue;
                }
                if ((T[source][w].dist) > (T[source][v].dist + C[v][w])){ //This if-statement compares the current weight to get to a node vs. the newly found weight
                        T[source][w].dist = T[source][v].dist + C[v][w]; //Update the weight/distance to get to the node.
                        T[source][w].path = v; //Mark the node we visited from the current node.
                 }
            }
        }
    }
}


// ---------------------------------displayAll--------------------------------------------------
// Description: uses cout to demonstrate that the algorithm works properly.
// ---------------------------------------------------------------------------------------------------
void GraphM::displayAll(){

    cout << "Description\t     From Node\t To Node   Dijkstra's\t Path" << endl;
    cout << "--------------------------------------------------------------" << endl;

    for (int source = 1; source <= size; source++){
        cout << data[source] /*<< endl*/ << endl; 

        for (int dest = 1; dest <= size; dest++){
            if (T[source][dest].dist != 0){
                cout << "\t\t\t " << source; 
                cout << "\t    " << dest; 

                if (T[source][dest].dist == inf){
                    cout << "\t      " << "----" << endl;           //
                }

                else{
                    cout << "\t       " << T[source][dest].dist;   //
                    cout << "\t ";
                    getPath(source, dest);                          //
                    cout << "" << endl;
                }
            }
        }
    }
    cout << "" << endl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//###################################### Utility Functions ##############################################
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ---------------------------------printAdjMatrix--------------------------------------------------
// Description: Utility function to print the adjacency matrix.
// ---------------------------------------------------------------------------------------------------
void GraphM::printAdjMatrix(){
    for(int i = 1; i <= this->size; i++){
        for(int j = 1; j <= this->size; j++){
        cout << "Adjacency Matrix[" << i << "][" << j << "]: " << this->C[i][j] << endl;
        }
    }
}

// ---------------------------------getPath--------------------------------------------------
// Description: Utility function to find path using recursion.
// ---------------------------------------------------------------------------------------------------
void GraphM::getPath(int source, int dest)
{
    if (T[source][dest].dist == inf){ 
        return;
    }

    if (source==dest){
        cout << dest << " "; 
        return;
    }

    int currentNode = dest;
    getPath(source, dest = T[source][dest].path);

    cout << currentNode << " ";
}

// ---------------------------------getWeight--------------------------------------------------
// Description: Utility function to help calculate the weight between two nodes.
//              source is the start node and dest is the end node.
//              This is done recursively.
// ---------------------------------------------------------------------------------------------------
void GraphM::getWeight(int source, int dest){

    int dist = dest;

    if (source == dest){                   //base case for our function.
        cout << data[dest] << endl;
        return;
    }

    //If we havent reached out destination node, call the function again but with the next node in our path
    getWeight(source, T[source][dest].path); 
    cout << data[dist] << endl;         //Print out the name of the path
}














