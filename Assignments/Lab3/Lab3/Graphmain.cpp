
#include <iostream>
#include <fstream>
#include <string>

#include "Graph.h"

using namespace std;


typedef GraphArc<std::string, int> Arc;
typedef GraphNode<std::string, int> Node;

void visit(Node * node) {
	cout << "Visiting: " << node->data() << endl;
}

int main(int argc, char *argv[]) {

	Graph<std::string, int> graph(25);

	std::string nodeLabel;
	int i = 0;
	ifstream myfile;
	myfile.open("nodes.txt");

	while (myfile >> nodeLabel) {
		graph.addNode(nodeLabel, i++);
	}

	myfile.close();
	myfile.open("arcs.txt");

	int from, to, weight;
	while (myfile >> from >> to >> weight) {
		graph.addArc(from, to, weight);
	}
	myfile.close();

	// Now traverse the graph.
	graph.breadthFirst(graph.nodeIndex(0), visit);
	
	//Q2
	Graph<std::string, int> graph2(25);

	std::string nodeLabel2;
	int i2 = 0;
	ifstream myfile2;
	myfile2.open("nodes.txt");

	while (myfile2 >> nodeLabel2) {
		graph2.addNode(nodeLabel2, i2++);
	}

	myfile2.close();
	myfile2.open("Q2Arcs.txt");

	int from2, to2, weight2;
	while (myfile2 >> from2 >> to2 >> weight2) {
		graph2.addArc(from2, to2, weight2);
	}
	myfile2.close();

	Node* temp = graph2.nodeIndex(15);
	// Now traverse the graph.
	graph2.adaptedBreadthFirst(graph2.nodeIndex(0), temp);

	while (temp->previous() != nullptr)
	{
		std::cout << temp->data() << std::endl;
		temp = temp->previous();
	}

	std::cout << temp->data() << std::endl;

	system("PAUSE");

}
