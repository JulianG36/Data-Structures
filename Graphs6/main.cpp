//Name: Julian Gonzales
//School: University of illinois of Chicago 
//Assignment: Project 6
//Description: Performs a BFS, DFS, Adjacent neightbors and Dijkstra Shortest Path on a specified graph file
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <string>
#include <fstream>
#include "minqueue.h"
#include "graph.h"
using namespace std;
vector<char> BFS(graph& g, char startV){
   queue<char> frontierQueue;
   set<char> discoveredSet;
   vector<char> visited;
   frontierQueue.push(startV);
   discoveredSet.insert(startV);
   char currentVertex;
   while(!frontierQueue.empty()){
      currentVertex = frontierQueue.front();
      frontierQueue.pop();
      visited.push_back(currentVertex);
      vector<char> neightbors = g.neighbors(currentVertex);
      for(char v : neightbors){
         if (discoveredSet.find(v) == discoveredSet.end()){
            frontierQueue.push(v);
            discoveredSet.insert(v);
      
         }
      }
   }
   return visited;

}

//
// DFS:
//
// Performs a depth-first search from the given starting vertex.  
// Returns the vertices in the order they were visited; startV will
// be first.
//
vector<char> DFS(graph& g, char startV)
{
  vector<char>  visited;
  stack<char>   frontierStack;
  set<char>     visitedSet;

  frontierStack.push(startV);
   char currentV;
   while(!frontierStack.empty()){
      currentV = frontierStack.top(); 
      frontierStack.pop();
      if (visitedSet.find(currentV) == visitedSet.end()){
         visited.push_back(currentV);
         visitedSet.insert(currentV);
         for(char v : g.neighbors(currentV)){
            frontierStack.push(v);
         }
      }// then v is not an element of the set:
   }
  
  return visited;
}
//Prints the path for dijkstra
void printPath(map<char, int> &keyValues, stack<int> &path, char v){
	cout << v << ": " << keyValues[v] << " ";
	while(!path.empty()){
		char current = path.top();
		path.pop();
		cout << current << " "; 
	}
	cout << v << endl;
}
//deciphers path from predecessor array and places it onto a stack to flip the order to the correct direction
void determinePath(int predecessor[], char from, vector<char> &vertices, map<char, int> &keyValues, int infinity){ 
	for(char v : vertices){
		stack<int> path;
		int currentIndex = predecessor[v-'A'];
		while(true){
			if(currentIndex == infinity){
				break;
			}
			path.push(currentIndex + 'A');
			currentIndex = predecessor[currentIndex];			
		}
		printPath(keyValues, path, v);
	}
}
//
void DijkstraShortestPath(graph &g, char from, int predecessor[], vector<char> &visited, map<char, int> &keyValues, int infinity){
	minqueue<char, int> priorityQueue;
	vector<char> vertices = g.vertices();
	//sets vertices to infinity
	for(char v : vertices){
		priorityQueue.pushinorder(v, infinity);
		keyValues[v] = infinity;
		predecessor[v-'A'] = infinity;
	}
	//sets starting point
	priorityQueue.pushinorder(from, 0);
	keyValues[from] = 0;
	char currentV;
	int currentDistance;
	//keeps going until the queue is empty or hits an infinity
	while (!priorityQueue.empty()){
		currentV = priorityQueue.minfront();
		priorityQueue.minpop();
		currentDistance = keyValues[currentV];
		if(currentDistance == infinity){
			break;
		}
		visited.push_back(currentV);
		vector<char> neighbors = g.neighbors(currentV);
		//checks all neighbors to find shortest path saves shortest path in keyValues
		//also sets a predecessor
		for(char adjV : neighbors){
			int edgeWeight = g.getweight(currentV, adjV);
			int alternativePath = currentDistance + edgeWeight;
			if(alternativePath < keyValues[adjV]){
				priorityQueue.pushinorder(adjV, alternativePath);
				keyValues[adjV] = alternativePath;
				predecessor[adjV-'A'] = currentV-'A';
			}
		}
	}
}

//
// buildGraph:
//
// Inputs the graph vertices and edges from the given file, building
// the graph g.  File format:
//   vertex vertex vertex ... #
//   src dest weight ... #
//
void buildGraph(string filename, graph& g)
{
  ifstream file(filename);
  char     v;

  if (!file.good())
  {
    cout << endl;
    cout << "**Error: unable to open input file '" << filename << "'." << endl;
    cout << endl;
    return;
  }

  //
  // Input vertices as single uppercase letters:  A B C ... #
  //
  file >> v;

  while (v != '#')
  {
    g.addvertex(v);

    file >> v;
  }

  //
  // Now input edges:  Src Dest Weight ... #
  //
  char src, dest;
  int  weight;

  file >> src;

  while (src != '#')
  {
    file >> dest;
    file >> weight;

    g.addedge(src, dest, weight);

    file >> src;
  }
}
//prints the vectors returned by BFS, DFS and neighbors
void printVector(string prefix, vector<char> target){
	cout << prefix;
	for(char v: target){
		cout << v << " ";
	}
	cout << endl;
}
//prints BFS, DFS and Neighbors 
void outputBFSandDFS(graph &g, char startingVertex){
	vector<char> BFsVisited = BFS(g, startingVertex);
	vector<char> DFsVisited = DFS(g, startingVertex);
	vector<char> neighbors = g.neighbors(startingVertex);
	printVector("Neighbors: ", neighbors);
	printVector("BFS: ", BFsVisited);
	printVector("DFS: ", DFsVisited);		
}



int main(){
	graph g;
	string filename;
	char startingVertex;
	int infinity = 2147483647/2;
	cout << "Enter filename containing graph data> ";
	cin >> filename;
	buildGraph(filename, g);
	g.output();
	cout << endl;
	while(startingVertex != '#'){
		cout << "Enter a starting vertex or #> ";
		cin >> startingVertex;
		outputBFSandDFS(g, startingVertex);
		int predecessor[26];
		vector<char> visited;
		map<char, int> keyValues;
		DijkstraShortestPath(g, startingVertex, predecessor, visited, keyValues, infinity);	
		determinePath(predecessor, startingVertex, visited, keyValues, infinity);
	}
}

