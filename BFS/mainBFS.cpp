//a program that implements breadth first search (BFS) on an undirected graph

#include <vector>
#include <forward_list>
#include <iostream>
#include <queue> 
#include <stack>

using std::cout;

enum class Color {black, gray, white};

std::ostream& operator<<(std::ostream& out, Color col) {
	switch (col) {
	case Color::black: out << "black";
		break;
	case Color::gray: out << "gray";
		break;
	case Color::white: out << "white";
		break;
	default: out << "invalid color";
	}
	return out;
}

//vertex in graph with attributes for breadth first search
struct Vertex {
	Color col;
	int dist; //distance from the vertex at beginning of BFS
	int prev; //previous vertex in the BFS
	//the vector index (in UGraph::vertices) of the other vertex connected by the edge is stored here
	std::forward_list<int> adj_list; 
};

//class for adjacency list representation of undirected graph
class UGraph {
	std::vector<Vertex> vertices;
	int vTotal; //total number of vertices
public:
	explicit UGraph(int v) {
		if (v <= 0)
			throw std::runtime_error("invalid number of vertices in constructor\n");
		vTotal = v;
		vertices = std::vector<Vertex>(v, Vertex{ Color::white, -1, -1, std::forward_list<int>{} });
	}
	void addEdge(int, int);
	void display();
	void bfs(int);
	void printPath(int, int);
};

//add edge for vertices with indices in the vector: v1 and v2
void UGraph::addEdge(int v1, int v2) {
	if (v1 < 0 || v1 >= vTotal || v2 < 0 || v2 >= vTotal)
		throw std::runtime_error("invalid vertex value in addEdge");
	if (v1 != v2) {
		vertices[v1].adj_list.push_front(v2);
		vertices[v2].adj_list.push_front(v1);
	}
	else
		vertices[v1].adj_list.push_front(v2);
}

void UGraph::display() {
	cout << "displaying undirected graph:\n";
	for (int i = 0; i < static_cast<int>(vertices.size()); i++) {
		cout << "vertex " << i << " - color: " << vertices[i].col << " | distance: " << vertices[i].dist
			<< " | previous: " << vertices[i].prev << '\n' << "edges: ";
		for (auto it = vertices[i].adj_list.begin(); it != vertices[i].adj_list.end(); it++)
			cout << *it << ' ';
		cout << '\n';
	}
	
}

//sets attributes of the vertices according to a bfs starting at vertex s
//s is the index of the vertex in UGraph::vertices
void UGraph::bfs(int s) {
	for (int i = 0; i < static_cast<int>(vertices.size()); i++) {
		if (i != s) {
			vertices[i].col = Color::white;
			vertices[i].dist = -1;
			vertices[i].prev = -1;
		}
	}
	vertices[s].col = Color::gray;
	vertices[s].dist = 0;
	vertices[s].prev = -1;
	std::queue<int> q;
	q.push(s);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (auto it = vertices[u].adj_list.begin(); it != vertices[u].adj_list.end(); it++) {
			if (vertices[*it].col == Color::white) {
				vertices[*it].col = Color::gray;
				vertices[*it].dist = vertices[u].dist + 1;
				vertices[*it].prev = u;
				q.push(*it);
			}
		}
		vertices[u].col = Color::black;
	}
}

//assumes bfs has already been called with s
//prints a shortest path from vertex s to vertex v
//s and v are the vector indices (in UGraph::vertices) of the vertices
void UGraph::printPath(int s, int v) {
	int saveV{ v };
	std::stack<int> path;
	while (vertices[v].prev >= 0) {
		path.push(v);
		v = vertices[v].prev;
	}
	if (v != s)
		cout << "no path from " << s << " to " << saveV << '\n';
	else {
		cout << "path: " << s << ' ';
		while (!path.empty()) {
			cout << path.top() << ' ';
			path.pop();
		}
		cout << '\n';
	}

}

int main() {
	try {
		UGraph g{ 8 };
		g.addEdge(0,1);
		g.addEdge(0,4);
		g.addEdge(1,5);
		g.addEdge(2,5);
		g.addEdge(5,6);
		g.addEdge(2,6);
		g.addEdge(2,3);
		g.addEdge(3,6);
		g.addEdge(3,7);
		g.addEdge(6,7);
		g.addEdge(6, 6);
		g.addEdge(7, 7);
		
		g.bfs(7);
		g.display();
		g.printPath(7, 5);
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
	}
}