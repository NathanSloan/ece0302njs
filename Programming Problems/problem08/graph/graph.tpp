#include "graph.hpp"

template <typename LabelType>
Graph<LabelType>::Graph() {
    numEdges = 0;
}

template <typename LabelType> 
int Graph<LabelType>::getNumVertices() const {
    return adjList.size();
}

template <typename LabelType> 
int Graph<LabelType>::getNumEdges() const {
    return numEdges;
}
        
template <typename LabelType> 
bool Graph<LabelType>::add(LabelType start, LabelType end) {
    // check which nodes are new
    bool startNew = adjList.find(start) == adjList.end();
    bool endNew = adjList.find(end) == adjList.end();

    // if both nodes are new, do not add (unless first nodes)
    if(startNew && endNew && numEdges != 0){
        // edge is added later if these are the first two nodes
        return false;
    }
    // if both nodes are not new, make sure connection does not already exist
    else if(!startNew && !endNew){
        for(int x = 0; x < adjList[start].size(); x++){
            if(adjList[start][x] == end){
                return false;
            }
        }
    }

    // add new connections to map
    adjList[end].push_back(start);
    adjList[start].push_back(end);
    numEdges += 1;
    return true;
}   

template <typename LabelType> 
bool Graph<LabelType>::remove(LabelType start, LabelType end) {
    // check that the nodes exist
    bool startExist = adjList.find(start) != adjList.end();
    bool endExist = adjList.find(end) != adjList.end();

    // return false if either node does not exist
    if(!startExist || !endExist)
        return false;
    
    // get new connection list for start excluding end node
    std::vector<LabelType> newEdges = {};
    for(int x = 0; x < adjList[start].size(); x++){
        if(adjList[start][x] != end){
            newEdges.push_back(adjList[start][x]);
        }
    }
    
    // return false if lists match (no connection between nodes)
    if(adjList[start] == newEdges)
        return false;
    adjList[start] = newEdges;

    // get new connection list for end excluding start node
    newEdges = {};
    for(int x = 0; x < adjList[end].size(); x++){
        if(adjList[end][x] != start){
            newEdges.push_back(adjList[end][x]);
        }
    }
    adjList[end] = newEdges;

    // remove edge
    numEdges -= 1;

    // remove any node left with no edges connecting it
    std::vector<LabelType> removals = {};
    for(auto node : adjList){
        if(node.second.size() == 0){
            removals.push_back(node.first);
        }
    }
    for(auto val : removals)
        adjList.erase(val);
    
    return true;
}

template <typename LabelType> 
void Graph<LabelType>::depthFirstTraversal(LabelType start, void visit(LabelType&)) {}

template <typename LabelType> 
void Graph<LabelType>::breadthFirstTraversal(LabelType start, void visit(LabelType&)) {}