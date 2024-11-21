#include<stdio.h>
#include<stdlib.h>
#include<conio2.h>
#include<math.h>

#define K 2
#define N 11
#define MAX_VALUE 41
int qtd = 0;

#include "tad.h"

void gerarPontos (int pontos[N][K]) {
	int i, j;
	
	for (i=0; i<N; i++)
		for (j=0; j<K; j++)
			pontos[i][j] = rand() % MAX_VALUE;
}

void exibePontos (int pontos[N][K]) {
	int i;
	
	for (i=0; i<N && pontos[i][0] >= 0 && pontos[i][1] < MAX_VALUE; i++)
		printf("[%d, %d] ", pontos[i][0], pontos[i][1]);
}

void ordenar (int pontos[N][K], int d, int ini, int fim) {
	int aux[K], a, qtde = fim-ini;
	while (qtde>0) {
		for (a=ini; a<fim; a++)
			if (pontos[a][d] > pontos[a+1][d]) {
				aux[0] = pontos[a][0];
				aux[1] = pontos[a][1];
				pontos[a][0] = pontos[a+1][0];
				pontos[a][1] = pontos[a+1][1];
				pontos[a+1][0] = aux[0];
				pontos[a+1][1] = aux[1];
			}
		qtde--;
	}
}

void insereBal (kdTree **raiz, int pontos [N][K], int ini, int fim, int n) {
	int d, meio;
	
	if (ini <= fim) {
		d = n%K;
		ordenar(pontos, d, ini, fim);	
		meio = (int)(ini+fim)/2;
		*raiz = CriaNo(pontos, meio);
		insereBal(&(*raiz)->esq, pontos, ini, meio-1, n+1);
		insereBal(&(*raiz)->dir, pontos, meio+1, fim, n+1);
	}
}

void gerarKDTree (kdTree **raiz, int pontos [N][K]) {
	 insereBal (&*raiz, pontos, 0, N-1, 0);
}

void buscarProx (kdTree *raiz, int ponto[], int raio, int proximos[N][K]) {
	if (raiz != NULL) {
		if (distEuc(raiz, ponto) <= raio)
			inserirVet(raiz, proximos);
		buscarProx(raiz->esq, ponto, raio, proximos);
		buscarProx(raiz->dir, ponto, raio, proximos);
	}
}

void Executar () {
	kdTree *raiz;
	int pontos[N][K], ponto[K], raio, proximos[N][K];
	
	ponto[0] = 12; ponto[1] = 4; raio=15;
	gerarPontos(pontos);
	printf("Pontos gerados: \n");
	exibePontos(pontos);
	printf("\n\nArvore: \n");
	gerarKDTree(&raiz, pontos);
	
	buscarProx(raiz, ponto, raio, proximos);
	exibeh(raiz);
	printf("\n\n");
	if (qtd > 0) {
		printf("\nPontos encontrados dentro do raio de %d unidades para (%d, %d): \n", raio, ponto[0], ponto[1]);
		exibePontos(proximos);
	}
	else
		printf("\nNao foram encontrados pontos proximos a (%d, %d)\n", ponto[0], ponto[1]);
}

int main (void) {
	srand(time(NULL));
	Executar();
	return 0;
}
