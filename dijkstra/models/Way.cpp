#pragma once

#include <vector>

#include "./Node/Node.h"

struct Way
{
    std::vector<Node *> nodes;
    int length;
    Way() : length(-1) {}
};