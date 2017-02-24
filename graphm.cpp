// ------------------------------------------------ graphm.cpp -------------------------------------------------------- 
// Brent Stone CSS 343 Section C
// February 7th, 2016
// February 14th, 2016
// --------------------------------------------------------------------------------------------------------------------
// Purpose - The graphm.cpp files provides functions for to find Dijkstra's shortest path.  The functions are
//			depthFirstSeach(), empty(), buildGraph(), displayGraph(), dfs helper, insert and check an edge 
// -------------------------------------------------------------------------------------------------------------------- 
// Assumptions - Maxnodes are assumed to max 100 modes and all data entry is correct. 
// --------------------------------------------------------------------------------------------------------------------
#include "graphm.h"
#include "nodedata.cpp"
#include "limits.h"
#include <iomanip>
#include <algorithm> 

//------------------------- GraphM() ----------------------------
// Default constructor: Creates a graphm object  
// Preconditions: None
// Postconditions: graphm object created.
// ---------------------------------------------------------------
GraphM::GraphM()
{
	empty();
}

//------------------------- ~GraphM() ----------------------------
// Default constructor: Clears a graphm object  
// Preconditions: None
// Postconditions: graphm object destroyed
// ---------------------------------------------------------------
GraphM::~GraphM()
{
	empty();
}

//------------------------- empty() ----------------------------
// Empty: Clears a graphm object  
// Preconditions: None
// Postconditions: graphm object destroyed
// --------------------------------------------------------------
void GraphM::empty()
{
	for (int i = 0; i < M_MAXNODES; i++)//clears all 
	{
		for (int j = 0; j < M_MAXNODES; j++)
		{
			C[i][j] = INT_MAX;
			T[i][j].dist = INT_MAX;
			T[i][j].visited = false;
			T[i][j].path = 0;
		}
	}
	size = 0;
}
//------------------- buildGraph(ifstream& in) ------------------
// buildGraph: Creates a graph
// Preconditions: ifstream
// Postconditions: Graph is created
// --------------------------------------------------------------
void GraphM::buildGraph(ifstream& in)
{
	empty();
	int to = 0;
	int from = 0;
	int weight = 0;
	string name = "empty";

	in >> size;
	if (in.eof())//checks for empty
	{
		return;
	}
	getline(in, name);//gets name

	for (int i = 1; i <= size; i++)//inserts into data
	{
		data[i].setData(in);
	}

	while (in >> from >> to >> weight)
	{
		if (from == 0) //breaks	
		{
			break;
		}
		C[from][to] = weight; //sets cost table
	}
}

//------------------- findShortestPath() -----------------------------
// findShortestPath(): Find the shortest path from one node to another
// Preconditions: graphm object
// Postconditions: finds shorest path
// Notes: followed psudo code given in handout
// --------------------------------------------------------------------
void GraphM::findShortestPath()
{
	for (int source = 1; source <= size; source++)//first for loop
	{
		T[source][source].dist = 0;			//set distance to 0
		int v = 0;							//v set to 0, not used

		for (int i = 1; i <= size; i++)		//second for loop
		{
			v = vSearch(source);			//search for smallest vertex(find v)
			T[source][v].visited = true;	//mark smallest vertex visited(mark v visited)
			if (v != 0)
			{
				for (int w = 1; w <= size; w++)//third for loop(for each w adj to v)
				{
					if (T[source][w].visited == false && C[v][w] != INT_MAX)//if W is not visited and cost table exist
					{
						if ((T[source][w].dist > T[source][v].dist + C[v][w]))//if current distance is greater the compared, a shorter path exist
						{
							T[source][w].dist = min(T[source][w].dist, (T[source][v].dist + C[v][w])); //set distace
							T[source][w].path = v;		//record v
						}
					}
				}
			}
		}
	}
}

//------------------- vSearch(int) -----------------------
// V Search(): finds the vertex with the lowest cost
// Preconditions: graphm object
// Postconditions: returns true if found, false of
// ---------------------------------------------------------
int GraphM::vSearch(int source)
{
	int vertex = 0;		//0 not used
	int path = INT_MAX;	//set max

	for (int i = 1; i <= size; i++)
	{
		if (T[source][i].dist < path && T[source][i].visited == false)//finds if the T table is less than path
		{															//and if T is not visited, uses first vertex to pass on to mark as visited
			path = T[source][i].dist;					//finds shortest path
			vertex = i;									//sets vertext has shortest 
		}
	}
	return vertex;
	
}

//------------------- insertEdge(int,int,int) -----------------------
// insertEdge(): insert and edge, clears T table and recalculates 
//				 shortest path
// Preconditions: graphm object
// Postconditions: returns true if found, false if not found
// ------------------------------------------------------------------
bool GraphM::insertEdge(int from, int to, int weight)
{
	if (checkEdge(from, to, weight))//check valid input
	{
		C[from][to] = weight;		//insert edge
		clearT();					//resets t- table
		findShortestPath();			//recalculates shortest path
		return true;
	}
	else
	{
		return false;
	}

}

