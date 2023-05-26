#include "Node.h"

/*

	Edges

*/

template<class Data, class Key, class Cost = std::size_t>
Node<Data, Key, Cost>::edge::edge(const std::weak_ptr<Node> &ptr, Cost &c) 
	: nodeTo_(ptr), cost_(std::make_shared<Cost>(c)) {} 

template<class Data, class Key, class Cost = std::size_t>
Node<Data, Key, Cost>::edge::edge(const edge& other) 
	: nodeTo_(other.nodeTo_), cost_(other.cost_) {} 

template<class Data, class Key, class Cost = std::size_t>
Cost& Node<Data, Key, Cost>::edge::cost() const {
	return *cost_;
}

template<class Data, class Key, class Cost = std::size_t>
std::shared_ptr<Cost> Node<Data, Key, Cost>::edge::costPtr() const {
	return cost_;
}

/*

	Node

*/

template<class Data, class Key, class Cost>
Node<Data, Key, Cost>::Node() {}

template<class Data, class Key, class Cost>
Node<Data, Key, Cost>::Node(const Data &d) : data_(d) {}

template<class Data, class Key, class Cost>
Node<Data, Key, Cost>::Node(Data&& data) : data_(std::move(data)) {}

template<class Data, class Key, class Cost>
Node<Data, Key, Cost>::Node(Node<Data, Key, Cost>&& other) : data_(std::move(other.data_)) {}

template<class Data, class Key, class Cost>
Node<Data, Key, Cost>::Node(const Node<Data, Key, Cost> &n) {
	data_ = n.data_;
}

template<class Data, class Key, class Cost>
Data& Node<Data, Key, Cost>::getData() {
	return data_;
}

template<class Data, class Key, class Cost>
Data& Node<Data, Key, Cost>::getData() const {
	return data_;
}

template<class Data, class Key, class Cost>
typename Node<Data, Key, Cost>::iterator Node<Data, Key, Cost>::begin() noexcept {
	return listEdges_.start();
}

template<class Data, class Key, class Cost>
typename Node<Data, Key, Cost>::iterator Node<Data, Key, Cost>::end() noexcept {
	return listEdges_.end();
}

template<class Data, class Key, class Cost>
typename Node<Data, Key, Cost>::const_iterator Node<Data, Key, Cost>::begin() const noexcept {
	return listEdges_.start();
}

template<class Data, class Key, class Cost>
typename Node<Data, Key, Cost>::const_iterator Node<Data, Key, Cost>::end() const noexcept {
	return listEdges_.end();
}

template<class Data, class Key, class Cost>
typename Node<Data, Key, Cost>::const_iterator Node<Data, Key, Cost>::cbegin() const noexcept {
	return listEdges_.cbegin();
}

template<class Data, class Key, class Cost>
typename Node<Data, Key, Cost>::const_iterator Node<Data, Key, Cost>::cend() const noexcept {
	return listEdges_.cend();
}

