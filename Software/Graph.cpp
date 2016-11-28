//
//  Graph.cpp
//  Software
//
//  Created by Rei Halle on 09/11/2016.
//  Copyright © 2016 Rei Halle. All rights reserved.
//

#include "Graph.hpp"
# include <iostream>
# include <fstream>
# include <string>
#include <vector>
#include <list>
#include <queue>
#include <ctime>
#define WHITE 1
#define GRAY 2
#define BLACK 3
#define NIL -1
using namespace std;




struct graph {
    std::vector<int> color, dist;
    
    
    graph(size_t nodes)
    : m_adjacency_list(nodes), color(nodes), dist(nodes) {
        size = nodes;
    }
    
    size_t number_of_nodes() const {
        return m_adjacency_list.size();
    }
    
    std::vector<size_t> const& neighbours_of(size_t node) const {
        return m_adjacency_list.at(node);
    }
    
    void add_edge(size_t from, size_t to) {
        std::vector<size_t>& al = m_adjacency_list.at(from);
        if (to >= m_adjacency_list.size())
            throw std::runtime_error("Tried to add edge to non-existant node");
        for (size_t i = 0; i < al.size(); ++i) if (al[i] == to) return;
        al.push_back(to);
    }
    
    int getColor(size_t node) const{
        return color[node];
    }
    
    void setColor(size_t node, int _color){
        color[node] = _color;
    }
    
    size_t getNeighbours(size_t i, size_t j){
        return m_adjacency_list.at(i).at(j);
    }
private:
    size_t size;
    const int infinity = std::numeric_limits<int>::max();
    int *pred, *partition;
    
    std::vector<std::vector<size_t>> m_adjacency_list;
};



class Distance
{
private:
    
    double weight;
    bool infinite;
    
public:
    
    Distance()
    {
        weight = 0;
        infinite = true;
    }
    
    void setWeight(double weight)
    {
        this->weight = weight;
        infinite = false;
    }
    
    string getWeight() const
    {
        if(infinite)
            return "inf";
        
        return to_string(weight);
    }
    
    bool isInfinite()
    {
        return infinite;
    }
    
    bool isZero()
    {
        if(!infinite && weight==0)
            return true;
        
        return false;
    }
    
    // comparing infinite weights
    bool operator > (const Distance & e)
    {
        if (e.infinite)
            return false;
        else if (this->infinite)
            return true;
        else if (this->weight > e.weight)
            return true;
        
        return false;
    }
    
    // adding infinite weights
    Distance operator + (const Distance & e)
    {
        Distance d;
        
        if(this->infinite || e.infinite)
        {
            return d;
        }
        
        d.setWeight(e.weight + this->weight);
        return d;
    }
};



// To store shortest path distances
Distance ** dist ;

// To store the path and corresponding parents
int ** parent ;



// Recursive function to obtain the path as a string
string obtainPath(int i, int j)
{
    if (dist[i][j].isInfinite())
        return " no path to ";
    
    if (parent[i][j] == i)
        return " ";
    else
        return obtainPath(i, parent[i][j]) + to_string(parent[i][j]) + obtainPath(parent[i][j], j);
}



