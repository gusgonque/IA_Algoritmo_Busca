#ifndef A_ESTRELA_H
#define A_ESTRELA_H

#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>

/// Resultado canônico de uma busca (A*):
/// - caminho: sequência de nós do início ao objetivo (vazio se não achou)
/// - custo_total: soma dos pesos das arestas ao longo do caminho (0 se não achou)
/// - nos_expandidos: quantos nós foram expandidos (removidos da fronteira e geraram sucessores)
/// - encontrou: true se objetivo foi encontrado
struct ResultadoAEstrela {
    bool encontrou = false;
    std::vector<std::string> caminho;
    int custo_total = 0;
    int nos_expandidos = 0;
};

/// Estrutura auxiliar para nós na fronteira da A*.
/// Contém:
/// - nome: identificador do nó
/// - g: custo acumulado desde o início até este nó
/// - f: custo estimado total (f = g + h), usado como prioridade na fila
/// Operador `>` é definido para permitir uso em `std::priority_queue` como min-heap.
struct NoAEstrela {
    std::string nome;
    int g; // custo acumulado
    int f; // g + h

    bool operator>(const NoAEstrela &outro) const {
        return f > outro.f;
    }
};

/// Executa a busca A* no grafo carregado.
/// Usa heurísticas fornecidas no arquivo de entrada.
/// @param inicio Nó inicial (tipicamente `pontoInicial`)
/// @param objetivo Nó objetivo (tipicamente `pontoFinal`)
/// @return Estrutura ResultadoAEstrela com caminho, custo_total, nos_expandidos e encontrou.
ResultadoAEstrela executarAEstrela(const std::string &inicio, const std::string &objetivo);

/// Imprime uma iteração da A* no formato exigido.
/// Mostra "Iteracao n:", a "Lista" (conteúdo da fila de prioridade)
/// com "(no: g + h = f)", e a "Medida de desempenho".
/// @param out  Stream de saída (ex.: std::cout).
/// @param iter Número da iteração (1-based).
/// @param fronteira Snapshot da fronteira (cópia por valor, será consumida aqui).
/// @param g    Mapa de custo acumulado g(no) calculado ao inserir o nó na fronteira.
/// @param nosExpandidos Contagem acumulada de nós expandidos até esta iteração.
void imprimirIteracaoAEstrela(std::ostream &out, int iter, std::priority_queue<NoAEstrela, std::vector<NoAEstrela>, std::greater<NoAEstrela>> fronteira, const std::unordered_map<std::string, int> &g, int nosExpandidos);

#endif
