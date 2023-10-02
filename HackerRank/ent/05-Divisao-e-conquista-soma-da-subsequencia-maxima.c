/*Seja um arranjo composto por números inteiros, podendo ser positivos e/ou negativos. 
A subsequência máxima é aquela que tem o maior valor de soma entre todos os os seus elementos.

Por exemplo, dada a sequência a seguir: .

A subsequência máxima é , pois, de todas as subsequências possíveis, essa foi a que registrou 
a maior soma entre os seus elementos (43).

Implemente, utilizando a estratégia divisão-e-conquista, uma função que retorne o somatório 
da subsequência máxima.

Input Format
Na primeira linha deve ser lido um número inteiro (n).
Na segunda linha deve ser lida um vetor de números inteiros de tamanho n.

Constraints
.
Output Format
Somatório da subsequência máxima.

Sample Input 0
14
10 -3 -30 20 -3 -16 -23 15 23 -7 12 -4 -25 6

Sample Output 0
43

Sample Input 1
1
1

Sample Output 1
1*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int maior(int  a, int b)
{
    return(( a > b) ? a : b);
}

int maior3(int a, int b, int c)
{
    return(maior(maior(a,b),c));
}
int maiorsoma(int a[], int meio, int inicio, int fim)
{
    int soma = 0;
    int somaesquerda = INT_MIN;

    int indice = meio;

    while(indice >= inicio)
    {
        soma = soma + a[indice];
        indice--;

        if(soma > somaesquerda)
            somaesquerda = soma;
    }

    soma = 0;
    indice = meio;

    int somadireita = INT_MIN;

    while(indice <= fim)
    {
        soma = soma + a[indice];
        indice++;

        if(soma > somadireita)

            somadireita = soma;
    }
    return(maior3(somaesquerda + somadireita - a[meio], somaesquerda, somadireita));
}

int subseqmaior(int a[], int inicio, int fim)
{
    if(inicio > fim)
        return INT_MIN;

    if(inicio == fim)
        return(a[inicio]);

    int meio = (inicio + fim) / 2;

    return(maior3(subseqmaior(a, inicio, meio - 1), subseqmaior(a, meio + 1, fim), maiorsoma(a, meio, inicio, fim)));
}

int main(void) 
{
    int n;

    scanf("%d", &n);

    int x[n];
    int r;

    for(int i = 0; i < n; i++)
        scanf("%d", &x[i]);

    r = subseqmaior(x, 0, n - 1);

    printf("%d", r);

    return 0;
}
