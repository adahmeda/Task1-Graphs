//
//  main.cpp
//  Software
//
//  Created by Rei Halle on 09/11/2016.
//  Copyright © 2016 Rei Halle. All rights reserved.
//

#include <iostream>
#include "Graph.hpp"

// Driver program to test above functions
int main()
{
    // Create a graph given in the above diagram.  Here vertex numbers are
    // 0, 1, 2, 3, 4, 5 with following mappings:
    // 0=r, 1=s, 2=t, 3=x, 4=y, 5=z
    Graph g(6);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 3, 6);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 4, 4);
    g.addEdge(2, 5, 2);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 4, -1);
    g.addEdge(4, 5, -2);
    
    int s = 1;
    cout << "Following are shortest distances from source " << s <<" \n";
    g.shortestPath(s);
    cout << "\n";
    
    
    Graph g2(0);
    g2.readGraph("/Users/reihalle/Downloads/Ex1/G0.txt");
    cout << "Following are shortest distances from source " << "0" <<" \n";
    g2.shortestPath(0);
    cout << "\n";
    
    
    return 0;
}