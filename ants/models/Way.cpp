#pragma once

#include <vector>

#include "./Node/Node.h"

struct Way
{
    std::vector<Node> nodes;
    int length;
    double probability;
    double pheramones;
    Way() : length(0) {}
};

// bool operator == (const Way& lhs, const Way& rhs) {
//     return lhs.nodes == rhs.nodes &&
//            lhs.length == rhs.length &&
//            lhs.probability == rhs.probability &&
//            lhs.pheramones == rhs.pheramones;
// }
