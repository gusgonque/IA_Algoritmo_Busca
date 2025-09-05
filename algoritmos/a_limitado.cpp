#include "a_limitado.h"
#include "a_estrela.h"   // para reaproveitar struct NoAEstrela
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

ResultadoAEstrelaLimitado executarAEstrelaLimitado(const std::string &inicio, const std::string &objetivo, int comprimentoFio) {
    ResultadoAEstrelaLimitado R;

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

    std::cout << "Qual o comprimento do fio? " << comprimentoFio << "\n\n";

    while (!fronteira.empty()) {
        NoAEstrela atual = fronteira.top();
        fronteira.pop();

        std::string u = atual.nome;

        if (visitados.count(u)) continue;
        visitados.insert(u);
        R.nos_expandidos++;

        // se estourou o fio, descarta
        if (g[u] > comprimentoFio) {
            std::cout << "Iteracao " << ++iter << ":\n";
            std::cout << "Caminho descartado: custo " << g[u] << " excedeu fio (" << comprimentoFio << ")\n\n";
            continue;
        }

        // teste de objetivo
        if (u == objetivo) {
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
        imprimirIteracaoAEstrelaLimitado(std::cout, iter, fronteira, g, R.nos_expandidos, comprimentoFio - g[u]);
    }

    return R;
}

void imprimirIteracaoAEstrelaLimitado(std::ostream &out, int iter,
    std::priority_queue<NoAEstrela, std::vector<NoAEstrela>, std::greater<NoAEstrela>> fronteira,
    const std::unordered_map<std::string, int> &g, int nosExpandidos, int comprimentoRestante) {
    
    out << "Iteracao " << iter << ":\n";
    out << "Fila: ";

    std::vector<NoAEstrela> tmp;
    while (!fronteira.empty()) {
        tmp.push_back(fronteira.top());
        fronteira.pop();
    }

    std::sort(tmp.begin(), tmp.end(), [](const NoAEstrela &a, const NoAEstrela &b) {
        return a.f < b.f;
    });

    for (const auto &no : tmp) {
        int h = heuristicas.count(no.nome) ? heuristicas[no.nome] : 0;
        out << "(" << no.nome << ": " << no.g << " + " << h << " = " << no.f << ") ";
    }
    out << "\n";

    out << "Medida de desempenho: " << nosExpandidos << "\n";
    out << "Comprimento restante: " << comprimentoRestante << "\n\n";
}
