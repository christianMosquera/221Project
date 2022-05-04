#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <iostream>
#include <queue>


class Graph {
private:
    // TODO(student): implement graph
    
    struct Vertex {
        size_t id;
        std::list<Vertex*> adjVertices;
        Vertex () : id(), adjVertices() {}
        Vertex (size_t id) : id(id), adjVertices() {}
    };

    std::unordered_map<size_t, Vertex*> vertices;
    std::unordered_map<size_t, std::unordered_map<size_t, double>> edges; // edges[][] edges.at().at()
    

public:
    // Task 1
    Graph() : vertices(), edges() {}
    Graph(const Graph& other) {}
    Graph& operator=(const Graph& other) {
        if (&other == this) {
            return *this;
        }

        // make deep copy
    }

    ~Graph() {}

    size_t vertex_count() const { return vertices.size(); }
    size_t edge_count() const { return edges.size(); }

    bool contains_vertex(size_t id) const { return vertices.find(id) != vertices.end(); }
    bool contains_edge(size_t src, size_t dest) const {}
    double cost(size_t src, size_t dest) const { return edges.at(src).at(dest); } // access edges through src and dest and return value

    bool add_vertex(size_t id) {

        // if it already exists return false
        if (vertices.find(id) == vertices.end()) {
            return false;
        }

        // insert using id and allocate a new Vertex
        vertices.insert({id, new Vertex(id)});

        return true;

    }

    bool add_edge(size_t src, size_t dest, double weight=1) {

        // make sure both exist
        if (vertices.find(src) == vertices.end() || vertices.find(dest) == vertices.end()) {
            return false;
        }

        // updating edge map
        edges[src][dest] = weight;

        // updating vertices map
        vertices.at(src)->adjVertices.push_back(vertices.at(dest));

        return true;

    }
    bool remove_vertex(size_t id);
    bool remove_edge(size_t src, size_t dest);

    // Task 2
    void prim(size_t source_id);
    bool is_path(size_t id) const;
    void print_path(size_t dest_id, std::ostream& os=std::cout) const;

    // Task 3
    void dijkstra(size_t source_id);
    double distance(size_t id) const;
    void print_shortest_path(size_t dest_id, std::ostream& os=std::cout) const;
};

#endif  // GRAPH_H
