#ifndef GRAPH_GRAPH_H_
#define GRAPH_GRAPH_H_

#include <utility>          // std::size_t, std::pair
#include <limits>           // std::numeric_limits<T>
#include <map>              // std::map
#include <queue>            // std::queue, std::priority_queue
#include <functional>       // std::greater<T>


#include "Node.h"

enum GraphType {
    undirected,
    directed
};


/*
    Key = key to reference the nodeValue
    Data = data stored in node
    Cost = cost type of edges (default std::size_t)
    GraphType = enumerate of graph
*/
template <class Key, class Data, class Cost = std::size_t, GraphType GT = undirected>
class Graph {
private:
    // --- Definitions ---
    using node = typename Node<Data, Key, Cost>::Node;
    using NodeSharedPtr = std::shared_ptr<node>;
    using MapNodes = std::map<Key, NodeSharedPtr>;

    // struct holding data for algorithms
    struct visitData {
        Cost d = 0; 
        std::size_t f = 0;
        std::weak_ptr<node> p;
        enum color {
            white, gray, black
        } color = white;
    };

    // --- Member data ---
    MapNodes nodes_;
    Cost maxCost_;

    GraphType getGraphType() const { return GT; }

public:
    // --- iterators ---
    using iterator = typename MapNodes::iterator;
    using const_iterator = typename MapNodes::const_iterator;
    using reverse_iterator = typename MapNodes::reverse_iterator;
    using const_reverse_iterator = typename MapNodes::const_reverse_iterator;


    // --- Graph ---

    explicit Graph();
    // cpy ctor
    Graph(const Graph &other);
    // move ctor
    Graph(Graph &&other);
    ~Graph();

    // merge nodes and edges of other with *this
    // preserves nodes and edges in *this if nodes or links are alrady present
    // returns new size of *this
    std::size_t mergeGraph(const Graph<Key, Data, Cost, GT>& other);


    // --- Capacity ---

    inline bool empty() const noexcept { return nodes_.empty(); }
    inline std::size_t size() const noexcept { return nodes_.size(); }


    // --- Node functions ---

    // return data of node by key
    Data &operator[](const Key &key);
    Data &operator[](Key &&key);

    // find node in graph by key
    iterator find(const Key &key);
    const_iterator find(const Key &key) const;
    bool contains(const Key &key) const { return find(key) != (*this).cend(); }

    // emplace key node in graph
    std::pair<iterator, bool> emplace(const Key &key);
    std::pair<iterator, bool> emplace(Key &&key);
    std::pair<iterator, bool> emplace(const Key &key, const node &node);
    std::pair<iterator, bool> emplace(Key &&key, node &&node);

    // erase node in graph
    std::size_t erase(const Key &key);
    std::size_t erase(Key &&key);
    iterator erase(iterator pos);


    // --- Edge functions ---

    // get cost of edge in graph, if no edge in graph creates it
    Cost &operator()(const Key &key1, const Key &key2);
    Cost &operator()(Key &&key1, Key &&key2);
    Cost &operator()(iterator n1, iterator n2);
    const Cost &operator()(const Key &key1, const Key &key2, const Cost &cost);
    // have to manage the () operator with the undirected graph 
    // maybe return std::pair<Cost, bool> ????
    // to fix return value
    bool removeEdge(const Key &key1, const Key &key2);
    bool removeEdge(const_iterator it1, const_iterator it2);


    // check if to nodes are connected by an edge
    bool isConnectedTo(const Key &key1, const Key &key2) const;
    bool isConnectedTo(Key &&key1, Key &&key2) const;
    bool isConnectedTo(const_iterator itNode1, const_iterator itNode2) const;


    // --- Algorithms functions ---

    // run bfs on start node returns data of visited nodes
    std::map<Key, visitData> bfs(const Key &start) const;
    std::map<Key, visitData> bfs(const iterator start) const;

    // run dfs on start node returns data on visited nodes
    std::map<Key, visitData> dfs(const Key &start) const;
    std::map<Key, visitData> dfs(const const_iterator start) const;
    void dfsVisit(std::map<Key, visitData>& visitedNodes, const const_iterator node, std::size_t& time) const;

    // coputes all the floydWarshall matrices
    std::vector<Cost> computeFloydWarshall();
    // returns a 1 dimensional array rapresenting 
    // the last matrix of floydWarhall algorithm
    std::vector<Cost> floydWarshall();

    // run dikjstra algorithm on start node return data on visited nodes
    std::map<Key, visitData> dijkstra(const Key &start) const;
    std::map<Key, visitData> dijkstra(const const_iterator start) const;

    // =====> working on...
    Graph<Key, Data, Cost, GT> prim(const Key &root) const;
    Graph<Key, Data, Cost, GT> prim(const const_iterator root) const;

    // =====> kruskal
    // =====> connected components

    Graph<Key, Data, Cost, GT> getConnectedComponents() const;

    // --- Iterators functinos ---

    iterator begin() noexcept;
    iterator end() noexcept;

    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    reverse_iterator rbegin() noexcept;
    reverse_iterator rend() noexcept;

    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator rend() const noexcept;

    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;
};


// --- Graphs definitions ---
template <class Key, class Data, class Cost = std::size_t>
using DirectedGraph = Graph<Key, Data, Cost, directed>;

template <class Key, class Data, class Cost = std::size_t>
using UndirectedGraph = Graph<Key, Data, Cost, undirected>;

#include "Graph.cpp"

#endif