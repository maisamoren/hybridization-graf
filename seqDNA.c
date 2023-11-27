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
    
  // implementar o resto...

  grafo G = cria_grafo();


  
  return 0;
}
