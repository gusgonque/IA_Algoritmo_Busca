#include <iostream>
#include "grafo.h"
#include "utils.h"

// Variáveis globais
Grafo grafo;
std::unordered_map<std::string, int> heuristicas;
std::string pontoInicial, pontoFinal;
bool grafoOrientado = false;

int main() {

    lerArquivoEntrada("../erro.txt");

    return 0;
}