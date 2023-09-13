/*
Considere n itens a serem levados para uma viagem, dentro de uma mochila de capacidade b. Cada item x_j tem um peso a_j e um valor c_j. Implemente uma função, utilizando força-bruta, que calcule o valor máximo de objetos que podem ser carregados dentro da mochila.

Input Format

Na primeira linha deve ser lido um número inteiro que represente a capacidade da mochila.

Na próxima linha, deve ser lido um outro número (N) referente à quantidade de objetos disponíveis.

Em seguida, nas N linhas restantes devem ser lidos o peso e o valor (logo em sequência) de cada objeto.

Constraints

.

Output Format

O valor máximo de objetos que a mochila possa carregar.

Sample Input 0

50
3
10 60
20 100
30 120
Sample Output 0

220
Sample Input 1

40
6
5 25
20 30
10 60
15 30
25 100
30 80
Sample Output 1

185
*/
#include <stdio.h>
#include <stdlib.h>

static int mochila_fb(int *custo,int *peso, int n, int capacidade, int i, int max)
{
    int c1,c2;
    if (i>= n)
    {
        if (capacidade<0)
        {
            return 0;
        }
        else
        {
            return max;
        } 
    }
    else
    {
        c1 = mochila_fb(custo,peso,n,capacidade,i +1,max);
        c2 = mochila_fb(custo,peso,n,capacidade - peso[i],i+1,max+custo[i]);

        return (c1>c2) ? c1 : c2;
    }
}
int mochila(int *custo,int *peso, int n, int capacidade)
{
    return mochila_fb(custo,peso,n,capacidade,0,0);
}
int main() 
{
    int i,n,capacidade;
    int *peso,*custo;

    scanf("%d",&capacidade);
    scanf("%d",&n);

    custo = malloc(sizeof(int) * n);
    peso = malloc(sizeof(int) * n);

    for ( i = 0; i < n; i++)
    {
        scanf("%d %d",&peso[i],&custo[i]);
    }
    printf("%d",mochila(custo,peso,n,capacidade));
    
    return 0;
}
