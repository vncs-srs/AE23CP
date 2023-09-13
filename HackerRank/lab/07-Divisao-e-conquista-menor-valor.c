/*
Dona Lurdes é responsável pelo gerenciamento de uma sala de aula, onde ela deve alocar a maior quantidade de aulas possíveis durante o expediente. No entanto, fazer essa tarefa de forma otimizada e manualmente pode ser uma tarefa muito difícil, pois muitas disciplinas podem ter horários que sobrepõem entre elas.

Implemente uma função, por meio da estratégia gulosa, para que a maior quantidade possíveis de aula possam ser alocadas na sala.

Input Format

A primeira linha deve ser um número inteiro n referente à quantidade de atividades. Para cada uma das próximas n linhas devem ser lidos os horários de início e de fim para cada atividade.

Constraints

As aulas devem ser ordenadas crescentemente pelo horário de término.

Output Format

A primeira linha apresenta a mensagem “Aulas alocadas:” seguida das aulas (posição no vetor) que foram alocadas na respectiva sala.

Sample Input 0

11
1 4
3 5
0 6
5 7
3 8
5 9
6 10
8 11
8 12
2 13
12 14
Sample Output 0

Aulas alocadas: 0 3 7 10*/

#include <stdio.h>
#include <stdlib.h>

#define min(a,b) (a<b) ? a : b

int menorDQ(int *vetor,int ini,int fim)
{
    if (fim - ini <= 1)
    {
        return min(vetor[ini],vetor[fim]);
    }
    else
    {
        int meio = (ini + fim)/ 2;
        int esquerda = menorDQ(vetor,ini,meio);
        int direita = menorDQ(vetor,meio+ 1,fim);

        return min(esquerda,direita);
    }
    
}

int main() 
{
    int i, n, *vetor;

    scanf("%d",&n);

    vetor = (int*) malloc(sizeof(int) * n);

    for ( i = 0; i < n; i++)
    {
        scanf("%d",&vetor[i]);
    }

    printf("%d",menorDQ(vetor,0, n-1));
    
 
    return 0;
}