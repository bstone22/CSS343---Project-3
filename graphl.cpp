// ------------------------------------------------ graphl.cpp -------------------------------------------------------- 
// Brent Stone CSS 343 Section C
// February 7th, 2016
// February 14th, 2016
// --------------------------------------------------------------------------------------------------------------------
// Purpose - The graphl.cpp files provides functions for depth first search.  The functions are
//			depthFirstSeach(), empty(), buildGraph(), displayGraph(), dfs helper, insert and check an edge.
//			This program prints out the complete adjaccenly list and the depth first search for the given graphl object
// -------------------------------------------------------------------------------------------------------------------- 
// Assumptions - Maxnodes are assumed to max 100 modes and all data entry is correct. 
// --------------------------------------------------------------------------------------------------------------------

#include "nodedata.h"
#include "graphl.h"
#include <iomanip>

//------------------------- GraphL() ----------------------------
// Default constructor: Creates a graphl object  
// Preconditions: None
// Postconditions: graphl object created.
// ---------------------------------------------------------------
GraphL::GraphL()
{
	for (int i = 1; i < L_MAXNODES; i++) //sets contents to empty
	{
		adjList[i].edgeHead = NULL;
		adjList[i].visited = false;
		adjList[i].data = NULL;
	}
	size = 0;
}

//------------------------- ~GraphL() ----------------------------
// Default constructor: Destroys a graphl object  
// Preconditions: None
// Postconditions: graphl object destroy
// ---------------------------------------------------------------
GraphL::~GraphL()
{
	empty();
}

//------------------------- empty() ----------------------------
// Empty(): clears object
// Preconditions: None
// Postconditions: graphl object is deleted
// ---------------------------------------------------------------
void GraphL::empty()///possible memory leak
{

	for (int i = 1; i <= size; i++)
	{
		EdgeNode * temp = adjList[i].edgeHead; //pointer to edge head
		while (temp != NULL)
		{
			adjList[i].edgeHead = adjList[i].edgeHead->nextEdge; //sets edgehead to next node
			delete temp;					//deletes temp
			temp = NULL;					
			temp = adjList[i].edgeHead;			//sets temp pointer to new edgehead
		}

		adjList[i].visited = false;		//marks unvisited
		delete adjList[i].data;			//deletes data
		adjList[i].data = NULL;			
	}
	size = 0;
}

//------------------------- buildGraph(ifstream& in)--------------
// Build Graph: Builds Graph object
// Preconditions: valid file input
// Postconditions: graphl object is deleted
// ---------------------------------------------------------------
void GraphL::buildGraph(ifstream& in)
{
	int from = 0;
	int to = 0;
	empty();

	in >> size;

	if (in.eof())//empty file
	{
		return;
	}

	string name = "empty";
	getline(in, name); 

	for (int i = 1; i <= size; i++)
	{
		getline(in, name);
		NodeData *temp = new NodeData(name); //creates new Node data 
		adjList[i].data = temp;				//stors in array
	}

	while (in >> from >> to)
	{
		if (from == 0)
		{
			break;
		}
		insertEdge(from, to);
	}
}

//------------------insertEdge(int, int)-------------------------
// insertEdge: inserts an edge into the adj list
// Preconditions: 
// Postconditions: graphl object
// ---------------------------------------------------------------
bool GraphL::insertEdge(int from, int to)
{
	if (checkEdge(from, to))		//input validation
	{
		if (adjList[from].edgeHead == NULL)		//if adj list index empty
		{
			adjList[from].edgeHead = new EdgeNode;		// new edge head
			adjList[from].edgeHead->adjGraphNode = to;	//input data
			adjList[from].edgeHead->nextEdge = NULL;	//
			return true;
		}
		else
		{											//if adj list index not empty
			EdgeNode* insert = new EdgeNode();		//new edge node
			insert->adjGraphNode = to;				//insert data
			insert->nextEdge = adjList[from].edgeHead;//set next edge
			adjList[from].edgeHead = insert;		//copy
			return true;		
		}
	}
	else
	{
		return false;
	}
}

//------------------- checkEdge(int,int) ----------------------------
// CheckEdge(): Check if inserted edge is valid
// Preconditions: graphl object
// Postconditions: returns true if valid, false if not valid
// ------------------------------------------------------------------
bool GraphL::checkEdge(int from, int to)
{
	if (from > size || to > size || from < 1 || to < 1)//if either to and from are greater than size or less than 1
	{
		return false;
	}
	else
	{
		return true;
	}

}
//------------------- depthFirstSearch()----------------------------
// depthFirstSearch(): performs a depth first searhc
// Preconditions: graphl object
// Postconditions: prints out dfs 
// ------------------------------------------------------------------
void GraphL::depthFirstSearch()
{
	cout << "Depth-first ordering: ";		//print line

	for (int v = 1; v <= size; v++)			
	{
		if (adjList[v].visited == false)	//if not visited call fucntion
		{
			dfs(v);							//dfs helper
		}
	}

	cout << endl << endl;
}

//------------------- dfs(int)--------------------------------------
// dfs(): performs a depth first search, helper
// Preconditions: graphl object
// Postconditions: prints out dfs
// ------------------------------------------------------------------
void GraphL::dfs(int v)
{
	if(adjList[v].visited == true)//base case
	{
		return;
	}
	else
	{
		adjList[v].visited = true;				//mark visited
		cout << " " << v;						//print
		EdgeNode * current = adjList[v].edgeHead;	//create pointer to edgehead
		while (current != NULL)						//while not at the end
		{
			if (adjList[current->adjGraphNode].visited == false)	//if not visited 
			{
				dfs(current->adjGraphNode);							//do depth first seach
			}

		current = current->nextEdge;							//else move pointer
		}
	}
}

//------------------- displayGraph()---------------------------------
// displayGraph(): dispalys adj list
// Preconditions: graphl object
// Postconditions: prints out dfs
// ------------------------------------------------------------------
void GraphL::displayGraph()
{
	cout << "Graph:" << endl;			//headline

	for (int i = 1; i <= size; i++)
	{
		cout << "Node " << i << "\t\t" << *(adjList[i].data) << endl << endl;	
		EdgeNode* current = adjList[i].edgeHead;				//pointer to edge head
		while (current != NULL)									//while pointer not null
		{
			cout << setw(7) << "edge " << setw(3) << i << " " << current->adjGraphNode << endl; //print out
			current = current->nextEdge;					//move pointer
		}

	}
	cout << endl;
}


