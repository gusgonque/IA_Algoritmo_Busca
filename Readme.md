# Projeto IA - Algoritmos de Busca no Labirinto do Minotauro 🧠⚔️

Este projeto é parte da disciplina de **Inteligência Artificial (IA)** do curso de Ciência da Computação da **UNIOESTE - Foz do Iguaçu**. Ele simula a travessia do labirinto do Minotauro por Teseu, utilizando algoritmos de busca para encontrar o caminho mais eficiente entre dois pontos.

O labirinto é representado como um **grafo ponderado** e pode ser orientado ou não orientado. O usuário fornece um arquivo de entrada com a definição do grafo, os pontos de início e fim da busca, e heurísticas para algoritmos informados.

---

## 👥 Integrantes

- André Luiz Grem Voigt
- Gustavo Gonçalves Queiroz

---

## 📁 Estrutura do Projeto

| Pasta/Arquivo | Responsabilidade |
|---------------|------------------|
| `algoritmos/a_estrela.cpp/.h` | Implementação do algoritmo A\* (melhor caminho com heurística) |
| `algoritmos/dfs.cpp/.h`    | Implementação da Busca em Profundidade (pior caminho) |
| `algoritmos/a_limitado.cpp/.h`| Implementação do A\* com limite de custo (bônus) |
| `grafo.h/.cpp`            | Estrutura de dados e manipulação do grafo e heurísticas |
| `utils.h/.cpp`           | Leitura e processamento do arquivo de entrada |
| `main.cpp`                 | Ponto principal do programa, onde tudo é orquestrado |

---

## 🧩 Funcionalidades

- Leitura de arquivos de entrada com definição de grafos e heurísticas
- Suporte a grafos **orientados e não orientados**
- Execução de diferentes algoritmos de busca:
    - **A*** (informado, melhor solução)
    - **Busca em Profundidade** (não informada, pior solução)
    - **A\* com limite de custo** (bônus)
- Impressão da execução passo a passo:
    - Nó sendo expandido
    - Lista da fronteira
    - Medida de desempenho: Número de nós expandidos
- Saída final com:
    - Caminho encontrado
    - Custo total
    - Total de nós expandidos

---

## 📥 Formato do Arquivo de Entrada

```prolog
ponto_inicial(a0).
ponto_final(f0).
orientado(n).

pode_ir(a0,b0,10).
pode_ir(b0,c0,20).
pode_ir(c0,f0,15).

h(a0,f0,40).
h(b0,f0,30).
h(c0,f0,10).
h(f0,f0,0).
