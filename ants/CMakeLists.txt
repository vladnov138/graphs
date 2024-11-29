cmake_minimum_required(VERSION 3.16)

project(ants LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(libs/matplotlibcpp.h)
find_package(Python3 REQUIRED COMPONENTS Interpreter Development NumPy)
include_directories(${Python3_NumPy_INCLUDE_DIRS})

add_executable(ants main.cpp
    data/synthetic.txt exceptions/FileNotOpenException.h exceptions/GraphException.h exceptions/NodeException.h models/BFS/BFS.cpp models/BFS/BFS.h models/Graph/Graph.cpp models/Graph/Graph.h models/Node/Node.cpp models/Node/Node.h models/PriorityQueue/PriorityQueue.cpp models/PriorityQueue/PriorityQueue.h models/MarkedNode.cpp models/Way.cpp

    models/BFS/BFS.cpp models/BFS/BFS.h models/Graph/Graph.cpp models/Graph/Graph.h models/Node/Node.cpp models/Node/Node.h models/PriorityQueue/PriorityQueue.cpp models/PriorityQueue/PriorityQueue.h models/Ant/Ant.cpp models/Ant/Ant.h models/AntColonyAlgorithm/AntColonyAlgorithm.cpp models/AntColonyAlgorithm/AntColonyAlgorithm.h models/MarkedNode.cpp models/Way.cpp
    exceptions/ValidationException.h
)

# Линковка Python
target_include_directories(ants PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(ants PRIVATE ${Python3_LIBRARIES})

include(GNUInstallDirs)
install(TARGETS ants
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
