//
// Created by gusta on 05/08/2025.
//

#ifndef DFS_H
#define DFS_H

#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

/// Resultado canônico de uma busca (DFS):
/// - caminho: sequencia de nós do início ao objetivo (vazio se não achou)
/// - custo_total: soma dos pesos das arestas ao longo do caminho (0 se não achou)
/// - nos_expandidos: quantos nós foram expandidos (removidos da fronteira e geraram sucessores)
/// - encontrou: true se objetivo foi encontrado
struct ResultadoDFS {
    std::vector<std::string> caminho;
    int custo_total = 0;
    int nos_expandidos = 0;
    bool encontrou = false;
};

/// Executa Busca em Profundidade (iterativa com pilha) no grafo carregado.
/// Não usa heuristica.
/// @param inicio Nó inicial (tipicamente `pontoInicial`)
/// @param objetivo Nó objetivo (tipicamente `pontoFinal`)
/// @return Estrutura ResultadoDFS com caminho, custo_total, nos_expandidos e encontrou.
ResultadoDFS executarDFS(const std::string& inicio, const std::string& objetivo);

/// Imprime uma iteracao da DFS no formato exigido.
/// Mostra "Iteracao n:", a "Lista" (conteudo da pilha - topo para base)
/// com "(no: dist + h = soma)", e a "Medida de desempenho".
/// @param out  Stream de saida (ex.: std::cout).
/// @param iter Numero da iteracao (1-based).
/// @param pilha Snapshot da fronteira (copia por valor, sera consumida aqui).
/// @param g    Mapa de custo acumulado g(no) calculado quando o no foi empilhado.
/// @param nosExpandidos Contagem acumulada de nos expandidos ate esta iteracao.
static void imprimirIteracaoDFS(std::ostream& out, int iter, std::stack<std::string> pilha, const std::unordered_map<std::string,int>& g, int nosExpandidos);


#endif //DFS_H
