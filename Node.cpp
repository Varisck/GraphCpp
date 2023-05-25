#include "Node.h"

/*

	Edges

*/

template<class Data, class Cost = std::size_t>
Node<Data, Cost>::edge::edge(const std::weak_ptr<Node> &ptr, Cost &c) 
	: nodeTo_(ptr), cost_(std::make_shared<Cost>(c)) {} 

template<class Data, class Cost = std::size_t>
Node<Data, Cost>::edge::edge(const edge& other) 
	: nodeTo_(other.nodeTo_), cost_(other.cost_) {} 

template<class Data, class Cost = std::size_t>
Cost& Node<Data, Cost>::edge::cost() const {
	return *cost_;
}

template<class Data, class Cost = std::size_t>
std::shared_ptr<Cost> Node<Data, Cost>::edge::costPtr() const {
	return cost_;
}

/*

	Node

*/

template<class Data, class Cost>
Node<Data, Cost>::Node() {}

template<class Data, class Cost>
Node<Data, Cost>::Node(const Data &d) : data_(d) {}

template<class Data, class Cost>
Node<Data, Cost>::Node(Data&& data) : data_(std::move(data)) {}

template<class Data, class Cost>
Node<Data, Cost>::Node(Node<Data, Cost>&& other) : data_(std::move(other.data_)) {}

template<class Data, class Cost>
Node<Data, Cost>::Node(const Node<Data, Cost> &n) {
	data_ = n.data_;
}

template<class Data, class Cost>
Data& Node<Data, Cost>::getData() {
	return data_;
}

template<class Data, class Cost>
Data& Node<Data, Cost>::getData() const {
	return data_;
}



