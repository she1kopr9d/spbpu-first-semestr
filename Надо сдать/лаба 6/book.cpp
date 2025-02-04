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

void input_book(Book& obj, void ** categories = {}, int lenght = 0){
    while (getchar() != '\n');
    printf("Введите автора книги: ");
    obj.author = const_input();
    printf("Введите название книги: ");
    obj.title = const_input();
    printf("Введите год выпуска книги: ");
    while(1) {
        if (scanf(" %d", &(obj.year)) != 1) {
            printf("Неверный формат, введите численное значение. (Пример: 1995): ");
            while (getchar() != '\n');
        } else {
            break;
        }
    }
    printf("Введите стоимость книги: ");
    while(1) {
        if (scanf("%lf", &obj.price) != 1) {
            printf("Неверный формат, введите численное значение. (Пример: 19.95): ");
            while (getchar() != '\n');
        } else {
            if (obj.price < 0){
                printf("Неверный формат, стоимость не может быть отрицательной. (Пример: 19.95): ");
                while (getchar() != '\n');
            } else{
                break;
            }
        }
    }
    if (lenght != 0){
        for(int i = 0; i < lenght; i++){
            printf("%d: %s\n", i + 1, (const char *)categories[i]);
        }
    }
    printf("Введите жанр книги или номер из предложенных: ");
    while (getchar() != '\n');
    const char * answer = const_input();
    bool flag = true;
    for (int i = 0; i < get_lenght((char *)answer); i++){
        flag = flag && (isdigit(answer[i]) || answer[i] == '\0');
    }
    if (flag == true){
        int index;
        index = std::stoi(answer);
        if ((index > 0) && (index <= lenght)){
            obj.category = str_copy(categories[index-1]);
            delete[] answer;
        } else {
            obj.category = answer;
        }
    } else {
        obj.category = answer;
    }
}


void delete_book(Book& obj){
    delete[] obj.author;
    delete[] obj.title;
    delete[] obj.category;
}

void print_all_parameters(){
    std::cout << "Выберите параметр:\n"
        << "1. Автор\n"
        << "2. Название\n"
        << "3. Год выпуска\n"
        << "4. Цена\n"
        << "5. Жанр\n";
}

void edit_book(Book * ptr){
    SortField state;
    Book & book = *(Book *)(ptr);
    print_all_parameters();
    state = (SortField)(get_valid_int(1, 5) - 1);
    switch(state){
        case AUTHOR:
        case TITLE:
        case CATEGORY:
            const char * new_value;
            printf("Введите новое значение: ");
            while (getchar() != '\n');
            new_value = const_input();
            delete[] ((const char **)(ptr))[(int)(state)];
            ((const char **)(ptr))[(int)(state)] = new_value;
            break;
        case YEAR:
            int year;
            printf("Введите новое значение: ");
            year = get_valid_int(-100000000, 2100);
            book.year = year;
            break;
        case PRICE:
            double price;
            printf("Введите новое значение: ");
            price = get_valid_double(0, 100000000);
            book.price = price;
            break;
    }
    printf("Параметр был успешно изменен!\n");
}