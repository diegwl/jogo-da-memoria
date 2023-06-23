#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "unistd.h"

#define ROWS 4
#define COLS 4

int i, j, k, l, matriz[ROWS][COLS] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, pontos = 0, erros = 0, jogar_novamente = 1, acertos[8],contacertos, erros;

void gerarMatriz(int matriz[ROWS][COLS]) {
    int numero, vetor[8], col, row;
    srand(time(NULL));
    
    for (i=0; i<=7;i++){
    	numero = rand() % 10;
    	
    	for (j=-1; j<=7; j++){
		if (vetor[j] == numero){
			numero = rand() % 10;
			j = -1;
		}
		}
		vetor[i] = numero;
		}
	
	for (i=0; i<=7;i++){
		
		row = rand() % 4;
		col = rand() % 4;
		for (j = 0; j < ROWS; j++) {
        	for (k = 0; k < COLS; k++) {
				if (matriz[row][col] != 0){
					row = rand() % 4;
					col = rand() % 4;
					j = 0;
					k = 0;
				}
			}
		}
		matriz[row][col] = vetor[i];
		
		row = rand() % 4;
		col = rand() % 4;
		for (j = 0; j < ROWS; j++) {
        	for (k = 0; k < COLS; k++) {
				if (matriz[row][col] != 0){
					row = rand() % 4;
					col = rand() % 4;
					j = 0;
					k = 0;
				}
			}
		}
		matriz[row][col] = vetor[i];
	}
}

void mostrarMatriz(){
        for(
		i=0; i<ROWS; i++){
    	    for(j=0; j<COLS; j++){
    	     printf("%d\t", matriz[i][j]);
		    }
		 printf("\n");
	    }
	  sleep(5); 
	  system("cls"); 
    } 

void mostrar_matriz_escondida(){
    int caracter = 35;
    for (i=0; i<ROWS; i++){
        for (j=0; j<COLS; j++)
        {
            int acerto = 0;
            int num = matriz[i][j];
            for (k = 0; k < 8; k++)
            {
                if (num == acertos[k])
                {
                    acerto = 1;
                }
            }
            if (acerto == 1){
                printf(" %d ", num);
            } else {
                printf(" %c ", caracter);
            }
        }
        printf("\n");
    }
}

bool verifica_acerto(num){
	for (i =0;i<=7;i++) {
		if (num == acertos[i]) {
			return false;
		}
	}
	return true;
}

void verificar_jogada(){
	

	int linha1, linha2,coluna1,coluna2;
	
	
	
	printf("Informe a linha e a coluna do primeiro número: ");
	
	scanf("%d %d",&linha1,&coluna1);
	
	printf("Informe a linha e a coluna do segundo número: ");
	
	scanf("%d %d", &linha2, &coluna2);
	
	bool valida_acerto = verifica_acerto(matriz[linha1][coluna1]);
	
	if (matriz[linha1][coluna1] == matriz[linha2][coluna2] && (coluna1 != coluna2 || linha1 != linha2) && valida_acerto) {
	
	printf("\a"); 
	contacertos++;
	for (i =0;i<=7;i++){
		if (acertos[i]==0){
			acertos[i] = matriz [linha1][coluna1];
			i=8;
		}
	}
	
	} 
	else {
	erros++;
	printf("Os números não são iguais. Tente novamente.\n");
	    
	}
}

bool ganhou(){
	return (contacertos==8);
}

bool perdeu(){
	return (erros>10);
}

void salvarPontuacao(int pontuacao) {
    FILE *arquivo;
    arquivo = fopen("pontuacao.txt", "w"); 

    if (arquivo == NULL) {
        printf("pontuação.\n");
        return;
    }

    fprintf(arquivo, "%d", pontuacao);

    fclose(arquivo); 
}

bool novoJogo(){
    	char opcao;
		fflush(stdin); 
    	printf("Deseja jogar novamente S/N?");
    	scanf("%c",&opcao);
    	    if(opcao=='S' || opcao=='s'){
    	   	return true;
		    } 
			else{
				return false;
			}
	}
	
int main(){
	bool jogar = true;
	while(jogar){
		bool ganhouVar = false;
		bool perdeuVar = false;
		gerarMatriz(matriz);
		mostrarMatriz();
		while(!ganhouVar && !perdeuVar){
			mostrar_matriz_escondida();
			verificar_jogada();
			perdeuVar = perdeu();
			ganhouVar = ganhou();
		}
		salvarPontuacao(contacertos*10);
		jogar = novoJogo();
	}
}
