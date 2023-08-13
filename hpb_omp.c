/*
    Universidad del Valle de Guatemala
    Computacion Paralela
    Christopher Garcia 20541
    · Ejercicio 2
*/

// Se importan librerias
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void hbd_msg(void);

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
    hbd_msg();

    return 0;
}

void hbd_msg(void){
    // Obtención de número de thread y cantidad de threads
    int thread_num = omp_get_thread_num();
    int cant_threads = omp_get_num_threads();
    if (thread_num % 2 == 0){
        printf("Saludos del hilo %d\n", thread_num);
    } else {
        printf("Feliz cumpleaños número %d\n", cant_threads);
    }
}