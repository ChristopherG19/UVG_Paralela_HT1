/*
    Universidad del Valle de Guatemala
    Computacion Paralela
    Christopher Garcia 20541
    · Ejercicio 1
*/

// Se importan librerias
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void hello_world(void);

// Main
int main(int argc, char *argv[])
{
    // Numero de threads y verificacion de que se envia parametro
    int thread_count = 10;
    if (argc > 1){
        thread_count = strtol(argv[1], NULL, 10);
    }

    // Paralelizacion al metodo creado
    #pragma omp parallel num_threads(thread_count)
    hello_world();

    return 0;
}

void hello_world(void){
    int thread_num = omp_get_thread_num();
    int cant_threads = omp_get_num_threads();
    printf("Hello from thread %d of %d !\n", thread_num, cant_threads);
}