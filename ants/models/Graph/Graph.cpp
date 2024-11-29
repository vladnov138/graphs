#include "Graph.h"
#include "../BFS/BFS.h"
#include "../../exceptions/FileNotOpenException.h"
#include "../../exceptions/GraphException.h"

Graph::Graph(const Graph *graph)
{
    nodes = (*graph).nodes;
}

Graph::Graph(const std::string filename, bool isDirectional)
{
    this->isDirectional = isDirectional;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw FileNotOpenException();
    }
    // file.ignore(100, '\n');
    Node *temp_nodes[1000] = {};
    std::string line;
    while (getline(file, line))
    {
        std::regex rgx(R"(\d+)");
        std::string str_source = "";
        std::string str_target = "";
        std::string str_weight = "";
        for (std::sregex_token_iterator it{line.begin(), line.end(), rgx, 0}, end; it != end;)
        {
            str_source = *it++;
            str_target = *it++;
            str_weight = *it++;
        }
        if (temp_nodes[std::stoi(str_source)] == 0)
        {
            temp_nodes[std::stoi(str_source)] = new Node(str_source);
            addNode(temp_nodes[std::stoi(str_source)]);
        }
        if (temp_nodes[std::stoi(str_target)] == 0)
        {
            temp_nodes[std::stoi(str_target)] = new Node(str_target);
            addNode(temp_nodes[std::stoi(str_target)]);
        }
        addEdge(temp_nodes[std::stoi(str_source)], temp_nodes[std::stoi(str_target)], std::stoi(str_weight));
    }
}

void Graph::removeNode(Node *node)
{
    nodes.erase(node);
    for (std::set<Node *>::iterator it = nodes.begin(); it != nodes.end(); it++)
    {
        (*it)->removeNeighbour(node);
    }
}

void Graph::addNode(Node *node)
{
    if (nodes.find(node) != nodes.end() || !node)
    {
        return;
    }
    nodes.insert(node);
}

void Graph::removeEdge(Node *begin, Node *end)
{
    if (nodes.find(begin) == nodes.end() || nodes.find(end) == nodes.end())
    {
        throw GraphException();
    }
    begin->removeNeighbour(end);
    end->removeNeighbour(begin);
}

void Graph::addEdge(Node *begin, Node *end, int weight)
{
    if (nodes.find(begin) == nodes.end() || nodes.find(end) == nodes.end())
    {
        throw GraphException();
    }
    if (begin != end) {
        begin->addNeighbour(end, weight);
        if (!isDirectional) {
            end->addNeighbour(begin, weight);
        }
    }
}

void Graph::splitGraph()
{
    BFS bfs(*this);
    std::ofstream file;
    std::set<Node *> visited_nodes;
    int c = 1;
    while (visited_nodes.size() < nodes.size())
    {
        file.open("outgraph" + std::to_string(c++) + ".txt");
        if (!file.is_open())
        {
            throw FileNotOpenException();
        }
        file << "Source Target\n";
        for (std::set<Node *>::iterator it = nodes.begin(), last_it = nodes.end(); it != nodes.end(); it++)
        {
            if (visited_nodes.find(*it) == visited_nodes.end() && (last_it == nodes.end() || bfs.connected(*it, *last_it)))
            {
                for (node_iterator nb_it = (*it)->nb_begin(); nb_it != (*it)->nb_end(); nb_it++) {
                    if (visited_nodes.find(*nb_it) == visited_nodes.end()) {
                        file << (*it)->getName() << " " << (*nb_it)->getName() << std::endl;
                    }
                }
                visited_nodes.insert(*it);
                last_it = it;
            }
        }
    }
}

const std::set<Node*> Graph::getNodes() const {
    return nodes;
}
