//
// Created by gusta on 24/07/2025.
//

#include "utils.h"
#include "grafo.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>

// Variáveis globais (declara em outro arquivo se for expandir depois)
extern Grafo grafo;

void lerArquivoEntrada(const std::string& caminhoArquivo) {
    std::ifstream arquivo(caminhoArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << caminhoArquivo << std::endl;
        return;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (linha.find("pode_ir(") == 0) {
            // Extrai origem, destino e custo
            std::regex regex("pode_ir\\(([^,]+),([^,]+),([^)]+)\\)\\.");
            std::smatch match;
            if (std::regex_search(linha, match, regex)) {
                std::string origem = match[1];
                std::string destino = match[2];
                int custo = std::stoi(match[3]);

                grafo[origem].push_back({ destino, custo });

                extern bool grafoOrientado;
                if (!grafoOrientado) {
                    grafo[destino].push_back({ origem, custo });
                }
            }
        }
        // Outras leituras virão depois: ponto_inicial, ponto_final, orientado, h(...)
    }

    arquivo.close();
}
