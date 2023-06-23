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
std::size_t Graph<Key, Data, Cost, GT>::mergeGraph(const Graph<Key, Data, Cost, GT>& other){

	if((*this).getGraphType() != other.getGraphType())
		return nodes_.size();

	// merging nodes of other in this
	for(const_iterator it = other.cbegin(); it != other.cend(); ++it){
		(*this).emplace(it->first, *it->second);
	}

	for(const_iterator it = other.cbegin(); it != other.cend(); ++it){
		for(typename node::const_iterator link = it->second->cbegin(); link != it->second->cend(); ++link){
			// add edges in node
			if(auto adjNode = link->getNodeTo().lock()){
				// check if edge is not present in *this alrady
				if(!(*this).find(it->first)->second->isEdge((*this).find(adjNode->getKeyInGraph())->second))
					(*this)(it->second->getKeyInGraph(), adjNode->getKeyInGraph()) = link->cost();	
			}
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
	std::pair<iterator, bool> pair{nodes_.emplace(key, std::make_shared<node>(n))};
	pair.first->second->setKey(key);
	return pair;
}

template <class Key, class Data, class Cost, GraphType GT>
std::pair<typename Graph<Key, Data, Cost, GT>::iterator, bool> Graph<Key, Data, Cost, GT>::emplace(Key &&key, node &&n) {
	// std::cout << "moved" << std::endl;
	std::pair<iterator, bool> pair{nodes_.emplace(std::move(key), std::move(std::make_shared<node>(n)))};
	pair.first->second->setKey(key);
	return pair;
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
		// if graph is directed creates the reverse edge as well
		if(getGraphType() == directed){
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

// Algorithms

template <class Key, class Data, class Cost, GraphType GT>
std::map<Key, typename Graph<Key, Data, Cost, GT>::visitData> Graph<Key, Data, Cost, GT>::bfs(const Key &start) const {
	iterator startIt{find(start)};
	return bfs(startIt);
}

template <class Key, class Data, class Cost, GraphType GT>
std::map<Key, typename Graph<Key, Data, Cost, GT>::visitData> Graph<Key, Data, Cost, GT>::bfs(const iterator start) const {

	// map holding data on visitedNodes 
	std::map<Key, visitData> visitedNodes;

	// set visitData of starting node 
	visitedNodes[start->first].p.reset();
	visitedNodes[start->first].color = visitData::color::gray;

	// queue holding nodes to visit
	std::queue<NodeSharedPtr> queue;
	queue.push(start->second);

	while(!queue.empty()){
		NodeSharedPtr u = queue.front();
		queue.pop();
		for(typename node::iterator edge = u->begin(); edge != u->end(); ++edge){
			if(auto adj = edge->getNodeTo().lock()){
				// if adj color is white (not visited)
				if(visitedNodes.find(adj->getKeyInGraph()) == visitedNodes.end()){
					visitedNodes[adj->getKeyInGraph()].color = visitData::color::gray;
					visitedNodes[adj->getKeyInGraph()].d = visitedNodes[u->getKeyInGraph()].d + 1;
					visitedNodes[adj->getKeyInGraph()].p = u;
					queue.push(adj);
				}
			}
		}
		visitedNodes[u->getKeyInGraph()].color = visitData::black;
	}

	return visitedNodes;
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
