struct kdtree {
	int ponto[K];
	struct kdtree *esq, *dir;
};
typedef struct kdtree kdTree;

kdTree *CriaNo(int pontos [N][K], int meio) {
	kdTree *no;
	no = (kdTree*)malloc(sizeof(kdTree));
	no->esq=NULL;
	no->dir=NULL;
	no->ponto[0] = pontos[meio][0];
	no->ponto[1] = pontos[meio][1];
	
	return no;
}

void exibeh (kdTree *A) {
	static int x = -1;
	int i;
	if (A != NULL) {
		x++;
		exibeh (A->dir);
		for (i=0; i<5*x; i++) printf(" ");
		printf("(%d, %d) \n",A->ponto[0],A->ponto[1]);
		exibeh (A->esq);
		x--;
	}
}

int distEuc (kdTree *no, int ponto[]) {
	return (int)sqrt(pow(ponto[0] - no->ponto[0], 2) + pow(ponto[1] - no->ponto[1], 2));
}

void inserirVet (kdTree *raiz, int proximos[N][K]) {
	proximos[qtd][0] = raiz->ponto[0];
	proximos[qtd][1] = raiz->ponto[1];
	qtd+=1;
}
