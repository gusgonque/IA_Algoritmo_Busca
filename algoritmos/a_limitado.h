#ifndef A_LIMITADO_H
#define A_LIMITADO_H

#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>
#include "a_estrela.h"

/// Resultado canônico da busca A* limitada (com fio):
/// - caminho: sequência de nós do início ao objetivo (vazio se não achou ou excedeu fio)
/// - custo_total: soma dos pesos das arestas ao longo do caminho (0 se não achou)
/// - nos_expandidos: quantos nós foram expandidos (removidos da fronteira e geraram sucessores)
/// - encontrou: true se objetivo foi encontrado dentro do limite do fio
struct ResultadoAEstrelaLimitado {
    bool encontrou = false;
    std::vector<std::string> caminho;
    int custo_total = 0;
    int nos_expandidos = 0;
};

/// Executa a busca A* limitada pelo comprimento do fio.
/// Não expande caminhos cujo custo acumulado exceda o valor fornecido.
/// @param inicio Nó inicial (tipicamente `pontoInicial`)
/// @param objetivo Nó objetivo (tipicamente `pontoFinal`)
/// @param comprimentoFio Limite máximo permitido para o custo acumulado
/// @return Estrutura ResultadoAEstrelaLimitado com caminho, custo_total, nos_expandidos e encontrou.
ResultadoAEstrelaLimitado executarAEstrelaLimitado(const std::string &inicio, const std::string &objetivo, int comprimentoFio);

/// Imprime uma iteração da A* limitada no formato exigido.
/// Mostra "Iteracao n:", a "Fila" (conteúdo da fila de prioridade)
/// com "(no: g + h = f)", a "Medida de desempenho"
/// e o "Comprimento restante".
/// @param out  Stream de saída (ex.: std::cout).
/// @param iter Número da iteração (1-based).
/// @param fronteira Snapshot da fronteira (cópia por valor, será consumida aqui).
/// @param g    Mapa de custo acumulado g(no) calculado ao inserir o nó na fronteira.
/// @param nosExpandidos Contagem acumulada de nós expandidos até esta iteração.
/// @param comprimentoRestante Comprimento de fio que ainda pode ser usado após expandir o nó atual.
void imprimirIteracaoAEstrelaLimitado(std::ostream &out, int iter, std::priority_queue<NoAEstrela, std::vector<NoAEstrela>, std::greater<NoAEstrela>> fronteira, const std::unordered_map<std::string, int> &g, int nosExpandidos, int comprimentoRestante);

#endif
