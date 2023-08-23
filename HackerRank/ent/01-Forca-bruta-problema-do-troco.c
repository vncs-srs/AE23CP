/*Implemente a solução do problema do troco (conforme apresentado em sala de aula) 
utilizando a estratégia de força-bruta.

Input Format

A primeira linha deve conter o valor do troco. A segunda linha deve conter a quantidade 
de moedas, que representará o tamanho do vetor que deverá ser lido logo em sequência.

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
5

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
8*/

#include <stdio.h>
#include <stdlib.h>

void troco(int valor,int moedas[],int n)
{
    int cont=0,i;
    for (i = 0; i < n; i++)
    {
        cont;
        while (valor >= moedas[i])
        {
            valor -= moedas[i];
            cont++;
        }

    }
    printf("%d\n",cont);
}

int main(void)
{
    int valor,n;
    scanf("%d %d",&valor,&n);
    int moedas[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&moedas[i]);
    }
    
    troco(valor,moedas,n);
    
    return 0;
}