/*Dada uma carreta de reboque com espaço útil de comprimento l e cargas de comprimento m e n, 
supondo que todas têm a mesma largura e altura. Para evitar desperdício, o preenchimento dessa 
carreta deve ser maximizado, isto é, deve sobrar o menor espaço possível caso não seja possível
a ocupação total. Implemente um algoritmo guloso que minimize a quantidade de espaço ocioso na
carreta determinando a quantidade de cada uma das cargas.

Input Forma
Devem ser lidos 3 números inteiros em sequência: l (comprimento da carreta), m (comprimento da carga 1) 
e n (comprimento da carga 1).

Constraints
.
Output Format
Na primeira linha deve ser impressa a quantidade de carga 1 que deve ser colocada na carreta.
Na segunda linha deve ser impressa a quantidade de carga 2 que deve ser colocada na carreta.
Na terceira linha deve ser impresso o espaço que sobrou na carreta.

Sample Input 0
23 8 5

Sample Output 0
1
3
0

Explanation 0
Para o preenchimento ótimo, foram necessárias 1 unidade da carga 1 (comprimento 8) e 3 unidades 
da carga 2 (comprimento 5).
O espaço ocioso é 0, ou seja, é possível preencher toda carreta com unidades da carga 1 e 2.

Sample Input 1
28 8 3

Sample Output 1
0
9
1

Sample Input 2
29 2 3

Sample Output 2
13
1
0*/

#include <stdio.h>
#include <stdlib.h>

void capacidadeCarga(int l,int m, int n)
{



}

int main(void)
{
    int l,m,n;

    scanf("%d %d %d",&l,&m,&n);

    capacidadeCarga(l,m,n);

    return 0;
}


