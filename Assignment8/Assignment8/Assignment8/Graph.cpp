#include "Graph.h"
#include <vector>
#include <iostream>

using namespace std;

Graph::Graph()
{
    
}

Graph::~Graph()
{
    //dtor
}
void Graph::addEdge(string v1, string v2, int weight){
    
    for(size_t i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1){
            for(size_t j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);
                }
            }
        }
    }
}
void Graph::addVertex(string n){
    bool found = false;
    for(size_t i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = n;
        vertices.push_back(v);
        
    }
}

void Graph::displayEdges(){
    //loop through all vertices and adjacent vertices
    for(size_t i = 0; i < vertices.size(); i++){
        cout<<vertices[i].name<<"-->";
        cout<<vertices[i].adj[0].v->name;
        for(size_t j = 1; j < vertices[i].adj.size(); j++){
            cout<<"***"<<vertices[i].adj[j].v->name;
        }
        cout<<endl;
    }
    
}

int Graph::isAdjacent(std::string v1, std::string v2)
{
    vertex v;
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i].name == v1) {
            v = vertices[i];
            break;
        }
    }
    for (int i = 0; i < v.adj.size(); i++) {
        if (v.adj[i].v->name == v2) {
            return true;
        }
    }
    return false;
}

