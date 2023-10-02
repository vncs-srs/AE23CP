/*
Submissions
Leaderboard
Discussions
A soma de dois números inteiros pode ser feita através de sucessivos incrementos, por exemplo, 7 + 4 = (++(++(++(++7)))) = 11. Implemente uma função, utilizando a estratégia de divisão e conquista, que calcule a soma entre dois números naturais, através de incrementos, utilizando recursão.

Input Format

Na primeira linha deve ser lido um número inteiro N referente a quantidade de leituras de entradas.

Para cada uma das N próximas linhas, ler dois números inteiros (a e b)

Constraints

.

Output Format

Em cada uma das N linhas, imprimir o resultado da soma dos respectivos números inteiros.

Sample Input 0

5
1 2
6 7
8 6
0 20
23 6
Sample Output 0

3
13
14
20
29*/

#include <stdio.h>
#include <stdlib.h>

int soma(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        int aux = a & b;
        int som = a ^ b;
        return soma(som, aux << 1);
    }
}

int main(void) 
{
    int n, a, b;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &a, &b);
        printf("%d\n", soma(a, b));
    }
    return 0;
}