#include <iostream>
#include <cassert>

#include "Graph.h"

class GraphTest {
	public:
		UndirectedGraph<int, std::string> undirectedGraph;

		GraphTest() {}

		void runTests() {
			testInsert();
			testFind();
			testEdges();
			testMergeGraphs();
			testBfs();
			testDfs();
			testDijkstra();
			testFloydWarshall();
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

			std::cout << "[+] Insertion tested operator[], emplace, size, erase, contains" << std::endl;
		}

		void testFind() {
			auto it = undirectedGraph.find(1);
			assert(it != undirectedGraph.end());
			assert(it->second->getData() == "Node 1");
			assert(undirectedGraph.find(6) == undirectedGraph.end());	// key 6 not present in graph
			assert(undirectedGraph.contains(6) == false);

			std::cout << "[+] tested find(), node->getData()" << std::endl;
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

			std::cout << "[+] tested operator(), isConnectedTo(), removeEdge()" << std::endl;
		}

		void testMergeGraphs() {}
		void testBfs() {}
		void testDfs() {}
		void testDijkstra() {}
		void testFloydWarshall() {}

};


int main() {
	GraphTest tester;
	tester.runTests();
	return 0;
}
