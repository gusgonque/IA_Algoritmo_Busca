//
// Created by gusta on 24/07/2025.
//

#ifndef GRAFO_H
#define GRAFO_H


#include <string>
#include <vector>
#include <unordered_map>

struct Aresta {
    std::string destino;
    int custo;
};

using Grafo = std::unordered_map<std::string, std::vector<Aresta>>;



#endif //GRAFO_H
