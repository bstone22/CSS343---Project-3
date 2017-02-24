// ------------------------------------------------ graphl.h -------------------------------------------------------- 
// Brent Stone CSS 343 Section C
// February 7th, 2016
// February 14th, 2016
// --------------------------------------------------------------------------------------------------------------------
// Purpose - The graphl.h files provides function definition for depth first search.  The functions are
//			depthFirstSeach(), empty(), buildGraph(), displayGraph(), dfs helper, insert and check an edge.
//			This program prints out the complete adjaccenly list and the depth first search for the given graphl object
// -------------------------------------------------------------------------------------------------------------------- 
// Assumptions - Maxnodes are assumed to max 100 modes and all data entry is correct. 
// --------------------------------------------------------------------------------------------------------------------
#ifndef GRAPHM_L
#define GRAPHM_L

#include "nodedata.h"
#include <fstream>
#include <iostream>
using namespace std;
const int L_MAXNODES = 101;

class GraphL
{
public:
	GraphL();					//constructor
	~GraphL();					//destructor

	void buildGraph(ifstream& in);//build graph
	void depthFirstSearch();	//dfs seach
	void displayGraph();		//display


private:
	struct EdgeNode;			//given struct
	struct GraphNode			//given strcut
	{
		EdgeNode *edgeHead;
		NodeData* data;
		bool visited;
	};

	struct EdgeNode				//given struct
	{
		int adjGraphNode;
		EdgeNode* nextEdge;
	};

	GraphNode adjList[L_MAXNODES];	//adj list array
	int size;				

	bool insertEdge(int from, int to);	//insert edge
	bool checkEdge(int from, int to);	//edge validation
	void dfs(int v);					//dfs helper
	void empty();						//clears object
};

#endif
