#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <vector>


using namespace std;

struct vertex;

struct adjVertex {
	vertex* v;
	int weight;
};

struct vertex {
	string key;
	vector<adjVertex> adjacent;
	bool visited = false;
};

class Graph {
	private:
		//vertices
		vector<vertex> vertices;
		vertex* findVertex(string);
	public:
		//methods for accessing graphs
		Graph();
		~Graph();
		void insertVertex(string);	//identifier of the vertex
		void insertEdge(string,string,int);	//start, end, weight
		void printGraph();
        void DFSpath(string, string);
		void findNodeWithMaximumAdjacent(string);

};

Graph::Graph() {}

Graph::~Graph() {}

void Graph::insertVertex(string value) {
	bool found = false;
	int i=0;
	while (i<vertices.size() && !found) {
		if (vertices[i].key == value) {
			found = true;
		}
		i++;
	}
	if (!found) {
		vertex v;
		v.key = value;
		vertices.push_back(v);
	}
	else {
		cout << "There is already a vertex " << value << " in this graph" << endl;
	}
}

vertex* Graph::findVertex(string value) {
	int i=0;
	while (i<vertices.size()) {
		if (vertices[i].key == value) {
			return &vertices[i];
		}
		i++;
	}
	return nullptr;
}

void Graph::insertEdge(string v1, string v2, int weight) {
	vertex *vStart = findVertex(v1);
	vertex *vEnd = findVertex(v2);
	if (vStart!=nullptr && vEnd!=nullptr) {
		//this code assumes that an edge doesn't exist
		//write some error checking to handle when it does
		adjVertex v1v2Edge;
		v1v2Edge.weight = weight;
		v1v2Edge.v = vEnd;
		vStart->adjacent.push_back(v1v2Edge);
	}
	else {
		if (vStart == nullptr) {
			cout << "no vertex with name " << v1 << " in this graph" << endl;
		}
		if (vEnd == nullptr) {
			cout << "no vertex with name " << v2 << " in this graph" << endl;
		}
	}
}

void Graph::findNodeWithMaximumAdjacent(string start) {
    size_t count = 1;
    string val = "";
    
    queue<vertex *> q;
    q.push(findVertex(start));
    while (!q.empty()) {
        vertex *v = q.front();
        q.pop();
        
        //Analyze current node
        cout<<v->key<<" ";
        if (v->adjacent.size() > count) {
            count = v->adjacent.size();
            val = v->key;
        }
        v->visited = true;
        
        //Add children
        for (int i = 0; i < v->adjacent.size(); i++) {
            if (!v->adjacent[i].v->visited) {
                vertex *t = v->adjacent[i].v;
                t->visited = true;
                q.push(t);
            }
        }
    }
    
    cout<<endl<<val<<endl;
}


void Graph::DFSpath(string src, string dst) {
    stack<vertex *> s;
    s.push(findVertex(src));
    
    while (!s.empty()) {
        vertex *v = s.top(); s.pop();
        v->visited = true;
        cout<<v->key<<" -> ";
        
        for (int i = 0; i < v->adjacent.size(); i++) {
            vertex *t = v->adjacent[i].v;
            if (t->key == dst) {
                cout<<dst<<endl;
                return;
            } else {
                s.push(t);
                t->visited = true;
            }
        }
    }
}



int main() {

	Graph myGraph;

	myGraph.insertVertex("A");
	myGraph.insertVertex("B");
	myGraph.insertVertex("C");
	myGraph.insertVertex("D");
	myGraph.insertVertex("E");
	myGraph.insertVertex("F");
	myGraph.insertVertex("G");

	myGraph.insertEdge("A", "B", 0); myGraph.insertEdge("B", "A", 0);
	myGraph.insertEdge("A", "C", 0); myGraph.insertEdge("C", "A", 0);
	myGraph.insertEdge("B", "D", 0); myGraph.insertEdge("D", "B", 0);
	myGraph.insertEdge("C", "D", 0); myGraph.insertEdge("D", "C", 0);
	myGraph.insertEdge("E", "D", 0); myGraph.insertEdge("D", "E", 0);
	myGraph.insertEdge("E", "B", 0); myGraph.insertEdge("B", "E", 0);
	myGraph.insertEdge("E", "G", 0); myGraph.insertEdge("G", "E", 0);
	myGraph.insertEdge("F", "G", 0); myGraph.insertEdge("G", "F", 0);
    
    cout<<"BFS"<<endl;
    myGraph.findNodeWithMaximumAdjacent("A");
    
    Graph g;
    
    g.insertVertex("A");
    g.insertVertex("B");
    g.insertVertex("C");
    g.insertVertex("D");
    g.insertVertex("E");
    g.insertVertex("F");
    g.insertVertex("G");
    
    g.insertEdge("A", "B", 0); g.insertEdge("B", "A", 0);
    g.insertEdge("A", "C", 0); g.insertEdge("C", "A", 0);
    g.insertEdge("B", "D", 0); g.insertEdge("D", "B", 0);
    g.insertEdge("C", "D", 0); g.insertEdge("D", "C", 0);
    g.insertEdge("E", "D", 0); g.insertEdge("D", "E", 0);
    g.insertEdge("E", "B", 0); g.insertEdge("B", "E", 0);
    g.insertEdge("E", "G", 0); g.insertEdge("G", "E", 0);
    g.insertEdge("F", "G", 0); g.insertEdge("G", "F", 0);
    
    cout<<endl<<"DFS"<<endl;
    g.DFSpath("A", "G");
}
