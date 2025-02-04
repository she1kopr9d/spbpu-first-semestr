#include "book.h"
#include "utils.h"

void init_book(Book& obj, const char * author, const char * title, int year, double price, const char * category){
    obj.author = author;
    obj.title = title;
    obj.year = year;
    obj.price = price;
    obj.category = category;
}

void print_book(const Book& obj){
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

void sort_catalog(std::vector<Book>& catalog, SortField field) {
    auto comparator = [field](const Book& a, const Book& b) {
        switch (field) {
            case AUTHOR: return strcmp(a.author, b.author) < 0;
            case TITLE: return strcmp(a.title, b.title) < 0;
            case YEAR: return a.year < b.year;
            case PRICE: return a.price < b.price;
            case CATEGORY: return strcmp(a.category, b.category) < 0;
        }
        return false;
    };
    std::sort(catalog.begin(), catalog.end(), comparator);
    std::cout << "Каталог отсортирован.\n";
}

void delete_book(Book& obj){
    delete[] obj.author;
    delete[] obj.title;
    delete[] obj.category;
}