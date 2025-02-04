#include <cstdio>
#include "book.h"
#include "utils.h"

void init_book(Book& obj, const char * author, const char * title, int year, double price, const char * category){
    obj.author = author;
    obj.title = title;
    obj.year = year;
    obj.price = price;
    obj.category = category;
}

void print_book(Book& obj){
    const char * ptr;
    printf("Author: ");
    ptr = obj.author;
    while(*ptr != '\0'){
        printf("%c", *ptr++);
    }
    printf("\n");
    printf("Year: %i\n", obj.year);
    printf("Price: %.2lf\n", obj.price);
    printf("Title: ");
    ptr = obj.title;
    while(*ptr != '\0'){
        printf("%c", *ptr++);
    }
    printf("\n");
    printf("Category: ");
    ptr = obj.category;
    while(*ptr != '\0'){
        printf("%c", *ptr++);
    }
    printf("\n");
}

void input_book(Book& obj){
    while (getchar() != '\n');
    printf("Введите автора книги: ");
    obj.author = const_input();
    printf("Введите название книги: ");
    obj.title = const_input();
    printf("Введите год выпуска книги: ");
    while(1) {
        if (scanf(" %d", &(obj.year)) != 1) {
            printf("Неверный формат, введите численное значение. (Пример: 1995)\n");
            while (getchar() != '\n');
        } else {
            break;
        }
    }
    printf("Введите стоимость книги: ");
    while(1) {
        if (scanf("%lf", &obj.price) != 1) {
            printf("Неверный формат, введите численное значение. (Пример: 19.95)\n");
            while (getchar() != '\n');
        } else {
            break;
        }
    }
    printf("Введите жанр книги: ");
    while (getchar() != '\n');
    obj.category = const_input();
}