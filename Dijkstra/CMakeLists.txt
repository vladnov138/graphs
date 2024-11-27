cmake_minimum_required(VERSION 3.5)

project(Dijkstra LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Dijkstra main.cpp
    exceptions/FileNotOpenException.h  exceptions/GraphException.h  exceptions/NodeException.h  models/BFS/BFS.cpp models/BFS/BFS.h  models/Dijkstra/Dijkstra.cpp models/Dijkstra/Dijkstra.h models/Graph/Graph.cpp models/Graph/Graph.h models/Node/Node.cpp models/Node/Node.h  models/PriorityQueue/PriorityQueue.cpp models/PriorityQueue/PriorityQueue.h  models/MarkedNode.cpp models/Way.cpp main.cpp)

include(GNUInstallDirs)
install(TARGETS Dijkstra
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
