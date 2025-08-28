//
// Created by gusta on 24/07/2025.
//

#include "utils.h"
#include "grafo.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_set>

// Variáveis globais, definidas em grafo.cpp
extern Grafo grafo;
extern std::unordered_map<std::string, int> heuristicas;
extern std::string pontoInicial, pontoFinal;
extern bool grafoOrientado;

void lerArquivoEntrada(const std::string &caminhoArquivo) {
    std::ifstream arquivo(caminhoArquivo);
    if (!arquivo.is_open()) {
        std::cout << "AVISO: Erro ao abrir o arquivo: " << caminhoArquivo << std::endl;
        return;
    }

    int numLinhas = 0;

    std::string linha;
    while (std::getline(arquivo, linha)) {

        // Pular linhas em branco e comentários
        if (linha.empty()) {            // linha vazia
            numLinhas++;
            continue;
        } if (linha.rfind('%', 0) == 0) {   // comentário
            numLinhas++;
            continue;
        }

        if (linha.find("ponto_inicial(") == 0) {
            if (!lerPontoInicial(linha))
                std::cout << "AVISO [linha "<< numLinhas <<"] ponto_inicial malformado. (esperado ponto_inicial(X).)" << std::endl;
        } else if (linha.find("ponto_final(") == 0) {
            if (!lerPontoFinal(linha))
                std::cout << "AVISO [linha "<< numLinhas <<"] ponto_final malformado. (esperado ponto_final(Y).)" << std::endl;
        } else if (linha.find("orientado(") == 0) {
            if (!lerOrientacao(linha))
                std::cout << "AVISO [linha "<< numLinhas <<"] orientado malformado. (esperado orientado(n). ou orientado(s).)" << std::endl;
        } else if (linha.find("pode_ir(") == 0) {
            if (!lerAresta(linha))
                std::cout << "AVISO [linha "<< numLinhas <<"] pode_ir malformado. (esperado pode_ir(U,V,c).)" << std::endl;
        } else if (linha.find("h(") == 0) {
            if (!lerHeuristica(linha))
                std::cout << "AVISO [linha "<< numLinhas <<"] heuristica malformada. (esperado h(U,ponto_final,c).)" << std::endl;
        } else
            std::cout << "AVISO [linha "<< numLinhas <<"] Linha nao reconhecida: " << linha << std::endl;

        numLinhas++;
    }

    arquivo.close();
    std::cout << "Arquivo carregado.\n";
}

/// Remove espaços em branco (ASCII) no começo e no fim da string, in-place.
/// @param s [in,out] String a ser aparada (só mexe nas bordas).
/// @notes Usa std::isspace; não remove espaços internos; assume locale padrão.
/// @examples "  a0  " -> "a0"; "\t\nx\n" -> "x".
static void trimInPlace(std::string& s) {
    size_t i = 0;
    while (i < s.size() && std::isspace(static_cast<unsigned char>(s[i]))) ++i;
    size_t j = s.size();
    while (j > i && std::isspace(static_cast<unsigned char>(s[j - 1]))) --j;
    s = s.substr(i, j - i);
}

bool lerPontoInicial(const std::string &linha) {
    const size_t abre = linha.find('(');
    const size_t fecha = linha.rfind(')');

    if (abre == std::string::npos || fecha == std::string::npos || fecha <= abre + 1) {
        return false; // sem parênteses ou vazio entre eles
    }

    std::string token = linha.substr(abre + 1, fecha - abre - 1);
    trimInPlace(token);

    if (token.empty()) {
        return false; // ponto_inicial() ou só espaços
    }

    pontoInicial = token;
    return true;
}

bool lerPontoFinal(const std::string &linha) {
    const size_t abre = linha.find('(');
    const size_t fecha = linha.rfind(')');

    if (abre == std::string::npos || fecha == std::string::npos || fecha <= abre + 1) {
        return false; // sem parênteses ou vazio entre eles
    }

    std::string token = linha.substr(abre + 1, fecha - abre - 1);
    trimInPlace(token);

    if (token.empty()) {
        return false; // ponto_final() ou só espaços
    }

    pontoFinal = token;
    return true;
}

bool lerOrientacao(const std::string &linha) {
    const size_t abre = linha.find('(');
    const size_t fecha = linha.rfind(')');

    if (abre == std::string::npos || fecha == std::string::npos || fecha <= abre + 1) {
        return false; // sem parênteses ou vazio entre eles
    }

    std::string token = linha.substr(abre + 1, fecha - abre - 1);
    trimInPlace(token);

    if (token.empty()) {
        return false; // ponto_final() ou só espaços
    }

    if (token == "s") {
        grafoOrientado = true;
    } else if (token == "n") {
        grafoOrientado = false;
    } else {
        return false; // valor inválido
    }

    return true;
}

