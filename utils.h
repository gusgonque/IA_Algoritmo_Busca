//
// Created by gusta on 24/07/2025.
//

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iosfwd>

/// Lê um arquivo de definição de labirinto/grafo e preenche as estruturas globais.
/// Formato esperado por linha: ponto_inicial(X)., ponto_final(Y)., orientado(s|n).,
/// pode_ir(U,V,c)., h(N,Goal,hc).
/// @param caminhoArquivo Caminho para o arquivo de entrada.
/// @effects Atualiza grafo, heuristicas, pontoInicial, pontoFinal e grafoOrientado.
void lerArquivoEntrada(const std::string &caminhoArquivo);

/// Processa uma linha do tipo ponto_inicial(X).
/// @param linha Linha completa lida do arquivo (pode conter espaços).
/// @return true se reconheceu/aplicou; false caso contrário.
/// @effects Define a variável global pontoInicial (ou contexto passado por referência).
bool lerPontoInicial(const std::string &linha);

/// Processa uma linha do tipo ponto_final(Y).
/// @param linha Linha completa.
/// @return true se reconheceu/aplicou; false caso contrário.
/// @effects Define a variável global pontoFinal.
bool lerPontoFinal(const std::string &linha);

/// Processa uma linha do tipo orientado(s|n).
/// @param linha Linha completa.
/// @return true se reconheceu/aplicou; false caso contrário.
/// @effects Define a variável global grafoOrientado (s->true, n->false).
bool lerOrientacao(const std::string &linha);

/// Processa uma linha do tipo pode_ir(U,V,c).
/// @param linha Linha completa.
/// @effects Insere aresta U->V com custo c em grafo; se não orientado, também V->U.
/// @return true se reconheceu/aplicou; false caso contrário.
/// @notes Deve validar custo numérico e nós não vazios.
bool lerAresta(const std::string &linha);

/// Processa uma linha do tipo h(N,Goal,hc).
/// @param linha Linha completa.
/// @effects Define heuristicas[N] = hc. (Goal pode ser verificado contra pontoFinal)
/// @return true se reconheceu/aplicou; false caso contrário.
/// @notes Ideal validar se Goal == pontoFinal (quando já conhecido) e hc >= 0.
bool lerHeuristica(const std::string &linha);

/// Imprime um resumo do estado atual carregado (grafo e heuristicas).
/// Mostra: ponto_inicial, ponto_final, orientado (s/n),
/// numero de nos, numero de arestas (e total de entradas de adjacencia),
/// e a lista (chave:valor) das heuristicas.
/// Nao altera estado global.
/// @param out Stream de saida (ex.: std::cout).
void imprimirResumo(std::ostream& out);

#endif //UTILS_H
