/*
Implemente a solução do problema do troco (conforme apresentado em sala de aula) utilizando método guloso.

Input Format

A primeira linha deve conter o valor do troco. A segunda linha deve conter a quantidade de moedas, que representará o tamanho do vetor que deverá ser lido logo em sequência.

Constraints

.

Output Format

Sequência de moedas que foram retornados como troco.

Sample Input 0

450
5
100
50
10
5
1
Sample Output 0

100
100
100
100
50
Sample Input 1

378
6
100
50
25
10
5
1
Sample Output 1

100
100
100
50
25
1
1
1
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int movX[] = {-1,0,1,0};
int movY[] = {0,-1,0,1};

int proximo_passo(int **mat, int l,int c,int *l_proximo,int *c_proximo)
{
    int i, menor = INT_MAX;
    int l_atual, c_atual;
    int l_melhor = *l_proximo, c_melhor = *c_proximo;

    for ( i = 0; i < 4; i++)
    {
        l_atual = *l_proximo + movX[i];
        c_atual = *c_proximo + movY[i];

        if ((l_atual >= 0) && (l_atual < l) && (c_atual >= 0) && (c_atual < c) && (menor > mat[l_atual][c_atual]))
        {
            l_melhor = l_atual;
            c_melhor = c_atual;
            menor = mat[l_atual][c_atual];
        }
        *l_proximo = l_melhor;
        *c_proximo = c_melhor;

        return menor;
    }
     
}
int percurso(int **mat, int l,int c,int l_atual,int c_atual, int custo)
{
    if ((l_atual == l -1) && (c_atual == c -1))
    {
        return custo;
    }
    else
    {
        mat[l_atual][c_atual] = INT_MAX;

        int aux = proximo_passo(mat, l, c, &l_atual,&c_atual);

        if (aux < INT_MAX)
        {
            return percurso(mat ,l,c, l_atual,c_atual,custo + mat[l_atual][c_atual]);
        }
        else
        {
            return INT_MAX;
        }
    }
    
}

int main() 
{
    int **mat, l,c,i,j,res;

    scanf("%d %d",&l,&c);

    mat = (int**) malloc(sizeof(int*) * l);
    for ( i = 0; i < l; i++)
    {
        mat[i] = (int*)malloc(sizeof(int) * c);
        for ( j = 0; j < c; j++)
        {
            scanf("%d",&mat[i][j]);
        }
    }
    res = percurso(mat,l,c,0,0,0);
    if (res < INT_MAX)
    {
        printf("%d",res);
    }
    else
    {
        printf("sem solucao");
    }


    free(mat);
    
    return 0;
}