#ifndef GRAPH_Graph_H
#define GRAPH_Graph_H

#include <map>
#include <utility>
#include <limits>

#include "Node.h"


enum GraphType {
    undirected, 
    directed
};


/*
    Key = key to reference the nodeValue
    Data = data stored in node 
    Cost = cost type of edges
    GraphType = enumerate of graph 
    
*/
template <class Key, class Data, class Cost = std::size_t, GraphType GT = undirected>
class Graph {
    
    private:

        using node = typename Node<Data, Cost>::Node;
        using NodeSharedPtr = std::shared_ptr<Node<Data, Cost>>;
        using MapNodes = std::map<Key, NodeSharedPtr>;

        MapNodes _nodes;
        Cost _maxCost;

    public:
        
        explicit Graph();
        // cpy ctor
        explicit Graph(const Graph& other);
        // move ctor
        explicit Graph(Graph&& other);

        ~Graph();

        // iterators
        using iterator = typename MapNodes::iterator;
        using const_iterator = typename MapNodes::const_iterator;
        using reverse_iterator = typename MapNodes::reverse_iterator;
        using const_reverse_iterator = typename MapNodes::const_reverse_iterator;


        // Node functinos

        Data& operator[](const Key& key);
        Data& operator[](Key&& key);

        iterator find(const Key& key);
        const_iterator find(const Key& key) const;

        std::pair<iterator, bool> emplace(const Key& key);
        std::pair<iterator, bool> emplace(const Key&& key);
        std::pair<iterator, bool> emplace(const Key& key, const node& node);
        std::pair<iterator, bool> emplace(const Key&& key, const node&& node);


        // Edge functions

        Cost& operator()(const Key& key1, const Key& key2);
        Cost& operator()(Key&& key1, Key&& key2);
        Cost& operator()(iterator n1, iterator n2);
        const Cost& operator()(const Key& key1, const Key& key2, const Cost& cost);

        bool isConnectedTo(iterator itNode1, iterator itNode2);


        // Iterators functinos

        iterator begin() noexcept;
        iterator end() noexcept;

        const_iterator begin() const noexcept;
        const_iterator end() const noexcept;

        const_iterator cbegin() const noexcept;
        const_iterator cend() const noexcept;

        reverse_iterator rbegin() noexcept;
        reverse_iterator rend() noexcept;

        const_reverse_iterator rbegin()  const noexcept;
        const_reverse_iterator rend()  const noexcept;

        const_reverse_iterator crbegin() const noexcept;
        const_reverse_iterator crend() const noexcept;

};

// definition of graphs
template<class Key, class Data, class Cost>
using DirectedGraph = Graph<Key, Data, Cost, directed>;

template<class Key, class Data, class Cost>
using UndirectedGraph = Graph<Key, Data, Cost, undirected>;

#include "Graph.cpp"

#endif