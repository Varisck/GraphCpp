#include "Graph.h"
#include <iostream>

template <class Key, class Data, class Cost, GraphType GT>
Graph<Key, Data, Cost, GT>::Graph() {
	nodes_.clear();
	if (std::numeric_limits<Cost>::is_specialized) 	{
		maxCost_ = std::numeric_limits<Cost>::max();
	}
}

template <class Key, class Data, class Cost, GraphType GT>
Graph<Key, Data, Cost, GT>::Graph(const Graph &other) : nodes_(other.nodes_), maxCost_(other.maxCost_) {}

template <class Key, class Data, class Cost, GraphType GT>
Graph<Key, Data, Cost, GT>::~Graph() {
	nodes_.clear();
}

template <class Key, class Data, class Cost, GraphType GT>
std::size_t Graph<Key, Data, Cost, GT>::mergeGraph(Graph<Key, Data, Cost, GT>& other){

	if(*this.getGraphType() != other.getGraphType())
		return nodes_.size();

	for(iterator it = other.start(); it != other.end(); ++it){
		if(*this.contains(it->first)){

		}else{

		}
	}
	return nodes_.size();
}

template <class Key, class Data, class Cost, GraphType GT>
Data &Graph<Key, Data, Cost, GT>::operator[](const Key &key) {
	return emplace(key).first->second->getData();
}

template <class Key, class Data, class Cost, GraphType GT>
Data &Graph<Key, Data, Cost, GT>::operator[](Key &&key) {
	return emplace(std::move(key), std::move(node())).first->second->getData();
}

template <class Key, class Data, class Cost, GraphType GT>
std::pair<typename Graph<Key, Data, Cost, GT>::iterator, bool> Graph<Key, Data, Cost, GT>::emplace(const Key &key) {
	return emplace(key, node());
}

template <class Key, class Data, class Cost, GraphType GT>
std::pair<typename Graph<Key, Data, Cost, GT>::iterator, bool> Graph<Key, Data, Cost, GT>::emplace(Key &&key) {
	return emplace(std::move(key), std::move(node()));
}

template <class Key, class Data, class Cost, GraphType GT>
std::pair<typename Graph<Key, Data, Cost, GT>::iterator, bool> Graph<Key, Data, Cost, GT>::emplace(const Key &key, const node &n) {
	// std::cout << "copyed" << std::endl;
	return nodes_.emplace(key, std::make_shared<node>(n));
}

template <class Key, class Data, class Cost, GraphType GT>
std::pair<typename Graph<Key, Data, Cost, GT>::iterator, bool> Graph<Key, Data, Cost, GT>::emplace(Key &&key, node &&n) {
	// std::cout << "moved" << std::endl;
	return nodes_.emplace(std::move(key), std::move(std::make_shared<node>(n)));
}

template <class Key, class Data, class Cost, GraphType GT>
std::size_t Graph<Key, Data, Cost, GT>::erase(const Key& key){
	return nodes_.erase(key);
}

template <class Key, class Data, class Cost, GraphType GT>
std::size_t Graph<Key, Data, Cost, GT>::erase(Key&& key){
	return nodes_.erase(std::move(key));
}

template <class Key, class Data, class Cost, GraphType GT>
typename Graph<Key, Data, Cost, GT>::iterator Graph<Key, Data, Cost, GT>::erase(iterator pos){
	return nodes_.erase(pos);
}

template <class Key, class Data, class Cost, GraphType GT>
bool Graph<Key, Data, Cost, GT>::contains(const Key &key) const {
	return nodes_.contains(key);
}

template <class Key, class Data, class Cost, GraphType GT>
typename Graph<Key, Data, Cost, GT>::iterator Graph<Key, Data, Cost, GT>::find(const Key &key) {
	return nodes_.find(key);
}

template <class Key, class Data, class Cost, GraphType GT>
typename Graph<Key, Data, Cost, GT>::const_iterator Graph<Key, Data, Cost, GT>::find(const Key &key) const {
	return nodes_.find(key);
}

