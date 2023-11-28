/*******************************************
 * Simulação de sequenciamento de DNA.
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

// ./seqDNA < <entrada.in>
int main() {
  
  // le fragmento do DNA e tamanho dos mers
  char *s = (char *) malloc(sizeof(char)*MAX_DNA);
  int l;
  scanf("%s %d", s, &l);
  
  // obtem spectrum
  lista l_mers = spectrum(s, l);
  embaralha_spectrum(l_mers); // para simulação mais realista
  imprime_spectrum(l_mers);
    
  // constroi grafo direcionado
  grafo G = constroi_grafo_spectrum(l_mers, l, 1, 1);

  // printf("%c\n", conteudo(topo(l_mers)));
  
  // encontra a trilha euleriana e imprime
  // lista T = trilha_euleriana(G);
  // imprime_trilha(T);

  // constroi um fragmento de DNA e imprime
  // r = reconstroi_DNA (T, l, ???, ???);

  // compara o fragmento r com o s e imprime a porcentagem
  // imprime_diferença (s, r);
  
  return 0;
}
