/*******************************************
 * Implementação de biblioteca para grafos.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//---------------------------------------------------------
// getters:

int vertice_id(vertice v) {
  return v->id;
}
char* vertice_rotulo(vertice v) {
  return v->rotulo;
}
int vertice_particao(vertice v) {
  return v->particao;
}
int custo(vertice v) {
  return v->custo;
}
int estado(vertice v) {
  return v->estado;
}
vertice pai(vertice v) {
  return v->pai;
}
lista fronteira_entrada(vertice v) {
  return v->fronteira_entrada;
}
lista fronteira_saida(vertice v) {
  return v->fronteira_saida;
}
int aresta_id(aresta e) {
  return e->id;
}
vertice vertice_u(aresta e) {
  return e->u;
}
vertice vertice_v(aresta e) {
  return e->v;
}
int grafo_id(grafo G) {
  return G->id;
}
lista vertices(grafo G) {
  return G->vertices;
}
lista arestas(grafo G) {
  return G->arestas;
}

//---------------------------------------------------------
// funcoes para construcao/desconstrucao do grafo:

// cria grafo vazio e o retorna
grafo cria_grafo(int id) {
  grafo G = (grafo) malloc(sizeof(t_grafo));

  if (!G)
    exit(_ERRO_MALLOC_);

  G->vertices = cria_lista();
  G->arestas = cria_lista();

  return G;
}

// destroi grafo G (desaloca toda a memoria)
void destroi_grafo(grafo G) {
  while(!vazio(arestas(G))){
       aresta a = desempilha(arestas(G));
       remove_aresta(a->id, G);
   }

   while(!vazio(vertices(G))){
       vertice v = desempilha(vertices(G));
       remove_vertice(v->id, G);
   }
   
   free(G);
}

// cria novo vertice com id <id>, rotulo <rotulo>, particao <particao>
// e adiciona ao grafo G
void adiciona_vertice(int id, char* rotulo, int particao, grafo G) {
   vertice v = (vertice) malloc(sizeof(t_vertice));
    
    if(!v)
        exit(_ERRO_MALLOC_);

    v->id = id;
    v->fronteira_entrada = cria_lista();
    v->fronteira_saida = cria_lista();

    strcpy(v->rotulo, rotulo);
    
    v->particao = particao;
    
    empilha(v, vertices(G));
}

// remove vertice com id <id> do grafo G e o destroi
// [deve remover e destruir tambem as arestas incidentes]
void remove_vertice(int id, grafo G) {
   vertice v = busca_chave_int(id, vertices(G), (int_f_obj) vertice_id);
  
  while(vazio(v->fronteira_entrada) == 0) { 
    aresta a = desempilha(fronteira_entrada(v));
    remove_aresta(a->id, G);
  }
  
  while(vazio(v->fronteira_saida) == 0) { 
    aresta a = desempilha(fronteira_saida(v));
    remove_aresta(a->id, G);
  }

  free(v);
}

// cria aresta com id <id> incidente a vertices com ids
// <u_id> e <v_id> e adiciona ao grafo G
void adiciona_aresta(int id, int u_id, int v_id, grafo G) {   
   aresta a = (aresta) malloc(sizeof(aresta));
       
    if(!a)
        exit(_ERRO_MALLOC_);

    a->id = id;
    a->u = busca_chave_int(u_id, vertices(G), (int_f_obj) vertice_id); 
    a->v = busca_chave_int(v_id, vertices(G), (int_f_obj) vertice_id);
    
    empilha(a, arestas(G));
    empilha(a, fronteira_saida(a->u));
    empilha(a, fronteira_entrada(a->v));   
}

// remove aresta com id <id> do grafo G e a destroi
void remove_aresta(int id, grafo G) {
    aresta a = busca_chave_int(id, arestas(G), (int_f_obj) aresta_id);
    
    a->id = 0;
    a->u = NULL;
    a->v = NULL;

    free(a);   
}
//---------------------------------------------------------
// funcoes para operacoes com o grafo pronto:

// calcula e devolve o grau do vertice v
int grau_entrada(vertice v) {
  int d_v = 0;
  for (no n = primeiro_no(fronteira_entrada(v)); n; n = proximo(n))
    ++d_v;
  return d_v;
}
int grau_saida(vertice v) {
  int d_v = 0;
  for (no n = primeiro_no(fronteira_saida(v)); n; n = proximo(n))
    ++d_v;
  return d_v;
}

// imprime o grafo G
void imprime_grafo(grafo G) {
  printf("%d\n", grafo_id(G));
  printf("\nVertices: ");
  imprime_lista(vertices(G), (void_f_obj) imprime_vertice);
  printf("\nArestas: ");
  imprime_lista(arestas(G), (void_f_obj) imprime_aresta);
  printf("\n");
  printf("\nEstrutura:\n");
  imprime_lista(arestas(G), (void_f_obj) imprime_estrutura_aresta);
}

// imprime o vertice v
void imprime_vertice(vertice v) {
  printf("(id:%d, rotulo:%s, grau_entrada:%d, fronteira_entrada:{ ", vertice_id(v), vertice_rotulo(v), grau_entrada(v));
  imprime_lista(fronteira_entrada(v), (void_f_obj) imprime_aresta);
  printf("}, grau_saida:%d, fronteira_saida:{ ", grau_saida(v));
  imprime_lista(fronteira_saida(v), (void_f_obj) imprime_aresta);
  printf("})");
}

// imprime a aresta e
void imprime_aresta(aresta e) {
  int u_id = vertice_id(vertice_u(e));
  int v_id = vertice_id(vertice_v(e));
  printf("(id:%d {%d,%d})", aresta_id(e), u_id, v_id);
}

// imprime apenas a estrutura da aresta e
void imprime_estrutura_aresta(aresta e) {
  char *u_rot = vertice_rotulo(vertice_u(e));
  char *v_rot = vertice_rotulo(vertice_v(e));
  int u_id = vertice_id(vertice_u(e));
  int v_id = vertice_id(vertice_v(e));
  printf("%d:%s > %d:%s\n", u_id, u_rot, v_id, v_rot);
}
