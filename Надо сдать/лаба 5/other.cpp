#include <cstdio>
#include <cmath>
#include <cstring>
#include "other.h"

void sort(char* pcFirst, int nNumber, int size,
     void (*Swap)(void*, void*), int (*Compare)(void*, void*) )
{
    int i;
    for(i=1; i<nNumber; i++)
        for(int j=nNumber-1; j>=i; j--)
        {
            char* pCurrent = pcFirst+j*size;
            char* pPrevious = pcFirst+(j-1)*size;
            if((*Compare)( pPrevious, pCurrent ) > 0)
                (*Swap)( pPrevious, pCurrent );
        }
}

void swap_int(void* p1, void* p2)
{
    int temp = *(int*)p1;
    *(int*)p1 = *(int*)p2;
    *(int*)p2 = temp;
}

int cmp_int(void* p1, void* p2)
{
    int nResult;
    int int1 = *(int*)p1;
    int int2 = *(int*)p2;
    if (int1 < int2) {
        nResult = -1;
    } else if (int1 > int2) {
        nResult = 1;
    } else {
        nResult = 0;
    }
    return nResult;
}

void swap_double(void* p1, void* p2)
{
    double temp = *(double*)p1;
    *(double*)p1 = *(double*)p2;
    *(double*)p2 = temp;
}

int cmp_double(void* p1, void* p2)
{
    int nResult;
    double num1 = *(double*)p1;
    double num2 = *(double*)p2;
    if (num1 < num2) {
        nResult = -1;
    } else if (num1 > num2) {
        nResult = 1;
    } else {
        nResult = 0;
    }
    return nResult;
}

void swap_str(void* p1, void* p2) {
    char* temp = *(char**)p1;
    *(char**)p1 = *(char**)p2;
    *(char**)p2 = temp;
}


int cmp_str(void* p1, void* p2) {
    char* l1 = *(char**)p1;
    char* l2 = *(char**)p2;
    while ((*l1 != '\0') && ((*l1++ - *l2++) == 0));
    return (*--l1 - *--l2);
}

double add(double a, double b) {
    return a + b;
}

double sub(double a, double b) {
    return a - b;
}

double mul(double a, double b) {
    return a * b;
}

double div(double a, double b) {
    if (b == 0) {
        printf("Ошибка: деление на ноль!\n");
        return 0;
    }
    return a / b;
}

void print_max(int arr[], int size) {
    if (size == 0) {
        printf("Массив пуст.\n");
        return;
    }
    int max_elem = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] > max_elem) {
            max_elem = arr[i];
        }
    }
    printf("Максимальный элемент: %d\n", max_elem);
}

void print_min(int arr[], int size) {
    if (size == 0) {
        printf("Массив пуст.\n");
        return;
    }
    int min_elem = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] < min_elem) {
            min_elem = arr[i];
        }
    }
    printf("Минимальный элемент: %d\n", min_elem);
}

void sort_asc(int arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    printf("Массив, отсортированный по возрастанию: ");
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void sort_desc(int arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (arr[i] < arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    printf("Массив, отсортированный по убыванию: ");
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

double integrate(double (*f)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;
    
    for (int i = 0; i < n; ++i) {
        double x = a + i * h;
        sum += f(x) * h;
    }
    
    return sum;
}

double linear_func(double x) {
    return x;
}

double parabola_func(double x) {
    return x * x;
}

double exp_func(double x) {
    return exp(x);
}

double sin_func(double x) {
    return sin(x);
}