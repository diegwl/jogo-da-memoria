#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "unistd.h"
#include <locale.h>

#define ROWS 4
#define COLS 4

int jogar = 1, i, j, k, l, matriz[ROWS][COLS] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, pontos = 0, erros = 0, acertos[8], contacertos;


void gerarMatriz(int matriz[ROWS][COLS]) {
    int numero, vetor[8], col, row;
    srand(time(NULL));
    
    for (i=0; i<=7;i++){
    	numero = rand() % 10;
    	
    	for (j=-1; j<=7; j++){
		if (vetor[j] == numero || numero == 0){
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
	printf("--- JOGO DA MEMORIA ---\n");
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
	system("cls"); 
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
                printf("\t%d", num);
            } else {
                printf("\t%c", caracter);
            }
        }
        printf("\n");
    }
}

bool verifica_acerto(int num){
	for (i =0;i<=7;i++) {
		if (num == acertos[i]) {
			return false;
		}
	}
	return true;
}

void verificar_jogada(){
	

	int linha1, linha2,coluna1,coluna2;
	
	
	
	printf("Informe a linha e a coluna do primeiro n�mero: ");
	
	scanf("%d %d",&linha1,&coluna1);
	
	printf("Informe a linha e a coluna do segundo n�mero: ");
	
	scanf("%d %d", &linha2, &coluna2);
	
	bool valida_acerto = verifica_acerto(matriz[linha1][coluna1]);
	
	if (matriz[linha1][coluna1] == matriz[linha2][coluna2] && (coluna1 != coluna2 || linha1 != linha2) && valida_acerto) {
	
	printf("\a");
	printf("Parabéns, você acertou.\n");
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
	printf("Os n�meros n�o s�o iguais. Tente novamente.\n"); 
	}
	sleep(5);
}

bool ganhou(){
	return (contacertos==8);
}

bool perdeu(){
	return (erros==10);
}

void salvarPontuacao(int pontuacao) {
    FILE *arquivo;
    arquivo = fopen("pontuacao.txt", "w"); 

    if (arquivo == NULL) {
        printf("pontua��o.\n");
        return;
    }

    fprintf(arquivo, "%d", pontuacao);

    fclose(arquivo); 
}
	
int main(){
	setlocale(LC_ALL, "Portuguese");
	bool ganhouVar, perdeuVar;
	system ("color 0D");
	while(jogar == 1){
		ganhouVar = false;
		perdeuVar = false;
		gerarMatriz(matriz);
		mostrarMatriz();
		while(!ganhouVar && !perdeuVar){
			mostrar_matriz_escondida();
			verificar_jogada();
			perdeuVar = perdeu();
			ganhouVar = ganhou();
		}
		if(perdeuVar == true){
			system("cls");
			printf("----------------------------------------\n");
			printf("  ________\n");
			printf(" /  _____ \\\n");
			printf("|  |     |  |\n");
			printf("|  | RIP |  |\n");
			printf("|  |_____|  |\n");
			printf("|__________|\n");
			printf("   Game Over\n----------------------------------------");
			sleep(5);

		} else if (ganhouVar == true){
			system("cls");
			printf("         VOCE GANHOU PARABENS!!!\n");
			printf("----------------------------------------\n");
			printf("          .-=========-.               \n");
			printf("          \\'-=======-'/               \n");
			printf("          _|   .=.   |_               \n");
			printf("         ((|  {{1}}  |))              \n");
			printf("          \\|   /|\\   |/               \n");
			printf("           \\__ '`' __/                \n");
			printf("             _`) (`_                  \n");
			printf("           _/_______\\_                \n");
			printf("          /___________\\\n----------------------------------------");
			sleep(5);
		}
		system("cls");
		salvarPontuacao(contacertos*10);
		printf("Sua pontuação foi salva! você fez %d pontos!\n", contacertos*10);
		sleep(3);
		system("cls");
		printf("Digite 1 para jogar novamente ou 0 para sair:\n");
		scanf("%d", &jogar);
		system("cls");
		
		for(
		i=0; i<ROWS; i++){
    	    for(j=0; j<COLS; j++){
    	     matriz[i][j] = 0;
		    }
		 printf("\n");
	    } 

		pontos = 0;
		erros = 0;
		
		for (i =0;i<=7;i++){
			acertos[i] = 0;
		}

		contacertos = 0;
	}
	return 0;
}
