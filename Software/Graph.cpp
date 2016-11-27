//
//  Graph.cpp
//  Software
//
//  Created by Rei Halle on 09/11/2016.
//  Copyright © 2016 Rei Halle. All rights reserved.
//


# include <iostream>
# include <fstream>
# include <string>
#include <vector>
#include <list>
#include <queue>
#define WHITE 1
#define GRAY 2
#define BLACK 3
#define NIL -1
using namespace std;




using namespace::std;

// class to handle comparisions and additions of infinite weighted quantities, used to store distances
class BFS {
private:
    int size;
    const int infinity = std::numeric_limits<int>::max();
public:
    std::vector<std::list<int>> graph;
    std::queue<int> *queue;
    std::list<int> *nodes;
    int *dist, *pred, *color, *partition;
    
    BFS(){
    }
    
    
    BFS(int v){
        std::vector<std::list<int>> graph(v);
        
        for (int i = 0; i < v; i++) {
            graph[i] = *new list<int>;
        }
        
        
        nodes = new std::list<int>();
        queue = new std::queue<int>();
        dist = new int[size];
        pred = new int[size];
        color = new int[size];
        partition = new int[size];
        clear();
        
        

    }
    
    void clear(){
        for (int i = 0; i< size; i++) {
            dist[i] = infinity;
            pred[i] = NIL;
            color[i] = WHITE;
            partition[i] = 0;
        }
    }
    
    void BFSearch(int s){

        clear();
        bool ans = true;
        int vertex = s;
        color[vertex] = GRAY;
        dist[vertex] = 0;
        pred[vertex] = NIL;
        queue->push(vertex);
        std::list<int> list;
        std::list<int>::iterator iter;
        while (!queue->empty()) {
            int current = queue->front();
            queue -> pop();
            list = graph.at(current);
            iter = list.begin();
            while (ans && iter != list.end()) {
                int currentNode = *iter++;
                if(color[currentNode] == WHITE){
                    color[currentNode] = GRAY;
                    dist[currentNode] = dist[current] + 1;
                    pred[currentNode] = current;
                    queue->push(currentNode);
                }
                color[current] = BLACK;
            }
            
            
        }
    }

    
};


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
 /*   if(argc < 2)
    {
        cout << "Check README for usage." << endl;
        exit(-1);
    }
  */
/*    argv[1] = "-h";
    
    if( !strcmp(argv[1], "-h")){
        cout << " -EV = Exclude Vertex" << endl;
        exit(0);
    }
  */

    argv[1] = "/Users/reihalle/Downloads/Ex1/G0.txt";
    
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
    
    return 0;
}

#include "Graph.hpp"

Graph::Graph(int V){
    this->V = V;
    adj = new list<AdjListNode>[V];
}

void Graph::addEdge(int u, int v, double weight){
    AdjListNode node(v, weight);
    adj[u].push_back(node); // Add v to u's list
}



void Graph::readGraph(const char *In){
    
    FILE *inFile;
    inFile = fopen(In, "r");
    if (inFile==NULL){
        printf("Error opening file\n");
    } else{
 
        
        int nodes ,edges, node, edge;
        double weight;
        fscanf(inFile, "%d %d", &nodes, &edges);
        this->V = nodes;
        this->E = edges;
        adj = new list<AdjListNode>[nodes];
        
        for(int i = 0; i < edges; i++){
            fscanf(inFile, "%d %d %lf", &node, &edge, &weight);
            this->addEdge(node, edge, weight);

        }
        fclose(inFile);

    }


    
}


