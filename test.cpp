#include "Graph.h"
#include <iostream>
#include <random>

struct W {
	int _val;
	public:
		W() {}
		W(int v) : _val(v) {}
		~W() { std::cout << "Distruttore di W!" << std::endl; }
		friend std::ostream& operator<<(std::ostream& os, const W& w);
};

std::ostream& operator<<(std::ostream& os, const W& w) {
	os << w._val;
	return os;			
}

int main() {

	{
		Graph<int, double> g;
		g[12] = 12.1;
	
		std::cout << g[12] << std::endl;
	
		std::cout << "Cambio nodo 12 a 151.12: " << std::endl;
	
		g[12] = 151.12;
	
		std::cout << g[12] << std::endl;
	
		std::cout << "Aggiungo nodo 1 con valore 100: " << std::endl;
	
		g[1] = 100;
	
		std::cout << g[1] << std::endl;
	
		std::cout << "Aggiungo arco tra 12 e 1 con valore 25: " << std::endl;
	
		g(1, 12) = 25;
	
		std::cout << "Valore dell'arco tra 12 e 1: " << g(1, 12) << std::endl;
	
		std::cout << "Creo arco tra 12 e 1 con valore predefinito (std::numeric_limits<Cost>::max()): " << g(12, 1) << std::endl;
	
		std::cout << "Testing operator()(key, key, cost) with node 7, 8:" << std::endl;
	
		g[7] = 7;
		g[8] = 8;
	
		g(7, 8, 78);
	
		std::cout << "Peso tra 7 e 8: " << g(7, 8) << " e peso tra 8 e 7: " << g(8, 7) << std::endl;
	
		std::cout << std::endl << "Test con peso senza numeric_limits: " << std::endl;	
	
		Graph<int, int, W> weighted;
	
		std::cout << "Creo nodi con valore 1 e 2: " << std::endl;
	
		weighted[1] = 1;
		weighted[2] = 2;
	
		std::cout << "Grafo creato con nodi 1 e 2" << std::endl;
	
		weighted(1, 2);
		std::cout << "Creato arco tra 1 e 2 con valore: " << weighted(1, 2) << std::endl;
	
		std::cout << "New undirected Graph: " << std::endl;
	
		UndirectedGraph<char, int> undir;
	
		undir['a'] = 12;
		undir['b'] = 11;
		undir['c'] = 10;
		undir['d'] = 9;
	
		undir('a', 'b') = 100;
	
		std::cout << undir('a', 'b') << " " << undir('b', 'a') << std::endl;
	
		std::cout << std::endl << "Testing moving copying: " << std::endl;
		std::cout << "Move: " << undir('a', 'b') << std::endl;
		char a = 'a';
		char b = 'b';
		std::cout << "Copy: " << undir(a, b) << std::endl;
	
		std::cout << std::endl << std::endl;
	
		undir.erase('a');
		undir.erase(b);
	
		for (const auto& node : undir) {
	    	// Access the key and data of the current node using node.first and node.second
			std::cout << "Node " << node.first << " with key " << node.second->getData() << std::endl;
		}
	
		std::cout << "Fine scope!" << std::endl;
	}

	{	
		UndirectedGraph<int, std::string> test;

		test[1] = "node 1";
		test[2] = "node 2";
		test[3] = "node 3";

		test(1, 2) = 12;
		test(2, 1) = 21;
		test(1, 3) = 13;

		std::cout << "Cost between 1-2: " << test.find(1)->second->getEdgeCost(test.find(2)->second) << std::endl;
		std::cout << "Size of the graph is: " << test.size() << " and the empty: " << test.empty() << std::endl;

		std::cout << "Key of node 1 in node element is: " << test.find(1)->second->getKeyInGraph() << std::endl;
		std::cout << "End of scope 2" << std::endl;
	}



	{
		UndirectedGraph<int, std::string> g1;
		UndirectedGraph<int, std::string> g2;

		g1[1] = "node 1";
		g1[2] = "node 2";
		g1[3] = "node 3";

		g1(1, 2, 100);

		g2[1] = "Node 1";
		g2[2] = "Node 2";
		g2[5] = "Node 5";

		g2(1, 2) = 9000;
		g2(1, 5, 500);

		std::cout << "G1: " << std::endl;
		for(auto node = g1.cbegin(); node != g1.cend(); ++node){
			std::cout << "Key: " << node->first << " value: " << node->second->getData() << std::endl;
		}
		for(auto node = g1.cbegin(); node != g1.cend(); ++node){
			std::cout << "Key: " << node->first;
			for(auto edge = node->second->cbegin(); edge != node->second->cend(); ++edge){
				if(auto nodeTo = edge->getNodeTo().lock())
					std::cout << " connected to: " << nodeTo->getKeyInGraph() << " (" << edge->cost() << "), ";
			}
			std::cout << std::endl;
		}

		std::cout << "G2: " << std::endl;
		for(auto node = g2.cbegin(); node != g2.cend(); ++node){
			std::cout << "Key: " << node->first << " value: " << node->second->getData() << std::endl;
		}
		for(auto node = g2.cbegin(); node != g2.cend(); ++node){
			std::cout << "Key: " << node->first;
			for(auto edge = node->second->cbegin(); edge != node->second->cend(); ++edge){
				if(auto nodeTo = edge->getNodeTo().lock())
					std::cout << " connected to: " << nodeTo->getKeyInGraph() << " (" << edge->cost() << "), ";
			}
			std::cout << std::endl;
		}

		g1.mergeGraph(g2);

		std::cout << "G1: " << std::endl;
		for(auto node = g1.cbegin(); node != g1.cend(); ++node){
			std::cout << "Key: " << node->first << " value: " << node->second->getData() << std::endl;
		}
		for(auto node = g1.cbegin(); node != g1.cend(); ++node){
			std::cout << "Key: " << node->first;
			for(auto edge = node->second->cbegin(); edge != node->second->cend(); ++edge){
				if(auto nodeTo = edge->getNodeTo().lock())
					std::cout << " connected to: " << nodeTo->getKeyInGraph() << " (" << edge->cost() << "), ";
			}
			std::cout << std::endl;
		}

		// auto ptr = g1.begin()->second;
		// std::shared_ptr<Node<std::string, int>> ptr2 = ptr;

		std::cout << "BFS start on g1" << std::endl;

		auto visitedNodes = g1.bfs(g1.begin());

		auto test = visitedNodes.begin();

		std::cout << "visitedNodes begin key " << test->first 
			<< " color " << test->second.color 
			<< " distance " << test->second.d << std::endl;

		if(auto ptr = visitedNodes[2].p.lock())
			std::cout << "predecessor of node key 2: " << ptr->getKeyInGraph() 
			<< " at distance: " << visitedNodes[2].d << std::endl;

		std::cout << "BFS end" << std::endl << "DFS start g1" << std::endl; 

		auto visitedNodesDFS = g1.dfs(g1.begin());

		for(auto it = visitedNodesDFS.begin(); it != visitedNodesDFS.end(); ++it){
			std::cout << "Node Key: " << it->first << " d: " << it->second.d << " f: " << it->second.f << std::endl;
		}

		std::cout << "DFS end" << std::endl;

		std::cout << "G1: " << g1.size() << std::endl;
		for(auto node = g1.cbegin(); node != g1.cend(); ++node){
			std::cout << "Key: " << node->first << " value: " << node->second->getData() << std::endl;
		}
		for(auto node = g1.cbegin(); node != g1.cend(); ++node){
			std::cout << "Key: " << node->first;
			for(auto edge = node->second->cbegin(); edge != node->second->cend(); ++edge){
				if(auto nodeTo = edge->getNodeTo().lock())
					std::cout << " connected to: " << nodeTo->getKeyInGraph() << " (" << edge->cost() << "), ";
			}
			std::cout << std::endl;
		}

		std::cout << "Removing node 5: " << std::endl;

		g1.erase(5);

		std::cout << "G1: " << g1.size() << std::endl;
		for(auto node = g1.cbegin(); node != g1.cend(); ++node){
			std::cout << "Key: " << node->first << " value: " << node->second->getData() << std::endl;
		}
		for(auto node = g1.cbegin(); node != g1.cend(); ++node){
			std::cout << "Key: " << node->first;
			for(auto edge = node->second->cbegin(); edge != node->second->cend(); ++edge){
				if(auto nodeTo = edge->getNodeTo().lock())
					std::cout << " connected to: " << nodeTo->getKeyInGraph() << " (" << edge->cost() << "), ";
			}
			std::cout << std::endl;
		}

		std::vector<std::size_t> res = g1.floydWarshall();

		for(int i = 0; i < g1.size(); ++i){
			for(int j = 0; j < g1.size(); ++j){
				std::cout << res[i * g1.size() + j] << " ";
			}
			std::cout << std::endl;
		}

		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;

		std::cout << "G1: " << g1.size() << std::endl;
		for(auto node = g1.cbegin(); node != g1.cend(); ++node){
			std::cout << "Key: " << node->first << " value: " << node->second->getData() << std::endl;
		}
		for(auto node = g1.cbegin(); node != g1.cend(); ++node){
			std::cout << "Key: " << node->first;
			for(auto edge = node->second->cbegin(); edge != node->second->cend(); ++edge){
				if(auto nodeTo = edge->getNodeTo().lock())
					std::cout << " connected to: " << nodeTo->getKeyInGraph() << " (" << edge->cost() << "), ";
			}
			std::cout << std::endl;
		}

		std::cout << "dijkstra start" << std::endl;

		auto djres = g1.dijkstra(g1.begin());

		for(auto it = djres.begin(); it != djres.end(); ++it){
			std::cout << "Node Key: " << it->first << " d: " << it->second.d << " f: " << it->second.f << std::endl;
		}


		std::cout << "dijkstra end" << std::endl;

	}

	{

		Graph<int, int> testG;
		for(int i = 1; i < 7; ++i){
			testG[i] = i;
		}

		testG(1, 2) = 10;
		testG(1, 4) = 11;
		testG(2, 3) = 12;
		testG(3, 4) = 7;
		testG(4, 5) = 3;
		testG(4, 6) = 4;
		testG(5, 6) = 0;

	    auto resdjt = testG.dijkstra(testG.begin());
	    auto resbfst = testG.bfs(testG.begin());

		for(auto it = resdjt.begin(); it != resdjt.end(); ++it){
			std::cout << "Node Key: " << it->first << " d: " << it->second.d << " d (bfs): " << resbfst[it->first].d << std::endl;
		}

		if(auto n = resbfst[6].p.lock())
			std::cout << "p of 6 in bfs: " << n->getKeyInGraph() << std::endl;
		if(auto n = resbfst[4].p.lock())
			std::cout << "p of 4 in bfs: " << n->getKeyInGraph() << std::endl;


	}


	// {
	// 	// huge graph
	//     // Create a graph with int keys, double data, and float costs
	//     Graph<int, double, float> myGraph;

	//     // Create a random number generator for generating node data
	//     std::random_device rd;
	//     std::mt19937 gen(rd());
	//     std::uniform_real_distribution<> dis(0.0, 100.0);

	//     // Create a large graph with 10,000 nodes
	//     const int numNodes = 10000;
	//     for (int i = 1; i <= numNodes; ++i) {
	//         double nodeData = dis(gen); // Generate random node data
	//         myGraph.emplace(i, nodeData); // Add node to the graph
	//     }

	//     // Connect nodes randomly with edges
	//     std::uniform_int_distribution<> nodeDist(1, numNodes);
	//     std::uniform_real_distribution<> costDist(1.0, 10.0);
	//     const int numEdges = 50000; // Total number of edges to create

	//     for (int i = 0; i < numEdges; ++i) {
	//         int node1 = nodeDist(gen);
	//         int node2 = nodeDist(gen);
	//         float cost = costDist(gen);

	//         // Add an edge between the two randomly chosen nodes with a random cost
	//         myGraph(node1, node2) = cost;
	//     }

	//     // Print the size of the graph
	//     std::cout << "Graph size: " << myGraph.size() << std::endl;


	//     auto hugeres = myGraph.dijkstra(myGraph.begin());
	//     auto resbfs = myGraph.bfs(myGraph.begin());

	// 	for(auto it = hugeres.begin(); it != hugeres.end(); ++it){
	// 		std::cout << "Node Key: " << it->first << " d: " << it->second.d << " d (bfs): " << resbfs[it->first].d << std::endl;
	// 	}


	// }


	{

		std::cout << "undirectedG test: " << std::endl;
		UndirectedGraph<int, int> testptr;

		testptr[1] = 1;
		testptr[2] = 2;

		testptr(1, 2) = 10;

		std::cout << testptr(1, 2) << "  " << testptr(2, 1) << std::endl;

		std::cout << testptr.begin()->second->findEdge(testptr.find(2)->second)->costPtr().use_count() << std::endl;

		std::cout << "directedG test: " << std::endl;
		DirectedGraph<int, int> testptr2;
		testptr2[1] = 1;
		testptr2[2] = 2;

		testptr2(1, 2) = 10;

		std::cout << testptr2(1, 2) << "  " << testptr2(2, 1) << std::endl;

		std::cout << testptr2.begin()->second->findEdge(testptr2.find(2)->second)->costPtr().use_count() << std::endl;


		std::cout << "Test removig endge: " << std::endl;
		std::cout << "isConnectedTo(1, 2): " << testptr2.isConnectedTo(1, 2) << std::endl;	
		testptr2.removeEdge(1, 2);
		std::cout << "isConnectedTo(1, 2): " << testptr2.isConnectedTo(1, 2) << std::endl;	
		std::cout << testptr2.find(2)->second->findEdge(testptr2.find(1)->second)->costPtr().use_count() << std::endl;

	}


	std::cout << "End program";

	return 0;
}
