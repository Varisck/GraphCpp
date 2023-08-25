
# Graph C++ Library

- This library is a personal project developed to explore and familiarize with various features of C++ programming language.

- This Graph library is a C++ template library that provides an implementation of a graph data structure. It allows you to create and manipulate graphs with nodes and edges. This library supports both undirected and directed graphs.

## Features
- Templated implementation: The library is designed as a C++ template, allowing you to create graphs with custom key, data, and cost types.
- Node management: You can add, remove, and access nodes using their keys.
- Edge management: You can assign costs to edges between nodes, allowing you to represent weighted graphs.
- Graph types: The library supports both undirected and directed graphs through the GraphType enumeration.
- Iterator support: Iterators are provided to traverse the nodes in the graph.

## Installation
To use the Graph library in your C++ project, follow these steps:

1. Copy the Node.h, Node.cpp, Graph.h and Graph.cpp files into your project directory.
2. Include the library header file in your source code:

```cpp
#include "Graph.h"
```
That's it! You can now start using the Graph library in your project.

## Usage
### Creating a Graph
To create a graph, instantiate an object of the `Graph` class with the desired template parameters. For example, to create an undirected graph with `int` keys, `std::string` data, and `double` costs, you can do the following:

``` cpp
UndirectedGraph<int, std::string, double> graph;
```

### Adding and Accessing Nodes
To add nodes to the graph, use the the `operator[]` function or the `emplace` function, which takes a key and optionally a node object. If a node object is not provided, an empty node will be created. Here are some examples:

```cpp
graph[1];                                               // Add a node with key value 1 and default-constructed data
graph[2] = "Node 2"                                     // Add a node with key 2 and value "Node 2"
graph.emplace(3);                                       // Add a node with key 3 and default-constructed data
graph.emplace(4, Node<std::string, double>{"Node 4"});  // Add a node with key 4 and custom data
```

To access the data of a node, you can use the `operator[]` function, providing the key of the node:

```cpp
std::string& data = graph[2];  // Access the data of the node with key 2
```

### Manipulating Edges
You can assign costs to edges between nodes using the `operator()` function. The cost can be accessed and modified using this function as well. When creating an edge without assigning any value cost the default cost will be `std::numeric_limits<Cost>::max();` if `std::numeric_limits<Cost>::is_specialized`. Here are some examples:

```cpp
graph(1, 2);                    // Creating edge between 1 and 2 with max value of double
graph(1, 2) = 3.0;              // Assign a cost of 3.0 to the edge between nodes 1 and 2
double cost = graph(1, 2);      // Access the cost of the edge between nodes 1 and 2
graph(1, 2) += 1.5;             // Increase the cost of the edge between nodes 1 and 2 by 1.5 
```

### Iterating over Nodes
The Graph library provides various iterator types to traverse the nodes in the graph. You can use them as follows:

```cpp
for (auto it = graph.begin(); it != graph.end(); ++it) {
    // Access the key and data of the current node using (*it).first and (*it).second
}

for (const auto& node : graph) {
    // Access the key and data of the current node using node.first and node.second
}
```

### Graph Types
The library provides two predefined graph types: `DirectedGraph` and `UndirectedGraph`. These aliases allow you to create directed and undirected graphs more conveniently. For example:

```cpp
DirectedGraph<int, std::string, double> directedGraph;
UndirectedGraph<int, std::string, double> undirectedGraph;
```

## License
This library is distributed under the MIT License. See the LICENSE file for more information.

## Contributing
Contributions are welcome! If you find any issues or have suggestions for improvement, please open an issue or submit a pull request.

## Contact
If you have any questions or need further assistance, you can contact the library maintainer at `mail`.

Happy graphing!
