//
//  Graph.hpp
//  Software
//
//  Created by Rei Halle on 09/11/2016.
//  Copyright © 2016 Rei Halle. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>

// C++ program to find single source shortest paths for Directed Acyclic Graphs
#include<iostream>
#include <list>
#include <stack>
#include <limits.h>
#define INF INT_MAX
using namespace std;


// Graph is represented using adjacency list. Every node of adjacency list
// contains vertex number of the vertex to which edge connects. It also
// contains weight of the edge
class AdjListNode
{
    const int WHITE=1, NIL = -1;
    int v;
    int _color = WHITE;
    double weight;
    int _pred = NIL;
public:
    AdjListNode(int _v, double _w)  { v = _v;  weight = _w;}
    void setColor(int color) { _color = color; }
    void setPred(int pred) { _pred = pred; }
    int getV()       {  return v;  }
    double getWeight()  {  return weight; }
};

// Class to represent a graph using adjacency list representation
class Graph
{
    int V;    // No. of vertices'
    
    int E; // No. of edges'
    
    // Pointer to an array containing adjacency lists
    list<AdjListNode> *adj;
    
    // A function used by shortestPath
    void topologicalSortUtil(int v, bool visited[], stack<int> &Stack);
public:
    Graph(int V);   // Constructor
    
    // function to add an edge to graph
    void addEdge(int u, int v, double weight);
    
    // Finds shortest paths from given source vertex
    void shortestPath(int s);
    
    //read file with nodes
    void readGraph(const char *In);
    
    //run BFS algorithem
    void BFS(int source);
};

#endif /* Graph_hpp */
