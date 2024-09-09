#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//Verifica se a posição atual é válida
//Para isso, primeiro se itera em todas as colunas anteriores
//Checando por conflitos com as rainhas já colocadas
//board[i] == col checa se há conflitos verticais
//abs(board[i] - col) == abs(i - row) checa se há conflitos diagonais
//Não há necessidade de checar conflitos horizontais já que o algoritmo só coloca uma rainha por linha
//Caso haja algum conflito, retorna false, e solveNQueens chama isSafe na próxima posição
//Caso não haja, retorna true, indicando que se pode colocar a rainha aqui
bool isSafe(int board[], int row, int col){
    for(int i = 0; i < row; i++){
        if(board[i] == col || abs(board[i] - col) == abs(i - row)){
            return false;
        }
    }
    return true;
}

//Converte índice de coluna para letra (A, B, C,...)
char convertToLetter(int col){
    return 'A' + col;
}

void printSolution(int board[], int n){
    printf("Solution: ");
    for(int i = 0; i < n; i++){
        printf("(%c, %d) ", convertToLetter(board[i]), i + 1);
    }
    printf("\n");
}

bool solveNQueens(int board[], int row, int n){
    //Quando o tabuleiro todo foi percorrido, imprime solução
    //E para o algoritmo ao encontrar primeira solução
    if(row == n){
        printSolution(board, n);
        return true;
    }

    //Roda o algoritmo isSafe em cada coluna da linha atual
    //Caso isSafe retorne true, a rainha é colocada
    //E solveNQueens é chamado recursivamente na próxima linha
    //Caso isSafe retorne false, a próxima posição é checada
    for(int col = 0; col < n; col++){
        if(isSafe(board, row, col)){
            board[row] = col;
            if(solveNQueens(board, row + 1, n)){
                return true;  //Recursão para ao encontrar solução
            }
        }
    }
    return false;  //Retorna false se nenhuma solução é encontrada
}

int main(int argc, char *argv[]){
    int n = atoi(argv[1]);
    if (n <= 0){
        printf("Tamanho inválido.\n");
        return 1;
    }

    //Aloca o tabuleiro na qual o algoritmo é executado
    int *board = (int *)malloc(n * sizeof(int));
    if(board == NULL){
        printf("Falha em alocar memória\n");
        return 1;
    }

    clock_t start = clock();

    //Roda o algoritmo em um tabuleiro tamanho n a partir da coluna 0
    solveNQueens(board, 0, n);

    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tempo para resolver: %.6f seconds\n", time_taken);

    free(board);
    return 0;
}