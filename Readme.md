# Projeto IA - Algoritmos de Busca no Labirinto do Minotauro 🧠⚔️

Este projeto é parte da disciplina de **Inteligência Artificial (IA)** do curso de Ciência da Computação da **UNIOESTE - Foz do Iguaçu**. Ele simula a travessia do labirinto do Minotauro por Teseu, utilizando algoritmos de busca para encontrar o caminho mais eficiente entre dois pontos.

O labirinto é representado como um **grafo ponderado** e pode ser orientado ou não orientado. O usuário fornece um arquivo de entrada com a definição do grafo, os pontos de início e fim da busca, e heurísticas para algoritmos informados.

---

## 👥 Integrantes

- André Luiz Grem Voigt
- Gustavo Gonçalves Queiroz

---

## 📁 Estrutura do Projeto

| Pasta/Arquivo                  | Responsabilidade                                               |
|--------------------------------|----------------------------------------------------------------|
| `algoritmos/a_estrela.cpp/.h`  | Implementação do algoritmo A\* (melhor caminho com heurística) |
| `algoritmos/dfs.cpp/.h`        | Implementação da Busca em Profundidade (pior caminho)          |
| `algoritmos/a_limitado.cpp/.h` | Implementação do A\* com limite de custo (bônus)               |
| `Entradas/`   | Pasta com arquivos de entrada usados para testar os algoritmos |
| `grafo.h/.cpp`                 | Estrutura de dados e manipulação do grafo e heurísticas        |
| `utils.h/.cpp`                 | Leitura e processamento do arquivo de entrada                  |
| `main.cpp`                     | Ponto principal do programa, onde tudo é orquestrado           |

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

### 🚀 Como executar

#### Pré-requisitos
- **CMake** compatível com o projeto. O `CMakeLists.txt` está com `cmake_minimum_required(VERSION 3.31)`.
  - Se mantiver 3.31, instale CMake 3.31+.
  - *(Opcional)* Para maior compatibilidade, você pode reduzir para `3.20`.
- **Compilador C++20**:
  - GCC ≥ 10, Clang ≥ 12 ou MSVC ≥ 19.28.
- **Nenhuma biblioteca adicional é necessária.** O projeto usa apenas a STL.

#### CLion (recomendado)
1. Abra o diretório do projeto no **CLion**.
2. O CLion configurará o CMake e gerará o alvo `IA_P2`.
3. **Defina o Working Directory** (para o programa encontrar os `.txt` por caminho relativo):  
   *Run → Edit Configurations → Working directory* = **`$ProjectFileDir$`**
4. Build: **Build → Build ‘IA_P2’**.
5. Run: **Run → Run ‘IA_P2’**.
  - No menu do programa, use **1)** para carregar o arquivo de entrada (ex.: `Entradas/entrada_5.txt`), **3)** para DFS, **4)** para A*, **5)** para A* limitado.

#### Terminal (Linux/macOS)
```bash
# na raiz do projeto
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . -j
./IA_P2

```

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
