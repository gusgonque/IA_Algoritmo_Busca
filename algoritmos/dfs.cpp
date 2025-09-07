//
// Created by gusta on 05/08/2025.
//

#include "dfs.h"
#include "../grafo.h"

#include <iostream>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <algorithm> // reverse

// Variáveis globais
extern Grafo grafo;
extern std::string pontoInicial, pontoFinal;
extern std::unordered_map<std::string, int> heuristicas;

ResultadoDFS executarDFS(const std::string &inicio, const std::string &objetivo) {
    ResultadoDFS R;

    // guarda-chuvas
    if (inicio.empty() || objetivo.empty() || grafo.empty()) return R;

    // (opcional) caso trivial
    if (inicio == objetivo) {
        R.caminho = { inicio };
        R.custo_total = 0;
        R.nos_expandidos = 0;
        R.encontrou = true;
        return R;
    }

    std::stack<std::string> fronteira;
    std::unordered_set<std::string> visitados;
    std::unordered_map<std::string, std::string> pai;
    std::unordered_map<std::string, int> g; // custo acumulado g(no)

    fronteira.push(inicio);
    g[inicio] = 0;

    int iter = 0;

    while (!fronteira.empty()) {
        std::string u = fronteira.top();
        fronteira.pop();

        if (visitados.count(u)) {
            // ja foi expandido antes; segue
            continue;
        }

        visitados.insert(u);
        R.nos_expandidos++;  // definimos “expandir” como remover da fronteira e gerar sucessores

        // teste de objetivo
        if (u == objetivo) {
            // (1) reconstruir caminho usando o mapa pai
            std::vector<std::string> caminho;
            for (std::string x = u; ; ) {
                caminho.push_back(x);
                if (x == inicio) break;
                auto itp = pai.find(x);
                if (itp == pai.end()) break; // robustez minima
                x = itp->second;
            }
            std::reverse(caminho.begin(), caminho.end());
            R.caminho = std::move(caminho);

            // (2) custo total: g[u] contem o custo do caminho descoberto ate u
            R.custo_total = g[u];

            R.encontrou = true;
            return R;
        }

        // gerar sucessores de u
        const auto it = grafo.find(u);
        if (it != grafo.end()) {
            const auto& adj = it->second;

            // percorrer do fim pro começo para respeitar a ordem da lista na pilha (LIFO)
            for (int i = static_cast<int>(adj.size()) - 1; i >= 0; --i) {
                const std::string& v = adj[i].destino;
                int custo = adj[i].custo;

                // evita empilhar repetidamente: so define pai na primeira vez
                if (!visitados.count(v) && !pai.count(v)) {
                    pai[v] = u;
                    g[v]  = g[u] + custo;
                    fronteira.push(v);
                }
            }
        }

        // imprimir a iteracao apos inserir sucessores
        iter++;
        imprimirIteracaoDFS(std::cout, iter, fronteira, g, R.nos_expandidos);
    }

    return R; // encontrou=false, caminho vazio, custo_total=0
}

void imprimirIteracaoDFS(std::ostream &out, int iter, std::stack<std::string> pilha, const std::unordered_map<std::string, int> &g, int nosExpandidos) {
    out << "Iteracao " << iter << ":\n";
    out << "Lista: ";

    // imprimir do topo para a base
    while (!pilha.empty()) {
        const std::string no = pilha.top();
        pilha.pop();

        int dist = 0;
        if (auto it = g.find(no); it != g.end()) dist = it->second;

        int h = 0;
        if (auto ih = heuristicas.find(no); ih != heuristicas.end()) h = ih->second;

        out << "(" << no << ": " << dist << " + " << h << " = " << (dist + h) << ") ";
    }
    out << "\n";

    out << "Número de nós expandidos: " << nosExpandidos << "\n\n";

}
