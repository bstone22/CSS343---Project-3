// ------------------------------------------------ graphm.j -------------------------------------------------------- 
// Brent Stone CSS 343 Section C
// February 7th, 2016
// February 14th, 2016
// --------------------------------------------------------------------------------------------------------------------
// Purpose - The graphm.h files function definition for to find Dijkstra's shortest path.  The functions are
//			depthFirstSeach(), empty(), buildGraph(), displayGraph(), dfs helper, insert and check an edge.
//			The program uses dijkstra's to find the shortest path of a given graph object
// -------------------------------------------------------------------------------------------------------------------- 
// Assumptions - Maxnodes are assumed to max 100 modes and all data entry is correct. 
// --------------------------------------------------------------------------------------------------------------------
#ifndef GRAPHM_H
#define GRAPHM_H
#include "nodedata.h"
#include <fstream>
#include <iostream>
using namespace std;

const int M_MAXNODES = 101;

class GraphM
{
public:
	GraphM();			//constructor
	~GraphM();			//destructor

	void buildGraph(ifstream& in);				//build graph
	void findShortestPath();					//finds shortest path
	bool insertEdge(int from, int to, int weight);//insert
	bool removeEdge(int from, int to);			//remove
	void displayAll();							//display all table
	void display(int from, int to);				//display for 


private:
	struct TableType {
		bool visited;
		int dist;
		int path;
	};

	NodeData data[M_MAXNODES];
	int C[M_MAXNODES][M_MAXNODES];
	int size;
	TableType T[M_MAXNODES][M_MAXNODES];
	void empty();					//clears table	
	int vSearch(int source);		//finds v
	void printPath(int from, int to);//prints path
	void printName(int from, int to);//prints name
	bool checkEdge(int from, int to);//edge validation
	bool checkEdge(int from, int to, int weight);//edge validation
	void clearT();   //clears T table 
};

#endif

