#ifndef GRAPH_NODE_H_
#define GRAPH_NODE_H_

#include <memory>		// std::shared_ptr, std::weak_ptr
#include <list>			
#include <utility>		// std::size_t
#include <cassert>

template <class Data, class Key, class Cost = std::size_t>
class Node {

	private:
	class edge {
		private:
			// node connected to current
			std::weak_ptr<Node> nodeTo_;
			std::shared_ptr<Cost> cost_;

		public:
			explicit edge(const std::weak_ptr<Node> &ptr, Cost &c) : nodeTo_(ptr), cost_(std::make_shared<Cost>(c)) {}
			edge(const edge& other) : nodeTo_(other.nodeTo_), cost_(other.cost) {}

			Cost& cost() const { return *cost_; }
			std::shared_ptr<Cost> costPtr() const { return cost_; }
			std::weak_ptr<Node> getNodeTo() const { return nodeTo_; }

		friend class Node<Data, Key, Cost>;
	};

	// list of edges connected to this node
	std::list<edge> listEdges_;
	// data in the node
	Data data_;
	// key to reference this node in the graph
	Key key_;

	public:
		explicit Node() {}
		Node(const Data &data) : data_(data) {}
		Node(Data&& data) : data_(std::move(data)) {}
		Node(const Node& node) : data_(node.data_) {}
		Node(Node&& other) : data_(std::move(other.data_)) {}

		Data& getData() { return data_; }
		Data& getData() const { return data_; }

		using ListEdges = std::list<edge>;
		using ListEdgesIterator = typename ListEdges::iterator;
		using iterator = ListEdgesIterator;
		using const_iterator = typename ListEdges::const_iterator;

		// returns iterator to edge in list or _listEdge.end()
		ListEdgesIterator findEdge(std::shared_ptr<Node> toPtr) {
			assert(toPtr != nullptr);

			for(ListEdgesIterator it = listEdges_.begin(); it != listEdges_.end(); ++it){
				if(it->nodeTo_.lock() == toPtr){
					return it;
				}
			}
			return listEdges_.end();
		}

		bool isEdge(std::shared_ptr<Node> toPtr){
			return findEdge(toPtr) != listEdges_.end();
		}

		std::pair<ListEdgesIterator, bool> add_edge(std::shared_ptr<Node> toPtr, Cost& cost) {
			assert(toPtr != nullptr);

			ListEdgesIterator it = findEdge(toPtr);
			if(it != listEdges_.end()){
				it->cost() = cost;
				return std::make_pair(it, false);
			}

			listEdges_.emplace_back(std::weak_ptr<Node>(toPtr), cost);
			return std::make_pair(--listEdges_.end(), true);
		}

		void removeEdge(std::shared_ptr<Node> toPtr){
			assert(toPtr != nullptr);

			auto myPred = [&toPtr](edge& e) { 
				if(auto adj = e.getNodeTo().lock()){
					if(adj->getKeyInGraph() == toPtr->getKeyInGraph())
						return true;
					return false;
				}
				return true;
			};

			listEdges_.remove_if(myPred);

		}

		Cost& getEdgeCost(std::shared_ptr<Node> toPtr){
			assert(isEdge(toPtr) == true);
			return findEdge(toPtr)->cost();
		}

		void setKey(const Key &key) { key_ = key; }
		Key& getKeyInGraph() { return key_; }

		iterator begin() noexcept { return listEdges_.begin(); }
		iterator end() noexcept { return listEdges_.end(); }
		const_iterator begin() const noexcept { return listEdges_.begin(); }
		const_iterator end() const noexcept { return listEdges_.end(); }
		const_iterator cbegin() const noexcept { return listEdges_.cbegin(); }
		const_iterator cend() const noexcept { return listEdges_.cend(); }

}; // class Node

#endif