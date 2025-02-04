#include "matrix.h"

void m_zero(Matrix *A, int m, int n){
    if (A->lines != nullptr){
        m_free(A);
    }
    A->m = m;
    A->n = n;
    A->lines = new double * [m];
    for (int i = 0; i < m; i++){
        A->lines[i] = new double[n];
        for(int j = 0; j < n; j++){
            A->lines[i][j] = 0;
        }
    }
} // - инициализация матрицы размера m на n нулями;

void m_id(Matrix *A, int n){
    m_zero(A, n, n);
    for (int i = 0; i < n; ++i) {
        m_set(A, i, i, 1);
    }
    return;
    A->m = n;
    A->n = n;
    A->lines = new double * [n];
    for (int i = 0; i < n; i++){
        A->lines[i] = new double[n];
        for(int j = 0; j < n; j++){
            if (i != j)
                A->lines[i][j] = 0;
            else
                A->lines[i][j] = 1;
        }
    }
} // - инициализация единичной матрицы n на n;

void m_free(Matrix *A){
    if (A->lines == 0) return;
    for(int i = 0; i < A->m; i++){
        delete[] A->lines[i];
    }
    delete[] A->lines;
    A->lines = 0;
} // - очистка памяти, используемой для матрицы;

void m_copy(const Matrix *src, Matrix *dst){
    if (dst->lines != nullptr){
        m_free(dst);
    }
    dst->m = src->m;
    dst->n = src->n;
    dst->lines = new double * [dst->m];
    for (int i = 0; i < dst->m; i++){
        dst->lines[i] = new double[dst->n];
        for(int j = 0; j < dst->n; j++){
            dst->lines[i][j] = src->lines[i][j];
        }
    }
} // - копирование данных матрицы src в матрицу dst.

int m_width(const Matrix *A){
    return A->n;
} // - ширина матрицы A;

int m_height(const Matrix *A){
    return A->m;
} // - высота матрицы A;

double m_get(const Matrix* A, int i, int j){
    return A->lines[i][j];
} // - получение i,j-того элемента матрицы;

void m_set(Matrix *A, int i, int j, double value){
    A->lines[i][j] = value;
} // - установка i,j-того элемента матрицы.

int m_add(Matrix *A, const Matrix *B){
    if (A->n != B->n || A->m != B->m)
        return 1;

    for(int i = 0; i < A->m; i++)
        for(int j = 0; j < A->n; i++)
            A->lines[i][j] += B->lines[i][j];

    return 0;
} // - если A и B одинакового размера, то прибавляет к A значения B и возвращает 0; иначе возвращает 1.

void m_neg(Matrix *A){
    for(int i = 0; i < A->m; i++)
        for(int j = 0; j < A->n; i++)
            A->lines[i][j] *= -1;
} // - заменяет все элементы матрицы A на противоположные.

int m_mult(const Matrix *A, const Matrix *B, Matrix *dst){
    if (A->n != B->m)
        return 1;

    int iter = A->n;

    dst->m = B->m;
    dst->n = B->n;

    m_zero(dst, dst->m, dst->n);

    for(int x = 0; x < B->n; x++){
        for(int y = 0; y < B->m; y++){
            for(int i = 0; i < iter; i++){
                dst->lines[y][x] += A->lines[y][i] * B->lines[i][x];
            }
        }
    }

    return 0;
} // - умножает матрицу A на матрицу B и сохраняет результат в dst. Если размеры матрицы не позволяют умножить матрицы, функция возвращает 1, иначе 0.