#include <map>
#include <iostream>
#include <vector>

int main()
{
    std::map<std::string, std::vector<std::string>> adjList;

    adjList["B"].push_back("A");
    adjList["A"].push_back("B");

    adjList["A"].push_back("C");
    adjList["C"].push_back("A");

    //auto pair = adjList["A"];
    //std::cout << adjList.size();

    std::vector<std::string> newEdges = {};
    for(int x = 0; x < adjList["B"].size(); x++){
        if(adjList["B"][x] != "A"){
            newEdges.push_back(adjList["B"][x]);
        }
    }
    adjList["B"] = newEdges;

    for(auto node : adjList){
        if(node.second.size() == 0)
            std::cout << "erase" << std::endl;
    }

    std::cout << adjList["D"].size() << std::endl;
    

    for (auto pair : adjList) {
        std::cout << pair.first << " is connected to: ";
        for (auto neighbor : pair.second) {
            std::cout << neighbor << " ";
        }
        std::cout << "\n";
    }



}