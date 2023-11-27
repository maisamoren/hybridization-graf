/*******************************************
 * Biblioteca para manipulação de fragmentos
 * de DNA via spectrum.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "lista.h"
#include "grafo.h"
#include "euleriano.h"
#include "spectrum.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Devolve o spectrum (l-mers) do fragmento s
// em uma lista de strings, cada string é um l-mer
lista spectrum(char *s, int l) {
  int i, j;
  int num_subsequencias = (strlen(s) - l) + 1;
  lista dna = cria_lista();

  for (i = 0; i < num_subsequencias; ++i){
    char *substring = (char*)malloc(l * sizeof(char));
    if(!substring)
      exit(1);

    for (j = 0; j < l; ++j){
      substring[j] = s[i+j];
    }

    enfila(substring, dna);
  }
  return dna;
}

// Embaralha o spectrum
void embaralha_spectrum(lista l_mers) {
  srand(time(NULL));
  int N_SIZE = 5;
  lista L[N_SIZE];
  for (int i = 0; i < N_SIZE; ++i)
    L[i] = cria_lista();
  
  int i = ((int)rand()) % N_SIZE;
  while (!vazio(l_mers)) {
    enfila(desempilha(l_mers), L[i]);
    i = ((int)rand()) % N_SIZE;
  }
  for (int i = 0; i < N_SIZE; ++i)
    while (!vazio(L[i]))
      enfila(desempilha(L[i]), l_mers);
}

// Funções para impressão
void imprime_mer(char *mer) {
  printf("%s", mer);
}
void imprime_spectrum(lista l_mers) {
  printf("Spectrum: ");
  imprime_lista(l_mers, (void_f_obj) imprime_mer);
  printf("\n");
}

// Constroi grafo direcionado a partir do spectrum.
// Vértices são (l-1) mers e arestas representam l-mers.
// É necessário balancear o grafo (adicionar aresta falsa);
// caso isso seja feito, devolve em ini_id e fim_id os ids dos
// vértices da aresta falsa adicionada.
grafo constroi_grafo_spectrum(lista l_mers, int l, int *ini_id, int *fim_id) {
  
  grafo G = cria_grafo(1);  // cria grafo vazio
  int IDV = 1;              // contador de ids de vértices
  int IDA = 1;              // contador de ids de arestas
  
  // Para cada l-mer, adiciona (se já não existe) um vértice
  // com os l-1 primeiros caracteres e outro vértice com os
  // l-1 últimos caracteres, e adiciona uma aresta direcionada
  // entre esses vértices
  // implementar...
  
  // Balanceia o grafo, se necessário
  balanceia(G, IDA, ini_id, fim_id);
  
  return G;
}

// Considera que existem no máximo 2 vértices semi-balanceados
// e adiciona aresta falsa com id IDA entre os vértices de ids
// ini_id e fim_id
int balanceia(grafo G, int IDA, int *ini_id, int *fim_id) {
  int _DEBUG = 0;
  vertice semi_u = NULL, semi_v = NULL;
  for (no n = primeiro_no(vertices(G)); n; n = proximo(n)) {
    vertice v = conteudo(n);
    int ge = grau_entrada(v);
    int gs = grau_saida(v);
    
    if (ge == gs + 1) {
      semi_u = v;
      _DEBUG++;
    }
    else if (ge == gs - 1) {
      semi_v = v;
      _DEBUG++;
    }
    else if (ge != gs) {
      printf("[ERRO] Impossível balancear o grafo. Reporte este problema ao professor...\n");
      exit(1);
    }
  }
  if (_DEBUG != 0 && _DEBUG != 2) {
    printf("[ERRO] Impossível balancear o grafo. Reporte este problema ao professor...\n");
    exit(1);
  }
  if (semi_u && semi_v) {
    *ini_id = vertice_id(semi_u);
    *fim_id = vertice_id(semi_v);
    adiciona_aresta(IDA, *ini_id, *fim_id, G);
    return 1;
  }
  return 0;
}

// Constrói um fragmento de DNA com base numa lista de vértices T
// que representa uma trilha Euleriana obtida no grafo do spectrum.
// O inteiro l indica o tamanho dos mers (cada vértice do grafo
// representa um (l-1)-mer) e os inteiros ini_id e fim_id são os
// ids dos vértices da aresta falsa incluída no balanceamento do
// grafo, caso tenho ocorrido (do contrário, devem estar zerados).
char *reconstroi_DNA(lista T, int l, int ini_id, int fim_id) {
  char *fragmento = (char *) malloc(sizeof(char) * MAX_DNA);
  
  // ajusta caso tenha sido balanceado: rotaciona a trilha T
  // de modo que inicie no vértice de id fim_id.
  if (ini_id && fim_id) {
    no n = primeiro_no(T);
    while ((vertice_id(conteudo(n)) != ini_id) &&
           (vertice_id(conteudo(proximo(n))) != fim_id))
      n = proximo(n);
    rotaciona(T, proximo(n));
  }
  
  // implementar...
  
  return fragmento;
}

// Imprime a diferença entre dois fragmentos de DNA
// s e r.
void imprime_diferenca(char *s, char *r) {
  // implementar...
}
