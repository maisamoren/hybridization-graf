/*******************************************
 * Biblioteca para Trilha Euleriana em grafo
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "lista.h"
#include "grafo.h"
#include "euleriano.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Encontra uma trilha Euleriana fechada no grafo direcionado G e a devolve
// na forma de uma lista de vértices, com o primeiro e último vértices iguais.
// OBS: para cada par de vértices (u,v) incluído na lista, a aresta (u,v) é
// removida do grafo. Ao final, o conjunto de arestas de G será vazio.
// Funções auxiliares usadas: rotaciona(T), trilha_fechada(G,T,v) e
// concatena(T, TF).
lista trilha_euleriana(grafo G) {
  // supondo que todos os vértices de G tem grau par
  // r <- vértice de G
  // T <- r

  // enquanto E(G) != E(T)
  //   v <- vértice de T de grau positivo em G-E(T)
  //   faça uma rotação em T de forma que fazer de v seu início
  //   T <- concatena (T, TrilhaFechada(G-E(T),v))

  // devolva T
}

// Encontra uma trilha fechada no grafo G a partir de v e
// a devolve na forma de uma lista de vértices.
// Para cada par de vértices (u,v) incluído na lista, remove
// do grafo G a aresta (u,v).
lista trilha_fechada(grafo G, vertice v) {
  // supondo que todos os vértices de G tem grau par
  // T <- v
  // x <- v

  // repita
  //   [x,y] <- aresta de fronteira de x - arestas de T
  //   acrescente y ao final de T
  //   x <- y
  // até que y = v

  // devolva T
}

// Recebe uma lista T representando uma trilha fechada e
// um nó n dessa lista e rotaciona a trilha de modo a fazer
// de n o seu início.
void rotaciona(lista T, no n) {
  
  // se T possui um único vértice ou n é o primeiro nó de T,
  // já está rotacionado
  if (primeiro_no(T) == ultimo_no(T) || n == primeiro_no(T))
    return;
  
  desempilha(T);
  no pri = primeiro_no(T);
  no ult = ultimo_no(T);
  no ant = anterior(n);
  if (ant) {
    ult->proximo = pri;
    pri->anterior = ult;
    T->primeiro_no = n;
    n->anterior = NULL;
    T->ultimo_no = ant;
    ant->proximo = NULL;
  }
  enfila(conteudo(n), T);
}

// Considera que T e TF são duas trilhas fechadas com as
// mesmas pontas e concatena TF em T. Libera memória de TF.
void concatena(lista T, lista TF) {
  if (primeiro_no(T) == ultimo_no(T)) {
    T->primeiro_no = primeiro_no(TF);
    T->ultimo_no = ultimo_no(TF);
  }
  else if (primeiro_no(T) != ultimo_no(T)) {
    remove_ultimo(T);
    no m = ultimo_no(T);
    no n = primeiro_no(TF);
    m->proximo = n;
    n->anterior = m;
    T->ultimo_no = ultimo_no(TF);
  }
  free(TF);
}

// Funções para imprimir uma trilha
void imprime_vertice_rotulo(vertice v) {
  printf("%s ", vertice_rotulo(v));
}
void imprime_trilha(lista T) {
  printf("Trilha Euleriana: ( ");
  imprime_lista(T, (void_f_obj) imprime_vertice_rotulo);
  printf(")\n");
}
