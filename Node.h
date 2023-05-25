#ifndef GRAPH_NODE_H_
#define GRAPH_NODE_H_

#include <memory>
#include <list>
#include <cassert>
#include <utility>

template <class Data, class Cost = std::size_t>
class Node {

	class edge {
		private:
			// node connected to current
			std::weak_ptr<Node> nodeTo_;
			std::shared_ptr<Cost> cost_;

		public:
			explicit edge(const std::weak_ptr<Node> &ptr, Cost &c);
			edge(const edge& other);

			Cost& cost() const;
			std::shared_ptr<Cost> costPtr() const;

		friend class Node<Data, Cost>;
	};

	private:
		std::list<edge> listEdges_;
		Data data_;


	public:
		explicit Node();
		Node(const Data &data);
		Node(Data&& data);
		Node(const Node& node);
		Node(Node&& other);

		Data& getData();
		Data& getData() const;

		using ListEdges = std::list<edge>;
		using ListEdgesIterator = typename ListEdges::iterator;

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

		Cost& getEdgeCost(std::shared_ptr<Node> toPtr){
			assert(isEdge(toPtr) == true);
			return findEdge(toPtr)->cost();
		}

};

#include "Node.cpp"

#endif