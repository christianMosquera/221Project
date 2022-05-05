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
    
    // have to add other stuff for the algorithms
    struct Vertex {
        size_t id;
        std::list<Vertex*> adjVertices;
        Vertex* path;
        double cost;
        bool known;

        Vertex () : id(), adjVertices(), path(nullptr), cost(0), known(false) {}
        Vertex (size_t id) : id(id), adjVertices(), path(nullptr), cost(0), known(false) {}

    };

    std::unordered_map<size_t, Vertex*> vertices;
    std::unordered_map<size_t, std::unordered_map<size_t, double>> edges; // edges[][] edges.at().at()
    

public:
    // Task 1
    Graph() : vertices(), edges() {}
    Graph(const Graph& other) : vertices(), edges() {

        // iteratate over vertices and deep copy
        for (auto i = other.vertices.begin(); i != other.vertices.end(); ++i)  {
            add_vertex(i->first);
        }
        
        // iteratate over edges and deep copy the edges map
        for (auto i = other.edges.begin(); i != other.edges.end(); ++i) {
            auto second = i->second.begin();
            add_edge(i->first, second->first, other.edges.at(i->first).at(second->first));
        }

    }
    Graph& operator=(const Graph& other) {
        
        if (&other == this) {
            return *this;
        }

        // make deep copy
        // iteratate over vertices and deep copy
        for (auto i = other.vertices.begin(); i != other.vertices.end(); ++i)  {
            add_vertex(i->first);
        }
        
        // iteratate over edges and deep copy the edges map
        for (auto i = other.edges.begin(); i != other.edges.end(); ++i) {
            auto second = i->second.begin();
            add_edge(i->first, second->first, other.edges.at(i->first).at(second->first));
        }

        return *this;

    }

    ~Graph() {}

    size_t vertex_count() const { return vertices.size(); }
    size_t edge_count() const {

        // return value
        size_t numEdges = 0;

        // iteratate over map and count up all edges
        for (auto i = edges.begin(); i != edges.end(); ++i) {
            numEdges += i->second.size();
        }

        return numEdges;

    }

    bool contains_vertex(size_t id) const { return vertices.find(id) != vertices.end(); }
    bool contains_edge(size_t src, size_t dest) const {
        try {
            edges.at(src).at(dest);
            
        }
        catch(std::out_of_range& e) {
            return false;
        }
        return true;
    }
    double cost(size_t src, size_t dest) const { return edges.at(src).at(dest); } // access edges through src and dest and return value // fix

    bool add_vertex(size_t id) {

        // if it already exists return false
        if (vertices.find(id) != vertices.end()) {
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

        if (contains_edge(src, dest)) {
            return false;
        }

        // updating edge map
        edges[src][dest] = weight;

        // updating vertices map
        vertices.at(src)->adjVertices.push_back(vertices.at(dest));

        return true;

    }
    bool remove_vertex(size_t id) {

        if (vertices.find(id) == vertices.end()) {
            return false;
        }
        // remove from edges first
        

        // remove from vertices and delete object

        return true;

    }
    bool remove_edge(size_t src, size_t dest) {

        // make sure both exist
        if (vertices.find(src) == vertices.end() || vertices.find(dest) == vertices.end()) {
            return false;
        }

        // remove only edge
        //auto map = edges.find(src);

        // remove from the src's list
        //vertices.at(src)->adjVertices.remove
        

        return true;

    }

    // Task 2
    void prim(size_t source_id) {}
    bool is_path(size_t id) const {}
    void print_path(size_t dest_id, std::ostream& os=std::cout) const {}

    // Task 3
    void dijkstra(size_t source_id) {

        // if vertex does not exist
        if (!contains_vertex(source_id)) {
            return;
        }

        Vertex* cheapest;
        Vertex* current = vertices.at(source_id);
        std::unordered_set<size_t> available;

        // set all costs to infinity
        for (auto i = vertices.begin(); i != vertices.end(); i++) {
            i->second->cost = INFINITY;
        }

        // set source cost to 0
        current->cost = 0;

        // encapsulate in another loop
        for (auto i = vertices.begin(); i != vertices.end(); i++) {
            if (!current) {
                break;
            }
            cheapest = nullptr;
            current->known = true;

            // loop over the current vertex adjacency list
            for (Vertex* v : current->adjVertices) {

                // add all edges to available set
                available.insert(v->id);

                // checks
                if (v->known == true) {
                    continue;
                }

                if (current->cost + edges.at(current->id).at(v->id) < v->cost) {
                    
                    // replaces the cost with the lower number
                    v->cost = current->cost + edges.at(current->id).at(v->id);
                    
                    // updates the path
                    v->path = current;

                }

            }

            // find cheapest vertex for next iteration
            for (auto j = available.begin(); j != available.end(); j++) {
                
                if (cheapest == nullptr && vertices.at(*j)->known == true) {
                    continue;
                }
                // find cheapest vertex
                else if (cheapest == nullptr && vertices.at(*j)->known == false) {
                    cheapest = vertices.at(*j);
                }
                else if (vertices.at(*j)->cost < cheapest->cost && vertices.at(*j)->known == false) {
                    cheapest = vertices.at(*j);
                }

            }

            current = cheapest;
            
        }

    }

    double distance(size_t id) const {
        if (!contains_vertex(id)) {
            return INFINITY;
        } 
        return vertices.at(id)->cost; 
    }
    void print_shortest_path(size_t dest_id, std::ostream& os=std::cout) const {
        if (!contains_vertex(dest_id)) {
            return;
        }
        if (vertices.at(dest_id)->known == false) {
            os << "<no path>" << std::endl;
            return;
        }
        print_shortest_path_recursive(dest_id, os);
        os << " distance: " << distance(dest_id) << std::endl;
    }

    void print_shortest_path_recursive(size_t id, std::ostream& os=std::cout) const {
        
        Vertex* vertex = vertices.at(id);
    
        if (vertex->path == nullptr) {
            os << vertex->id;
        }

        else {
            print_shortest_path_recursive(vertex->path->id, os);
            os << " --> " << vertex->id;
        }

        

    }
};

#endif  // GRAPH_H
