
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <map>

#include "Graph.h"

using namespace std;


typedef GraphArc<pair<std::string, int>, int> Arc;
typedef GraphNode<pair<std::string, int>, int> Node;

void visit(Node * node) {
	cout << "Visiting: " << node->data().first << endl;
}

int main(int argc, char *argv[]) {

	Graph<pair<std::string, int>,int> graph(6);

	std::pair<string, int> nodeL;
	std::map<string, int> nodeM;

	int i = 0;
	ifstream myfile;
	myfile.open("Lab4Nodes.txt");

	while (myfile >> nodeL.first) 
	{
		graph.addNode(nodeL, i);
		nodeM[nodeL.first] = i;
		i++;
	}

	myfile.close();
	myfile.open("Lab4Arcs.txt");

	std::string start, end;
	int cost;
	while (myfile >> start >> end >> cost) 
	{
		std::cout << start << " " << end << " " << cost << std::endl;
		graph.addArc(nodeM[start],nodeM[end],cost);
	}
	myfile.close();

	Node* startN = graph.nodeIndex(0);
	Node* endN = graph.nodeIndex(5);

	std::vector<Node*> path;

	// Now traverse the graph.
	graph.ucs(startN,endN,visit,path);
	
	
	system("PAUSE");

}
