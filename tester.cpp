#include <iostream>
#include <cassert>
#include <random>

#include "Graph.h"

class GraphTest {
	public:
		UndirectedGraph<int, std::string> undirectedGraph;

		GraphTest() {}

		template <class Key, class Data, class Cost, GraphType GT>
		void printGraph(std::string name, Graph<Key, Data, Cost, GT> graph) {
			std::cout << name << ": " << graph.size() << std::endl;
			for(auto node = graph.cbegin(); node != graph.cend(); ++node){
				std::cout << "Key: " << node->first << " value: " << node->second->getData() << std::endl;
			}
			std::cout << "Connections: " << std::endl;
			for(auto node = graph.cbegin(); node != graph.cend(); ++node){
				std::cout << "Key: " << node->first;
				for(auto edge = node->second->cbegin(); edge != node->second->cend(); ++edge){
					if(auto nodeTo = edge->getNodeTo().lock())
						std::cout << " connected to: " << nodeTo->getKeyInGraph() << " (" << edge->cost() << "), ";
				}
				std::cout << std::endl;
			}
		}

		void runTests() {
			testInsert();
			testFind();
			testEdges();
			testMergeGraphs();
			testBfs();
			testDfs();
			testDijkstra();
			testFloydWarshall();
			testPrim();
			std::cout << "[+] Testing finished!" << std::endl;
		}

		void testInsert() {
			undirectedGraph[1] = "Node 1";
			undirectedGraph[2] = "Node start 2";
			auto resEmplace = undirectedGraph.emplace(3, std::string{"Node 3"});

			assert(resEmplace.second == true);
			assert(undirectedGraph[3] == "Node 3");
			assert(undirectedGraph[2] == "Node start 2");

			undirectedGraph[2] = "Node 2";
			assert(undirectedGraph[2] == "Node 2");
			assert(undirectedGraph[4] == "");

			auto size = undirectedGraph.size();
			assert(size == 4);

			undirectedGraph.erase(4);
			assert(undirectedGraph.size() == 3);
			assert(undirectedGraph.contains(4) == false);
			assert(undirectedGraph.contains(2) == true);

			// undirectedGraph[4];

			std::cout << "[+] Tested Insertion operator[], emplace, size, erase, contains" << std::endl;
		}

		void testFind() {
			auto it = undirectedGraph.find(1);
			assert(it != undirectedGraph.end());
			assert(it->second->getData() == "Node 1");
			assert(undirectedGraph.find(6) == undirectedGraph.end());	// key 6 not present in graph
			assert(undirectedGraph.contains(6) == false);

			std::cout << "[+] Tested find(), node->getData()" << std::endl;
		}

		void testEdges() {
			undirectedGraph(1, 2) = 100;
			undirectedGraph(2, 3, 777);

			assert(undirectedGraph(2, 3) == undirectedGraph(3, 2));
			assert(undirectedGraph(2, 3) == 777);
			assert(undirectedGraph(1, 2) == 100);
			assert(undirectedGraph(2, 1) == -1);

			assert(undirectedGraph.isConnectedTo(2, 3) == true);
			assert(undirectedGraph.isConnectedTo(2, 1) == true);
			assert(undirectedGraph.isConnectedTo(4, 2) == false);
			assert(undirectedGraph.isConnectedTo(4, 2) == false);
			assert(undirectedGraph.isConnectedTo(undirectedGraph.find(3), undirectedGraph.find(2)) == true);

			undirectedGraph.removeEdge(1, 2);
			undirectedGraph.removeEdge(2, 3);
			assert(undirectedGraph.isConnectedTo(1, 2) == false);
			assert(undirectedGraph.isConnectedTo(2, 1) == false);
			assert(undirectedGraph.isConnectedTo(2, 3) == false);
			assert(undirectedGraph.isConnectedTo(3, 2) == false);

			undirectedGraph(1, 2, 100);
			undirectedGraph(2, 3, 789);
			undirectedGraph(4, 2) = 345;

			// nodes not existing
			undirectedGraph.removeEdge(10, 12);
			assert(undirectedGraph.contains(10) == false);
			assert(undirectedGraph.contains(12) == false);

			std::cout << "[+] Tested operator(), isConnectedTo(), removeEdge()" << std::endl;
		}

		void testMergeGraphs() {}
		void testBfs() {}
		void testDfs() {}
		void testDijkstra() {}
		void testFloydWarshall() {}
		
		void testPrim() {
			UndirectedGraph<int, char> testPrimG;
			testPrimG[1] = 'a';
			testPrimG[2] = 'b';
			testPrimG[3] = 'c';
			testPrimG[4] = 'd';
			testPrimG[5] = 'e';
			testPrimG[6] = 'f';

			testPrimG(1, 2, 10);
			testPrimG(2, 3, 2);
			testPrimG(3, 5, 1);
			testPrimG(5, 4, 1);
			testPrimG(2, 5, 50);
			testPrimG(5, 6, 2);

			auto mst = testPrimG.prim(1);
			auto mstFromC = testPrimG.prim(3);
			auto mstFromD = testPrimG.prim(4);
			auto mstFromNoIterator = testPrimG.prim();

			assert(mst(1, 2) == 10);
			assert(mst(2, 3) == 2);
			assert(mst(3, 5) == 1);
			assert(mst(5, 4) == 1);
			assert(mst(5, 6) == 2);

			assert(mstFromC(1, 2) == 10);
			assert(mstFromC(2, 3) == 2);
			assert(mstFromC(3, 5) == 1);
			assert(mstFromC(5, 4) == 1);
			assert(mstFromC(5, 6) == 2);

			assert(mstFromD(1, 2) == 10);
			assert(mstFromD(2, 3) == 2);
			assert(mstFromD(3, 5) == 1);
			assert(mstFromD(5, 4) == 1);
			assert(mstFromD(5, 6) == 2);

			assert(mstFromNoIterator(1, 2) == 10);
			assert(mstFromNoIterator(2, 3) == 2);
			assert(mstFromNoIterator(3, 5) == 1);
			assert(mstFromNoIterator(5, 4) == 1);
			assert(mstFromNoIterator(5, 6) == 2);

			std::cout << "[+] Tested prim algorithm" << std::endl;
		}

};

void testBigGraph() {
    // Create a graph with int keys, double data, and float costs
    Graph<int, double, float> myGraph;

    // Create a random number generator for generating node data
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 100.0);

    // Create a large graph with 10,000 nodes
    const int numNodes = 10000;
    for (int i = 1; i <= numNodes; ++i) {
        double nodeData = dis(gen); // Generate random node data
        myGraph.emplace(i, nodeData); // Add node to the graph
    }

    // Connect nodes randomly with edges
    std::uniform_int_distribution<> nodeDist(1, numNodes);
    std::uniform_real_distribution<> costDist(1.0, 10.0);
    const int numEdges = 50000; // Total number of edges to create

    for (int i = 0; i < numEdges; ++i) {
        int node1 = nodeDist(gen);
        int node2 = nodeDist(gen);
        float cost = costDist(gen);

        // Add an edge between the two randomly chosen nodes with a random cost
        myGraph(node1, node2) = cost;
    }

  	myGraph.prim();
  	std::cout << "[+] BigGraph end" << std::endl;
}


int main() {
	GraphTest tester;
	tester.runTests();
	// testBigGraph();
	return 0;
}