//------------------- removeEdge(int,int) -----------------------
// removeEdge(): removes and edges, clears T table and recalculates
//				 shortest path
// Preconditions: graphm object
// Postconditions: returns true if found, false if not found
// ------------------------------------------------------------------
bool GraphM::removeEdge(int from, int to)
{
	if (checkEdge(from, to))	//checks valid input
	{
		C[from][to] = INT_MAX; //set to INF
		clearT();				//clears T table
		findShortestPath();		//recalculates
		return true;
	}
	else
	{
		return false;
	}

}

//------------------- ClearT() ------------------------------------
// ClearT(): Clears T table in order to rerun 
// Preconditions: graphm object
// Postconditions: returns true if found, false if not found
// ------------------------------------------------------------------
void GraphM::clearT()
{
	for (int i = 1; i <= size; i++)		//resets T table to update if and Edge is inserted or removed
	{
		for (int j = 1; j <= size; j++)
		{
			T[i][j].dist = INT_MAX;
			T[i][j].path = 0;
			T[i][j].visited = false;
		}
	}
}
//------------------- checkEdge(int,int) ----------------------------
// CheckEdge(): Check if inserted edge is valid
// Preconditions: graphm object
// Postconditions: returns true if valid, false if not valid
// ------------------------------------------------------------------
bool GraphM::checkEdge(int from, int to)
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
//------------------- checkEdge(int,int,int) ----------------------------
// CheckEdge(): Check if inserted edge is valid, check if weight is valid
// Preconditions: graphm object
// Postconditions: returns true if valid, false if not valid
// ------------------------------------------------------------------
bool GraphM::checkEdge(int from, int to, int weight)
{
	if (from > size || to > size || from < 1 || to < 1) //if either to and from are greater than size or less than 1
	{														
		return false;
	}
	else if(weight < 0) //weight less than 0
	{
		return false;
	}
	else if (from == to && weight != 0)//checks going to itself is greater than 0
	{
		return false;
	}
	else
	{
		return true;
	}

}
//------------------- DisplayAll() -----------------------------------
// DisplayAll(): Displays a table of all of shortest paths
// Preconditions: graphm object
// Postconditions: printed table
// -------------------------------------------------------------------
void GraphM::displayAll()
{
	cout << "Description" << setw(17) << "From node" << setw(12) << "To node" << 
	setw(13) << "Dijkstra's" << setw(9) << "Path" << endl; //heading

	for (int i = 1; i <= size; i++)
	{
		cout << data[i] << endl << endl;     // print name

		for (int j = 1; j <= size; j++)
		{
			if (i != j)					//Checks, so it does not print to itself
			{
				cout << setw(25) << i;   //from with formatting
				cout << setw(12) << j;   //to with formatting

				if (T[i][j].dist == INT_MAX)
				{
					cout << setw(12) << "----" << endl; // no adjacent nodes
				}
				else
				{
					cout << setw(10) << T[i][j].dist;   // print distance
					cout << setw(12);

					printPath(i, j); // call helper
					cout << endl;
				}
			}
		}
	}
	cout << endl;
}

//------------------- printPath(int, int) ---------------------------
// printPath(): Prints path of an edge
// Preconditions: graphm object
// Postconditions: printed path from one node to another
// -------------------------------------------------------------------
void GraphM::printPath(int from, int to)
{
	if (T[from][to].dist != INT_MAX)
	{
		int path = to; // assign to path to pathData
		printPath(from, T[from][to].path); //recursively call print path
		cout << path << " ";   // print path
	}
}

//------------------- display(int, int) -----------------------------
// display(): Prints path of an edge, calls printsName() & printPath()
// Preconditions: graphm object
// Postconditions: printed path from one node to another
// -------------------------------------------------------------------
void GraphM::display(int from, int to)		
{
	cout << setw(5) << from << setw(10) << to << setw(10); //formatting
	if (T[from][to].dist == INT_MAX)			
	{
		cout << setw(12) << "----" << endl << endl;	// doesn't not exist
	}
	else
	{
		cout << setw(12) << T[from][to].dist << setw(5);	//prints distance
		printPath(from, to);			//calls printPath
		cout << endl;	
		printName(from, to);			//calls printName
		cout << endl;
	}
}

//------------------- printName(int, int) ----------------------------
// printName(): Prints name recursivley
// Preconditions: graphm object
// Postconditions: printed path from one node to another
// -------------------------------------------------------------------
void GraphM::printName(int from, int to)
{
	if (T[from][to].dist != INT_MAX)
	{
		int path = to; // assign to path to pathData
		printName(from, T[from][to].path); //recurstively calls to print
		cout << data[path] << endl << endl;// print name
	}
}