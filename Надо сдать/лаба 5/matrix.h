#ifndef MATRIX_H
#define MATRIX_H

struct Matrix{
    int n;
    int m;
    double ** lines;
};

void m_zero(Matrix *A, int m, int n); // - инициализация матрицы размера m на n нулями;
void m_id(Matrix *A, int n); // - инициализация единичной матрицы n на n;
void m_free(Matrix *A); // - очистка памяти, используемой для матрицы;
void m_copy(const Matrix *src, Matrix *dst); // - копирование данных матрицы src в матрицу dst.
int m_width(const Matrix *A); // - ширина матрицы A;
int m_height(const Matrix *A); // - высота матрицы A;
double m_get(const Matrix* A, int i, int j); // - получение i,j-того элемента матрицы;
void m_set(Matrix *A, int i, int j, double value); // - установка i,j-того элемента матрицы.

int m_add(Matrix *A, const Matrix *B); // - если A и B одинакового размера, то прибавляет к A значения B и возвращает 0; иначе возвращает 1.
void m_neg(Matrix *A); // - заменяет все элементы матрицы A на противоположные.
int m_mult(const Matrix *A, const Matrix *B, Matrix *dst); // - умножает матрицу A на матрицу B и сохраняет результат в dst. Если размеры матрицы не позволяют умножить матрицы, функция возвращает 1, иначе 0.

#endif