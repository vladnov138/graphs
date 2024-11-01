#pragma once

#include <vector>

#include "./MarkedNode.cpp"

struct Way
{
    std::vector<MarkedNode> nodes;
    int length;
    Way() : length(-1) {}
};
