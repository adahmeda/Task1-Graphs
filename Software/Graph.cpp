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

using namespace::std;

// class to handle comparisions and additions of infinite weighted quantities, used to store distances
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
    }
    ifile.close();
    
    
    
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