int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cout << "Erorr." << endl;
        exit(-1);
    }
  

    
    if( !strcmp(argv[1], "-h")){
        cout << " -EV = Exclude Vertex" << endl;
        exit(0);
    }


  //  argv[1] = "/Users/reihalle/Downloads/Ex1/G0.txt"; / Test argument
    
    //Start the clock
    clock_t begin = clock();
    
    ifstream ifile (argv[1]);
    
    if(!ifile)
    {
        cout << "File not found." << endl;
        exit(-1);
    }
    
    // number of vertices and edges
    int V, E;
    int i, j, k, u, v;
    double w;
    
    ifile >> V >> E;
    

    

    

    graph g(V);
    
    for(int i = 0; i < V; i++){
        g.color[i] = WHITE;
    }
    
    // Matrices declared and initialised to infinity and zero respectively
    dist = new Distance * [V];
    for (int i = 0; i < V; i++)
        dist[i] = new Distance[V];
    
    
    parent = new int *[V];
    for (int i = 0; i < V; i++)
        parent[i] = new int[V];
    
    
    
    // Read edges from input file
    for (i=0; i<E; i++)
    {
        ifile >> u >> v >> w;
        dist[u][v].setWeight(w);
        dist[v][u].setWeight(w);
        parent[u][v] = u;
        parent[v][u] = v;
        
        g.add_edge(u, v);
        g.add_edge(v, u);
        
    }
    ifile.close();
    
    
    size_t maxIndex = 0;
    
    std::vector<graph> reached_by(g.number_of_nodes(), g.number_of_nodes());
    std::queue<size_t> q;
    size_t start = 0;
    g.dist[0] = 0;
    q.push(start);
    while (!q.empty()) {
        size_t node = q.front();
        q.pop();
        

        
        for (size_t i = 0; i < g.neighbours_of(node).size(); i++) {
            size_t currentNode = g.getNeighbours(node, i);
            if (g.getColor(currentNode) != BLACK) {
                if (g.getColor(currentNode) == WHITE) {
                    q.push(currentNode);
                    g.dist[currentNode] = g.dist[node] + 1;
                    if(maxIndex < g.dist[currentNode]){
                        maxIndex = g.dist[currentNode];
                        start = currentNode;
                    }
                }
                g.setColor(currentNode, GRAY);
            }
            
        }
        g.setColor(node, BLACK);
        
    }
    for(size_t i = 0; i < V; i++){
        g.setColor(i, WHITE);
        g.dist[i] = 0;
    }
    
    q.push(start);
    while (!q.empty()) {
        size_t node = q.front();
        q.pop();
        
        
        
        for (size_t i = 0; i < g.neighbours_of(node).size(); i++) {
            size_t currentNode = g.getNeighbours(node, i);
            if (g.getColor(currentNode) != BLACK) {
                if (g.getColor(currentNode) == WHITE) {
                    q.push(currentNode);
                    g.dist[currentNode] = g.dist[node] + 1;
                    if(maxIndex < g.dist[currentNode]){
                        maxIndex = g.dist[currentNode];
                        start = currentNode;
                    }
                }
                g.setColor(currentNode, GRAY);
            }
            
        }
        g.setColor(node, BLACK);
        
    }

    cout << "Diameter : " << maxIndex+1 << endl;
    
    // Path from vertex to itself is set
    for (i=0; i<V; i++)
    {
        dist[i][i].setWeight(0);
        parent[i][i] = i;
    }
    
    
    // Actual Floyd Warshall Algorithm
    for (k=0; k<V; k++)
    {
        for (i=0; i<V; i++)
        {
            for (j=0; j<V; j++)
            {
                if (dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j]    =   dist[i][k]    +   dist[k][j];
                    parent[i][j]  =   parent[k][j];
                }
            }
        }
    }
    
    
    // Check for negative cycles
    for (i=0; i<V; i++)
    {
        if (!dist[i][i].isZero())
        {
            cout << "Negative cycle at : " << i+1 << endl;
            return 0;
        }
    }
    
    
    // Print all paths
    cout << "All Pairs Shortest Paths : \n\n";
    for (i=0; i<V; i++)
    {
        cout << endl;
        for (j=0; j<V; j++)
        {
            cout << "From : " << i << " To : " << j << endl;
            cout << "Path : " << i << obtainPath(i,j) << j << endl;
            cout << "Distance : " << dist[i][j].getWeight() << endl << endl;
        }
    }
    
    delete [] dist;
    delete [] parent;
    
    
    //Stop the clock
    clock_t end = clock();
    
    double time = double(end - begin);
    
    cout << "Time : " << time <<"ms"<< endl;
    return 0;
}






