#ifndef GRAPH_Node_H
#define GRAPH_Node_H

#include <memory>
#include <list>
#include <cassert>
#include <utility>

template <class Data, class Cost = std::size_t>
class Node {

	class edge {
		private:
			// node connected to current
			std::weak_ptr<Node> _nodeTo;
			std::shared_ptr<Cost> _cost;

		public:
			explicit edge(const std::weak_ptr<Node> &ptr, Cost &c);
			edge(const edge& other);

			Cost& cost() const;
			std::shared_ptr<Cost> costPtr() const;

		friend class Node<Data, Cost>;
	};

	private:
		std::list<edge> _listEdges;
		Data _data;


	public:
		explicit Node();
		explicit Node(const Data &data);
		Node(Data&& data);
		Node(const Node& node);
		Node(Node&& other);

		Data& getData();
		Data& getData() const;

		typedef std::list<edge> ListEdges;
		typedef typename ListEdges::iterator ListEdgesIterator;

		// returns iterator to edge in list or _listEdge.end()
		ListEdgesIterator findEdge(std::shared_ptr<Node> toPtr) {
			assert(toPtr != nullptr);

			for(ListEdgesIterator it = _listEdges.begin(); it != _listEdges.end(); ++it){
				if(it->_nodeTo.lock() == toPtr){
					return it;
				}
			}
			return _listEdges.end();
		}

		bool isEdge(std::shared_ptr<Node> toPtr){
			return findEdge(toPtr) != _listEdges.end();
		}

		std::pair<ListEdgesIterator, bool> add_edge(std::shared_ptr<Node> toPtr, Cost& cost) {
			assert(toPtr != nullptr);

			ListEdgesIterator it = findEdge(toPtr);
			if(it != _listEdges.end()){
				it->cost() = cost;
				return std::make_pair(it, false);
			}

			_listEdges.emplace_back(std::weak_ptr<Node>(toPtr), cost);
			return std::make_pair(--_listEdges.end(), true);
		}

		Cost& getEdgeCost(std::shared_ptr<Node> toPtr){
			assert(isEdge(toPtr) == true);
			return findEdge(toPtr)->cost();
		}

};

#include "Node.cpp"

#endif