#include "a_estrela.h"
#include "../grafo.h"

#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm> // reverse

// Variáveis globais
extern Grafo grafo;
extern std::string pontoInicial, pontoFinal;
extern std::unordered_map<std::string, int> heuristicas;

ResultadoAEstrela executarAEstrela(const std::string &inicio, const std::string &objetivo) {
    ResultadoAEstrela R;

    if (inicio.empty() || objetivo.empty() || grafo.empty()) return R;

    if (inicio == objetivo) {
        R.caminho = { inicio };
        R.custo_total = 0;
        R.nos_expandidos = 0;
        R.encontrou = true;
        return R;
    }

    // fronteira como min-heap
    std::priority_queue<NoAEstrela, std::vector<NoAEstrela>, std::greater<NoAEstrela>> fronteira;
    std::unordered_set<std::string> visitados;
    std::unordered_map<std::string, std::string> pai;
    std::unordered_map<std::string, int> g; // custo acumulado

    int hInicio = heuristicas[inicio];
    fronteira.push({inicio, 0, 0 + hInicio});
    g[inicio] = 0;

    int iter = 0;

    while (!fronteira.empty()) {
        NoAEstrela atual = fronteira.top();
        fronteira.pop();

        std::string u = atual.nome;

        if (visitados.count(u)) continue;
        visitados.insert(u);
        R.nos_expandidos++;

        // teste de objetivo
        if (u == objetivo) {
            // reconstruir caminho
            std::vector<std::string> caminho;
            for (std::string x = u; ; ) {
                caminho.push_back(x);
                if (x == inicio) break;
                x = pai[x];
            }
            std::reverse(caminho.begin(), caminho.end());
            R.caminho = std::move(caminho);
            R.custo_total = g[u];
            R.encontrou = true;
            return R;
        }

        // expandir sucessores
        const auto it = grafo.find(u);
        if (it != grafo.end()) {
            const auto &adj = it->second;
            for (const auto &aresta : adj) {
                const std::string &v = aresta.destino;
                int custo = aresta.custo;
                int gNovo = g[u] + custo;
                int hNovo = heuristicas.count(v) ? heuristicas[v] : 0;
                int fNovo = gNovo + hNovo;

                if (!g.count(v) || gNovo < g[v]) {
                    g[v] = gNovo;
                    pai[v] = u;
                    fronteira.push({v, gNovo, fNovo});
                }
            }
        }

        // imprimir a iteração
        iter++;
        imprimirIteracaoAEstrela(std::cout, iter, fronteira, g, R.nos_expandidos);
    }

    return R;
}

void imprimirIteracaoAEstrela(std::ostream &out, int iter, 
                              std::priority_queue<NoAEstrela, std::vector<NoAEstrela>, std::greater<NoAEstrela>> fronteira,
                              const std::unordered_map<std::string, int> &g, int nosExpandidos) {
    out << "Iteracao " << iter << ":\n";
    out << "Lista: ";

    // copiar heap para imprimir
    std::vector<NoAEstrela> tmp;
    while (!fronteira.empty()) {
        tmp.push_back(fronteira.top());
        fronteira.pop();
    }

    // reordenar em ordem crescente de f (já está garantido pela priority_queue, mas só para exibir ordenado)
    std::sort(tmp.begin(), tmp.end(), [](const NoAEstrela &a, const NoAEstrela &b) {
        return a.f < b.f;
    });

    for (const auto &no : tmp) {
        int h = heuristicas.count(no.nome) ? heuristicas[no.nome] : 0;
        out << "(" << no.nome << ": " << no.g << " + " << h << " = " << no.f << ") ";
    }
    out << "\n";

    out << "Número de nós expandidos: " << nosExpandidos << "\n\n";
}
