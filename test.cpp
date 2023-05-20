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

	std::cout << "Fine!" << std::endl;


}