template <class Key, class Data, class Cost, GraphType GT>
Cost &Graph<Key, Data, Cost, GT>::operator()(iterator itNode1, iterator itNode2) {
	if (isConnectedTo(itNode1, itNode2)) {
		return itNode1->second->getEdgeCost(itNode2->second);
	}
	else {
		// if graph is undirected creates the reverse edge as well
		if(getGraphType() == undirected){
			std::shared_ptr<Cost> costPtr = itNode1->second->add_edge(itNode2->second, maxCost_).first->costPtr();
			itNode2->second->add_edge(itNode1->second, *costPtr);
			return *costPtr;
		}
		return (itNode1->second->add_edge(itNode2->second, maxCost_)).first->cost();
	}
}

template <class Key, class Data, class Cost, GraphType GT>
Cost &Graph<Key, Data, Cost, GT>::operator()(const Key &key1, const Key &key2) {
	iterator itNode1{emplace(key1).first};
	iterator itNode2{emplace(key2).first};
	return operator()(itNode1, itNode2);
}

template <class Key, class Data, class Cost, GraphType GT>
Cost &Graph<Key, Data, Cost, GT>::operator()(Key &&key1, Key &&key2) {
	iterator itNode1{emplace(std::move(key1)).first};
	iterator itNode2{emplace(std::move(key2)).first};
	return operator()(itNode1, itNode2);
}

template <class Key, class Data, class Cost, GraphType GT>
const Cost &Graph<Key, Data, Cost, GT>::operator()(const Key &key1, const Key &key2, const Cost &cost) {
	iterator itNode1{emplace(key1).first};
	iterator itNode2{emplace(key2).first};

	operator()(itNode1, itNode2) = cost;
	operator()(itNode2, itNode1) = cost;
	return cost;
}

template <class Key, class Data, class Cost, GraphType GT>
bool Graph<Key, Data, Cost, GT>::isConnectedTo(iterator itNode1, iterator itNode2) {
	return itNode1->second->isEdge(itNode2->second);
}

template <class Key, class Data, class Cost, GraphType GT>
typename Graph<Key, Data, Cost, GT>::iterator Graph<Key, Data, Cost, GT>::begin() noexcept {
	return nodes_.begin();
}

template <class Key, class Data, class Cost, GraphType GT>
typename Graph<Key, Data, Cost, GT>::iterator Graph<Key, Data, Cost, GT>::end() noexcept {
	return nodes_.end();
}

template <class Key, class Data, class Cost, GraphType GT>
typename Graph<Key, Data, Cost, GT>::const_iterator Graph<Key, Data, Cost, GT>::begin() const noexcept {
	return nodes_.begin();
}

template <class Key, class Data, class Cost, GraphType GT>
typename Graph<Key, Data, Cost, GT>::const_iterator Graph<Key, Data, Cost, GT>::end() const noexcept {
	return nodes_.end();
}

template <class Key, class Data, class Cost, GraphType GT>
typename Graph<Key, Data, Cost, GT>::const_iterator Graph<Key, Data, Cost, GT>::cbegin() const noexcept {
	return nodes_.cbegin();
}

template <class Key, class Data, class Cost, GraphType GT>
typename Graph<Key, Data, Cost, GT>::const_iterator Graph<Key, Data, Cost, GT>::cend() const noexcept {
	return nodes_.cend();
}

template <class Key, class Data, class Cost, GraphType GT>
typename Graph<Key, Data, Cost, GT>::reverse_iterator Graph<Key, Data, Cost, GT>::rbegin() noexcept {
	return nodes_.rbegin();
}

template <class Key, class Data, class Cost, GraphType GT>
typename Graph<Key, Data, Cost, GT>::reverse_iterator Graph<Key, Data, Cost, GT>::rend() noexcept {
	return nodes_.rend();
}

template <class Key, class Data, class Cost, GraphType GT>
typename Graph<Key, Data, Cost, GT>::const_reverse_iterator Graph<Key, Data, Cost, GT>::crbegin() const noexcept {
	return nodes_.crbegin();
}

template <class Key, class Data, class Cost, GraphType GT>
typename Graph<Key, Data, Cost, GT>::const_reverse_iterator Graph<Key, Data, Cost, GT>::crend() const noexcept {
	return nodes_.crend();
}
