#include "Graph.h"
#include <iostream>

template<class Key, class Data, class Cost, GraphType GT>
Graph<Key, Data, Cost, GT>::Graph() {
	_nodes.clear();
	if(std::numeric_limits<Cost>::is_specialized){
		_maxCost = std::numeric_limits<Cost>::max();
	}
}

template<class Key, class Data, class Cost, GraphType GT>
Graph<Key, Data, Cost, GT>::Graph(const Graph& other) : _nodes(other._nodes), _maxCost(other._maxCost) {}

template<class Key, class Data, class Cost, GraphType GT>
Graph<Key, Data, Cost, GT>::~Graph() {
	_nodes.clear();
}

template<class Key, class Data, class Cost, GraphType GT>
Data& Graph<Key, Data, Cost, GT>::operator[](const Key& key) {
	return emplace(key).first->second->getData();
}

template<class Key, class Data, class Cost, GraphType GT>
Data& Graph<Key, Data, Cost, GT>::operator[](Key&& key) {
	return emplace(std::move(key), std::move(node())).first->second->getData();
}

template<class Key, class Data, class Cost, GraphType GT>
std::pair<typename Graph<Key, Data, Cost, GT>::iterator, bool> Graph<Key, Data, Cost, GT>::emplace(const Key& key){
	return emplace(key, node());
}

template<class Key, class Data, class Cost, GraphType GT>
std::pair<typename Graph<Key, Data, Cost, GT>::iterator, bool> Graph<Key, Data, Cost, GT>::emplace(const Key&& key){
	return emplace(std::move(key), std::move(node()));
}

template<class Key, class Data, class Cost, GraphType GT>
std::pair<typename Graph<Key, Data, Cost, GT>::iterator, bool> Graph<Key, Data, Cost, GT>::emplace(const Key& key, const node& n){
	return _nodes.emplace(key, std::make_shared<node>(n));
}

template<class Key, class Data, class Cost, GraphType GT>
std::pair<typename Graph<Key, Data, Cost, GT>::iterator, bool> Graph<Key, Data, Cost, GT>::emplace(const Key&& key, const node&& n){
	return _nodes.emplace(std::move(key), std::move(std::make_shared<node>(n)));
}

template<class Key, class Data, class Cost, GraphType GT>
typename Graph<Key, Data, Cost, GT>::iterator Graph<Key, Data, Cost, GT>::find(const Key& key) {
	return _nodes.find(key);
}

template<class Key, class Data, class Cost, GraphType GT>
typename Graph<Key, Data, Cost, GT>::const_iterator Graph<Key, Data, Cost, GT>::find(const Key& key) const {
	return _nodes.find(key);
}

template<class Key, class Data, class Cost, GraphType GT>
Cost& Graph<Key, Data, Cost, GT>::operator()(iterator itNode1, iterator itNode2) {
	if(isConnectedTo(itNode1, itNode2)){
		return itNode1->second->getEdgeCost(itNode2->second);
	}else{
		return (itNode1->second->add_edge(itNode2->second, _maxCost)).first->cost();
	}
}

template<class Key, class Data, class Cost, GraphType GT>
Cost& Graph<Key, Data, Cost, GT>::operator()(const Key& key1, const Key& key2) {
	iterator itNode1{emplace(key1).first};
	iterator itNode2{emplace(key2).first};
	return operator()(itNode1, itNode2);
}

template<class Key, class Data, class Cost, GraphType GT>
Cost& Graph<Key, Data, Cost, GT>::operator()(Key&& key1, Key&& key2) {
	iterator itNode1{emplace(std::move(key1)).first};
	iterator itNode2{emplace(std::move(key2)).first};
	return operator()(itNode1, itNode2);
}

template<class Key, class Data, class Cost, GraphType GT>
const Cost& Graph<Key, Data, Cost, GT>::operator()(const Key& key1, const Key& key2, const Cost& cost) {
	iterator itNode1{emplace(key1).first};
	iterator itNode2{emplace(key2).first};
	
	operator()(itNode1, itNode2) = cost;
	operator()(itNode2, itNode1) = cost;
	return cost;
}

template<class Key, class Data, class Cost, GraphType GT>
bool Graph<Key, Data, Cost, GT>::isConnectedTo(iterator itNode1, iterator itNode2) {
	return itNode1->second->isEdge(itNode2->second);
}



template<class Key, class Data, class Cost, GraphType GT>
typename Graph<Key, Data, Cost, GT>::iterator Graph<Key, Data, Cost, GT>::begin() noexcept {
	return _nodes.begin();
}

template<class Key, class Data, class Cost, GraphType GT>
typename Graph<Key, Data, Cost, GT>::iterator Graph<Key, Data, Cost, GT>::end() noexcept {
	return _nodes.end();
}

template<class Key, class Data, class Cost, GraphType GT>
typename Graph<Key, Data, Cost, GT>::const_iterator Graph<Key, Data, Cost, GT>::begin() const noexcept {
	return _nodes.begin();
}

template<class Key, class Data, class Cost, GraphType GT>
typename Graph<Key, Data, Cost, GT>::const_iterator Graph<Key, Data, Cost, GT>::end() const noexcept {
	return _nodes.end();
}

template<class Key, class Data, class Cost, GraphType GT>
typename Graph<Key, Data, Cost, GT>::const_iterator Graph<Key, Data, Cost, GT>::cbegin() const noexcept {
	return _nodes.cbegin();
}

template<class Key, class Data, class Cost, GraphType GT>
typename Graph<Key, Data, Cost, GT>::const_iterator Graph<Key, Data, Cost, GT>::cend() const noexcept {
	return _nodes.cend();
}

template<class Key, class Data, class Cost, GraphType GT>
typename Graph<Key, Data, Cost, GT>::reverse_iterator Graph<Key, Data, Cost, GT>::rbegin() noexcept {
	return _nodes.rbegin();
}

template<class Key, class Data, class Cost, GraphType GT>
typename Graph<Key, Data, Cost, GT>::reverse_iterator Graph<Key, Data, Cost, GT>::rend() noexcept {
	return _nodes.rend();
}

template<class Key, class Data, class Cost, GraphType GT>
typename Graph<Key, Data, Cost, GT>::const_reverse_iterator Graph<Key, Data, Cost, GT>::crbegin() const noexcept {
	return _nodes.crbegin();
}

template<class Key, class Data, class Cost, GraphType GT>
typename Graph<Key, Data, Cost, GT>::const_reverse_iterator Graph<Key, Data, Cost, GT>::crend() const noexcept {
	return _nodes.crend();
}

