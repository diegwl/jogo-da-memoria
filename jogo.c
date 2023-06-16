#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "unistd.h"

#define ROWS 4
#define COLS 4

int matriz[4][4] = {{1, 2, 3, 4}, {1, 2, 3, 4}, {5, 6, 7, 8}, {5, 6, 7, 8}}, pontos = 0, erros = 0, jogar_novamente = 1, acertos[8] = {2, 7};

void mostrar_matriz_escondida(){
    int caracter = 35;
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLS; j++)
        {
            int acerto = 0;
            int num = matriz[i][j];
            for (int k = 0; k < 8; k++)
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

int main(){
    mostrar_matriz_escondida();
    return 0;
}