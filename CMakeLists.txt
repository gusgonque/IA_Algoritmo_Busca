cmake_minimum_required(VERSION 3.31)
project(IA_P2)

set(CMAKE_CXX_STANDARD 20)

add_executable(IA_P2 main.cpp
        grafo.cpp
        grafo.h
        utils.cpp
        utils.h
        algoritmos/a_estrela.cpp
        algoritmos/a_estrela.h
        algoritmos/dfs.cpp
        algoritmos/dfs.h
        algoritmos/a_limitado.cpp
        algoritmos/a_limitado.h)
