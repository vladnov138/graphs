cmake_minimum_required(VERSION 3.16)

project(ants LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ants main.cpp
    data/1000.txt data/6.txt data/synthetic.txt exceptions/FileNotOpenException.h exceptions/GraphException.h exceptions/NodeException.h models/BFS/BFS.cpp models/BFS/BFS.h models/Graph/Graph.cpp models/Graph/Graph.h models/Node/Node.cpp models/Node/Node.h models/PriorityQueue/PriorityQueue.cpp models/PriorityQueue/PriorityQueue.h models/MarkedNode.cpp models/Way.cpp

    models/BFS/BFS.cpp models/BFS/BFS.h models/Graph/Graph.cpp models/Graph/Graph.h models/Node/Node.cpp models/Node/Node.h models/PriorityQueue/PriorityQueue.cpp models/PriorityQueue/PriorityQueue.h models/Ant.cpp models/Ant.h models/AntColonyAlgorithm.cpp models/AntColonyAlgorithm.h models/MarkedNode.cpp models/Way.cpp
    utils/utils.h utils/utils.cpp)

include(GNUInstallDirs)
install(TARGETS ants
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
