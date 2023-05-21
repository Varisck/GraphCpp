#include "Node.h"

/*

	Edges

*/

template<class Data, class Cost = std::size_t>
Node<Data, Cost>::edge::edge(const std::weak_ptr<Node> &ptr, Cost &c) 
	: _nodeTo(ptr), _cost(std::make_shared<Cost>(c)) {} 

template<class Data, class Cost = std::size_t>
Node<Data, Cost>::edge::edge(const edge& other) 
	: _nodeTo(other._target), _cost(other._cost) {} 

template<class Data, class Cost = std::size_t>
Cost& Node<Data, Cost>::edge::cost() const {
	return *_cost;
}

template<class Data, class Cost = std::size_t>
std::shared_ptr<Cost> Node<Data, Cost>::edge::costPtr() const {
	return _cost;
}

/*

	Node

*/

template<class Data, class Cost>
Node<Data, Cost>::Node() {}

template<class Data, class Cost>
Node<Data, Cost>::Node(const Data &d) : _data(d) {}

template<class Data, class Cost>
Node<Data, Cost>::Node(Data&& data) : _data(std::move(data)) {}

template<class Data, class Cost>
Node<Data, Cost>::Node(Node<Data, Cost>&& other) : _data(std::move(other._data)) {}

template<class Data, class Cost>
Node<Data, Cost>::Node(const Node<Data, Cost> &n) {
	_data = n._data;
}

template<class Data, class Cost>
Data& Node<Data, Cost>::getData() {
	return _data;
}

template<class Data, class Cost>
Data& Node<Data, Cost>::getData() const {
	return _data;
}



