// Compilar com -fopenmp
// O Programa aloca aproximadamente 4gb de memoria ram fixa ate o fim da execução, tenha isso em mente antes de rodar.
// Integrantes: Gustavo Lopes dos Santos / GitHub - @HanniGust
// 				Lucas Vinicius Lima Braga De Amorin / GitHub - @lucasvlbamorim

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <string.h>

main()
{
    // Aloca 10^9.
    int *p = (int *)malloc(1000000000 * sizeof(int));
    int i, j, n;
    int z = 0;
    // n = numero cujo vai ser feito todos nPrimos até n;
    // p[] = Numeros primos; SE P = 0 ( TODOS NÃO PRIMOS menos o número 1 ), SE P = 1 ( TODOS PRIMOS )
    // i = cont 1;
    // j = cont 2;

    printf("\nDigite um numero n até 10^9: ");
    scanf("%d", &n);
    printf("\nDigite 0 para a função Time ('Imprime o tempo de execução do programa.'). ");
    printf("\nDigite 1 para a função List ('Imprime todos os números primos até n.'). ");
    printf("\nDigite 2 para a função All  ('Imprime o tempo de execução do programa e todos os números primos até n.'): ");
    scanf("%d", &z);

    double start = omp_get_wtime(); // Inicia o contador de tempo do programa
    for (i = 1; i <= n; i++)
    { // Começo assumindo que todos os numeros de 1 até n são números primos
        p[i] = 1;
    }
    p[1] = 0;

    ///*
    // Começamos a fazer a verificação dos não primos.
    // Iniciamos com o valor de i=2 já q 1 não é primo,  i*i tem quer ser menor ou igual a n, se não fariamos a verificação de números superior a n até o infinito.
    for (i = 2; i * i <= n; i++)
    {                    // Na execução de um n = 10, esse for só vai executar duas vezes, onde i = 2 e i = 3, 2*2, 2*3, executando no proximo for as instruções
#pragma omp parallel for //
        for (j = i * i; j <= n; j = j + i)
        { // Estamos removendo os múltiplos a partir de i*i, por exemplo, assumindo a primeira linha do for
            // j = i*i (j=2*2) 2*2 = 4, a raiz de 4 é 2, já que o número primo não tem raiz quadrada, pois as raizes quadrdas dos numeros primos sao irracionais
            if (p[j] == 1)
            {             // Logo, removemos os números não primos da lista dos números primos, deixando os números primos com valor de p[i] == 1
                p[j] = 0; // e os não primos como p[i] == 0
            }
            // Podemos imprimir a execução de onde está ocorrendo a verificação dos não primos em cada thread usando a função abaixo
            // printf("T-%d|",omp_get_thread_num());
        }
    }
    //*/
    // Em ordem de execução, para uma exemplificar, entramos com n = 10, 10 passa pelo segundo for, onde, 2*2, 2*3, 2*4 e 2*5 são verificados, retornando os valores
    // 4, 6, 8 e 10, passa pelo primeiro for onde i = 2, e então novamente pelo segundo for, onde 3*3 = 9, e após o primeiro for, i = 3, assim, obtendo o valor de todos
    // os não primos de 2 até 10 ( lembrando que o 1 não é verificado ).

    double end = omp_get_wtime(); // Termina o contador de tempo do programa

    // /*
    if (z == 0)
    {
        printf("\nTempo de exec = %.6f s\n", end - start);
    }
    else if (z == 1)
    {
        printf("\n");
        // Imprime Os Primos
        for (i = 2; i <= n; i++)
        {
            if (p[i] == 1)
            {
                printf("%d\t ", i);
            }
        }
    }
    else if (z == 2)
    {
        printf("\n");
        // Imprime Os Primos
        for (i = 2; i <= n; i++)
        {
            if (p[i] == 1)
            {
                printf("%d\t ", i);
            }
        }
        printf("\nTempo de exec = %.6f s\n", end - start);
    }

    free(p);
}