bool lerAresta(const std::string &linha) {
    const size_t abre  = linha.find('(');
    const size_t fecha = linha.rfind(')');
    if (abre == std::string::npos || fecha == std::string::npos || fecha <= abre + 1) {
        return false; // faltam parênteses ou vazio entre eles
    }
    std::string miolo = linha.substr(abre + 1, fecha - abre - 1);

    const size_t c1 = miolo.find(',');
    if (c1 == std::string::npos) return false;

    const size_t c2 = miolo.find(',', c1 + 1);
    if (c2 == std::string::npos) return false;

    // garantir que NÃO há terceira vírgula
    if (miolo.find(',', c2 + 1) != std::string::npos) return false;

    std::string u = miolo.substr(0, c1);
    std::string v = miolo.substr(c1 + 1, c2 - (c1 + 1));
    std::string custoStr = miolo.substr(c2 + 1);

    trimInPlace(u);
    trimInPlace(v);
    trimInPlace(custoStr);

    if (u.empty() || v.empty()) {
        return false; // identificadores vazios
    }

    int custo = 0;
    try {
        size_t pos = 0;
        custo = std::stoi(custoStr, &pos);
        if (pos != custoStr.size() || custo < 0) {
            return false; // lixo após número ou negativo
        }
    } catch (...) {
        return false; // não é inteiro válido
    }


    grafo[u].push_back(Aresta{ v, custo });
    if (!grafoOrientado) {
        grafo[v].push_back(Aresta{ u, custo });
    }
    return true;
}

bool lerHeuristica(const std::string &linha) {
    const size_t abre  = linha.find('(');
    const size_t fecha = linha.rfind(')');
    if (abre == std::string::npos || fecha == std::string::npos || fecha <= abre + 1) {
        return false; // faltam parênteses ou vazio entre eles
    }
    std::string miolo = linha.substr(abre + 1, fecha - abre - 1);

    const size_t c1 = miolo.find(',');
    if (c1 == std::string::npos) return false;

    const size_t c2 = miolo.find(',', c1 + 1);
    if (c2 == std::string::npos) return false;

    // garantir que NÃO há terceira vírgula
    if (miolo.find(',', c2 + 1) != std::string::npos) return false;

    std::string u = miolo.substr(0, c1);
    std::string v = miolo.substr(c1 + 1, c2 - (c1 + 1));
    std::string custoHStr = miolo.substr(c2 + 1);

    trimInPlace(u);
    trimInPlace(v);
    trimInPlace(custoHStr);

    if (u.empty() || v.empty()) {
        return false; // identificadores vazios
    }

    int custoH = 0;
    try {
        size_t pos = 0;
        custoH = std::stoi(custoHStr, &pos);
        if (pos != custoHStr.size() || custoH < 0) {
            return false; // lixo após número ou negativo
        }
    } catch (...) {
        return false; // não é inteiro válido
    }

    if (!pontoFinal.empty() && v != pontoFinal) {
        return false;  // dispatcher imprimirá: "heurística malformada (Goal != ponto_final)"
    }

    heuristicas[u] = custoH;
    return true;
}

void imprimirResumo(std::ostream &out) {
    out << "ponto_inicial: " << (pontoInicial.empty() ? "<vazio>" : pontoInicial) << '\n';
    out << "ponto_final  : " << (pontoFinal.empty() ? "<vazio>" : pontoFinal) << '\n';
    out << "orientado    : " << (grafoOrientado ? "s" : "n") << '\n';

    // Conjunto de nos distintos (origens, destinos e nos com heuristica)
    std::unordered_set<std::string> nosDistintos;

    // Origens: chaves do grafo
    for (const auto& par : grafo) {
        nosDistintos.insert(par.first);
        // Destinos: cada aresta da lista de adjacencia
        for (const auto& aresta : par.second) {
            nosDistintos.insert(aresta.destino);
        }
    }

    // Nos que aparecem somente em heuristicas
    for (const auto& h : heuristicas) {
        nosDistintos.insert(h.first);
    }

    const size_t nos = nosDistintos.size();

    size_t adjEntradas = 0;
    for (const auto& par : grafo) adjEntradas += par.second.size();

    // Nota: se houver self-loops, a contagem de arestas em nao orientado pode nao ser exata com /2.
    const size_t arestas = grafoOrientado ? adjEntradas : (adjEntradas / 2);

    out << "nos: " << nos << '\n';
    out << "arestas: " << arestas << " (entradas de adjacencia = " << adjEntradas << ")\n";

    out << "heuristicas (total: " << heuristicas.size() << "):\n";
    for (const auto& h : heuristicas) {
        out << "  " << h.first << " : " << h.second << '\n';
    }
}
