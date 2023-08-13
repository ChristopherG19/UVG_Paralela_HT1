/*
    Universidad del Valle de Guatemala
    Computacion Paralela
    Christopher Garcia 20541
    · Ejercicio 4
*/

// Se importan librerias
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

double cuadratic_func(double x);
double cubic_func(double x);
double sin_func(double x);
double get_h(double a, double b);
double trapezoides(double (*func)(double), double a, double b, double h, int threads);

// Se define n
int n = 10e6;

// Main
int main(int argc, char *argv[])
{
    // Numero de threads y verificacion de que se envia parametro
    double a = 1.0;
    double b = 1.0;
    int op = 0;
    int num_threads = 10;

    if (argc > 1){
        a = strtol(argv[1], NULL, 10);
        b = strtol(argv[2], NULL, 10);
        num_threads = strtol(argv[3], NULL, 10);
        op = strtol(argv[4], NULL, 10);

        if(n % num_threads != 0){
            fprintf(stderr, "Número de trapezoides no es múltiplo de número de threads\n");
        }

    }

    if(op == 1){
        double h = get_h(a, b);
        double resultado = trapezoides(cuadratic_func, a, b, h, num_threads);
        printf("Con n = %d, nuestra aproximacion\nde la integral de %f a %f es = %f\n",n,a,b,resultado);
    } else if(op == 2){
        double h = get_h(a, b);
        double resultado = trapezoides(cubic_func, a, b, h, num_threads);
        printf("Con n = %d, nuestra aproximacion\nde la integral de %f a %f es = %f\n",n,a,b,resultado);
    } else if(op == 3){
        double h = get_h(a, b);
        double resultado = trapezoides(sin_func, a, b, h, num_threads);
        printf("Con n = %d, nuestra aproximacion\nde la integral de %f a %f es = %f\n",n,a,b,resultado);
    } else {
        printf("Error");
    }

    return 0;
}

double trapezoides(double (*func)(double), double a, double b, double h, int threads){
    double sum = 0.0;
    double sumF = 0.0;
    int n_local = n/threads;
    
    #pragma omp parallel num_threads(threads)
    {
        int ID_thread = omp_get_thread_num();
        double a_local = a + ID_thread * n_local * h;
        double b_local = a_local + n_local * h;
        sumF = (func(a_local) + func(b_local)) / 2.0;

        for(int i = 1; i < n_local; i++){
            double x = a_local + i * h;
            sumF += func(x);
        }

        sumF *= h;

        #pragma omp critical
        sum += sumF;

    }
    return sum;
}

double get_h(double a, double b){
    return (b-a)/n;
}

double cuadratic_func(double x){
    return pow(x,2);
}

double cubic_func(double x){
    return 2.0 * pow(x,3);
}

double sin_func(double x){
    return sin(x);
}
