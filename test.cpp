#include "Graph.h"
#include <iostream>

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


	}


	std::cout << "End program";


	return 0;
}
