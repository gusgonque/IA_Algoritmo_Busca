#include <iostream>
#include "grafo.h"
#include "utils.h"
#include "algoritmos/dfs.h"

// Variáveis globais, definidas em grafo.cpp
extern Grafo grafo;
extern std::unordered_map<std::string, int> heuristicas;
extern std::string pontoInicial, pontoFinal;
extern bool grafoOrientado;

int main() {

    for (;;) {
        std::cout << "\n=== MENU ===\n"
                  << "1) Carregar arquivo de entrada.\n"
                  << "2) Mostrar resumo. (grafo/heuristicas)\n"
                  << "3) Executar algoritmo DFS. (Busca em Profundidade)\n"
                  << "0) Sair.\n"
                  << "> ";

        std::string opcao;
        if (!std::getline(std::cin, opcao)) break; // EOF/erro

        if (opcao == "0") {
            break;
        }
        if (opcao == "1") {
            std::cout << "Informe o caminho do arquivo (pode ser relativo ou absoluto): ";
            std::string caminho;
            if (!std::getline(std::cin, caminho)) {
                std::cerr << "Falha ao ler caminho.\n";
                continue;
            }

            // Limpar estado global ANTES de ler um novo arquivo
            grafo.clear();
            heuristicas.clear();
            pontoInicial.clear();
            pontoFinal.clear();
            grafoOrientado = false;

            lerArquivoEntrada(caminho);
        } else if (opcao == "2") {
            imprimirResumo(std::cout);
        } else if (opcao == "3") {
            if (pontoInicial.empty() || pontoFinal.empty()) {
                std::cout << "Carregue um arquivo valido antes.\n";
                continue;
            }

            std::cout << "Inicio da execucao\n";
            auto R = executarDFS(pontoInicial, pontoFinal);
            std::cout << "Fim da execucao\n";

        }

        else {
            std::cerr << "Opcao invalida.\n";
        }
    }


    return 0;
}