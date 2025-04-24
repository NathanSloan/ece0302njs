#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "abstract_graph.hpp"
#include <map>
#include <vector>

template <typename LabelType>
class Graph: public AbstractGraph<LabelType>
{
    public:

        Graph();

        int getNumVertices() const;
        
        int getNumEdges() const;

        bool add(LabelType start, LabelType end);

        bool remove(LabelType start, LabelType end);

        void depthFirstTraversal(LabelType start, void visit(LabelType&));

        void breadthFirstTraversal(LabelType start, void visit(LabelType&));
    
    private:
        std::map<LabelType, std::vector<LabelType>> adjList;
        int numEdges;
};

#include "graph.tpp"

#endif 
