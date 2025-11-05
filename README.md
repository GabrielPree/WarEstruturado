# 🎯 Projeto WAR Estruturado (em C)

Este projeto é uma versão **simplificada e estruturada** do jogo de tabuleiro **WAR**, desenvolvida em linguagem **C** como parte de um trabalho acadêmico.  
O foco está no uso de **estruturas (`struct`)**, **funções `void`**, **alocação dinâmica de memória** e **organização modular** do código.

---

## 🧩 Funcionalidades Principais

- Cadastro dinâmico de territórios (nome, cor e número de tropas)  
- Sorteio automático da cor do jogador  
- Sistema de missões aleatórias:
  1. **Conquistar 2 territórios**
  2. **Destruir um exército sorteado**
  3. **Manter 2 territórios com 3 ou mais tropas**
- Mecânica básica de **ataque entre territórios**, com:
  - Rolagem de dados aleatória (1–6)
  - Conquista de territórios inimigos
  - Transferência parcial de tropas
  - Proibição de ataques entre territórios da mesma cor
- Verificação automática de missão a qualquer momento  
- Pausa com `getchar()` após cada ataque para leitura dos resultados  
- Interface de **menu interativo** via terminal

---

## ⚙️ Estrutura do Código

O projeto é dividido em funções modulares para facilitar a manutenção e a leitura:

| Função | Descrição |
|--------|------------|
| `cadastrarTerritorios()` | Cadastra os territórios dinamicamente |
| `listarTerritorios()` | Exibe o estado atual do mapa |
| `escolhaCor()` | Sorteia a cor do jogador |
| `sortearMissao()` | Sorteia uma missão e define, se necessário, uma cor alvo |
| `loopAtaque()` | Controla o fluxo dos ataques |
| `atacar()` | Realiza a simulação do ataque com rolagem de dados |
| `verificarMissao()` | Verifica se o jogador completou sua missão |
| `menu()` | Exibe o menu principal do jogo |
| `limpaBufferEntrada()` | Garante a leitura correta de entradas com `getchar()` |

---

## 🧠 Conceitos Aplicados

- Estruturas (`struct`)  
- Vetores de estruturas  
- Alocação dinâmica (`calloc` / `free`)  
- Manipulação de strings (`strcmp`, `strcpy`, `fgets`)  
- Modularização de código  
- Controle de fluxo (`switch`, `while`, `do-while`)  
- Funções do tipo `void`  
- Geração de números aleatórios (`rand()` e `srand(time(NULL))`)

---

## ▶️ Como Executar

1. **Clone o repositório:**
   ```bash
   git clone https://github.com/SEU_USUARIO/war-estruturado.git
2. Acesse a pasta do projeto:
  cd war-estruturado

4. Compile o código:
  gcc main.c -o war

5. Execute o jogo:
   ./war
---
   
## 🧾 Exemplo de Saída

```console
=======================
=   WAR ESTRUTURADO   =
=======================

--- Cadastrando o território 1 ---
Digite o nome do território: Brasil
Digite a cor do exército: verde
Digite o número de tropas: 4

--- Cadastrando o território 2 ---
Digite o nome do território: Argentina
Digite a cor do exército: vermelho
Digite o número de tropas: 3

--- Cadastrando o território 3 ---
Digite o nome do território: Chile
Digite a cor do exército: azul
Digite o número de tropas: 2

--- Cadastrando o território 4 ---
Digite o nome do território: México
Digite a cor do exército: verde
Digite o número de tropas: 5

--- Cadastrando o território 5 ---
Digite o nome do território: Canadá
Digite a cor do exército: vermelho
Digite o número de tropas: 4

====================================
    MAPA DO MUNDO - ESTADO ATUAL
====================================

1. Brasil (Exército verde, Tropas: 4)
2. Argentina (Exército vermelho, Tropas: 3)
3. Chile (Exército azul, Tropas: 2)
4. México (Exército verde, Tropas: 5)
5. Canadá (Exército vermelho, Tropas: 4)

-------------------------------------
  Sua cor de exército foi sorteada!  
  Você será o exército verde.
-------------------------------------

--- SUA MISSÃO ---
Destruir o exército vermelho.

--- MENU DE AÇÕES ---
1 - Atacar
2 - Verificar Missão
0 - Sair
Escolha sua ação: 
````

## 💻 Autor

Nome: Gabriel Preé

Curso: Análise e Desenvolvimento de Sistemas – Estácio

Objetivo: Trabalho prático da disciplina de Estruturas de Dados

## 📚 Licença

Este projeto é de uso acadêmico e está sob a licença MIT.

Sinta-se à vontade para estudar, modificar e reutilizar o código.
