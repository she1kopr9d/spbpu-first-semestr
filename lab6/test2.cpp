#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

#include "utils.h"
#include "book.h"

#define PATH "catalog.txt"

void Clear()
{
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
    system("clear");
#endif
}

void garbage_collector(dinamic_array * list){
    dinamic_array * temp = new dinamic_array();
    utils::init_dinamic_array(temp);
    void * ptr;
    for(int i = 0; i < utils::get_lenght(list); i++){
        ptr = utils::get_item(list, i);
        if (ptr == nullptr)
            continue;
        utils::add_item(temp, ptr);
    }
    delete[] list->items;
    list->next_index = temp->next_index;
    list->capacity = temp->capacity;
    list->items = temp->items;
    delete temp;
}

bool book_cmp(SortField state, void * p1, void * p2){
    Book * left = (Book *)p1;
    Book * right = (Book *)p2;
    switch(state){
        case AUTHOR:
            return (cmp_str(const_cast<char *>(left->author), const_cast<char *>(right->author)) > 0);
        case TITLE:
            return (cmp_str(const_cast<char *>(left->author), const_cast<char *>(right->author)) > 0);
        case YEAR:
            return (left->year > right->year);
        case PRICE:
            return (left->price > right->price);
        case CATEGORY:
            return (cmp_str(const_cast<char *>(left->author), const_cast<char *>(right->author)) > 0);
    }
    return false;
}

void void_swap(void ** p1, void ** p2){
    void * temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void sort_library(SortField state, void ** items, int lenght){
    if (lenght <= 1)
        return;
    int j;
    for (int i = 1; i < lenght; i++){
        j = i;
        while((j != 0)){
            if (book_cmp(state, items[j-1], items[j])){
                void_swap(&items[j-1], &items[j--]);
            }
            else{
                break;
            }
        }
    }
}

void write_to_file(dinamic_array * array_ptr){

    FILE* file = fopen(PATH, "w");

    void * ptr;

    for (int i = 0; i < utils::get_lenght(array_ptr); i++) {
        ptr = utils::get_item(array_ptr, i);
        if (ptr == nullptr)
            continue;
        fputs((const char *)((*(Book *)(ptr)).author), file);
        fputc('\n', file);
        fputs((const char *)((*(Book *)(ptr)).title), file);
        fputc('\n', file);
        fputs((const char *)(std::to_string((*(Book *)(ptr)).year).c_str()), file);
        fputc('\n', file);
        fputs((const char *)(std::to_string((*(Book *)(ptr)).price).c_str()), file);
        fputc('\n', file);
        fputs((const char *)((*(Book *)(ptr)).category), file);
        fputc('\n', file);
    }

    fclose(file);
}

void read_file(dinamic_array * array_ptr){
    std::ifstream file(PATH);

    char c;
    int buffer_index = 0;
    int buffer_capacity = 1;
    char * buffer = new char[buffer_capacity];
    buffer[0] = '\0';
    SortField state = AUTHOR;
    while (file.get(c)) {
        std::cout << c;
        if (buffer_index == buffer_capacity){
            buffer_capacity *= 2;
            char * buffer_2 = new char[buffer_capacity];
            for(int i = 0; i < (buffer_capacity / 2); i++){
                buffer_2[i] = buffer[i];
            }
            delete[] buffer;
            buffer = buffer_2;
        }
        buffer[buffer_index++] = c;
        if (c == '\n'){
            buffer[buffer_index-1] = '\0';
            char * answer = new char[buffer_index];
            for (int i = 0; i < buffer_index; i++){
                answer[i] = buffer[i];
            }
            delete[] buffer;
            buffer_index = 0;
            buffer_capacity = 1;
            buffer = new char[buffer_capacity];
            buffer[0] = '\0';
            Book * temp;
            if (state == AUTHOR){
                temp = new Book();
                init_book(*temp, answer, nullptr, 0, 0, nullptr);
                utils::add_item(array_ptr, temp);
            }
            else{
                temp = (Book *)(utils::get_item(array_ptr, utils::get_lenght(array_ptr)-1));
                switch(state){
                    case TITLE:
                        temp->title = answer;
                        break;
                    case YEAR:
                        temp->year = std::stoi(answer);
                        delete[] answer;
                        break;
                    case PRICE:
                        temp->price = std::stod(answer);
                        delete[] answer;
                        break;
                    case CATEGORY:
                        temp->category = answer;
                        break;
                }
            }
            state = (SortField)((state + 1) % 5);
        }
    }
    delete[] buffer;

    file.close();
}

int main(){
    dinamic_array * list = new dinamic_array();
    utils::init_dinamic_array(list);
    int move = 0;
    const char * ptr;
    void * buffer_ptr;
    while(true){
        switch(move) {
            case 0:
                std::cout << "Меню действий:\n"
                    << "1. Выписать список книг\n"
                    << "2. Добавить книгу\n"
                    << "3. Удалить книгу\n"
                    << "4. Загрузить список книг из файла\n"
                    << "5. Выгрузить книги в файл\n"
                    << "6. Сортировать каталог\n"
                    << "7. Выход из программы\n"
                    << "8. Очистить каталог от мусора\n"
                    << "Введите свой вариант: ";
                scanf("%d", &move);
                Clear();
                break;
            case 1:
                for(int i = 0; i < utils::get_lenght(list); i++){
                    buffer_ptr = utils::get_item(list, i);
                    if (buffer_ptr != nullptr){
                        printf("Книга %d:\n", i+1);
                        print_book(*(Book *)(buffer_ptr));
                    }
                }
                move = 0;
                break;
            case 2:
                buffer_ptr = (void *)(new Book());
                input_book(*(Book *)(buffer_ptr));
                utils::add_item(list, (void *)(buffer_ptr));
                buffer_ptr = nullptr;
                move = 0;
                break;
            case 3:
                for(int i = 0; i < utils::get_lenght(list); i++){
                    buffer_ptr = utils::get_item(list, i);
                    if (buffer_ptr != nullptr){
                        printf("Книга %d:\n", i+1);
                        print_book(*(Book *)(buffer_ptr));
                    }
                }
                printf("Выберите книгу, которую хотите удалить: ");
                std::cin >> move;
                buffer_ptr = utils::get_item(list, move - 1);
                utils::delete_item(list, move - 1);
                delete_book(*(Book *)(buffer_ptr));
                delete (Book *)buffer_ptr;
                garbage_collector(list);
                move = 0;
                break;
            case 4:
                read_file(list);
                move = 0;
                break;
            case 5:
                write_to_file(list);
                move = 0;
                break;
            case 6:
                std::cout << "По какому параметру вы хотите сортировать?:\n"
                    << "1. Автор\n"
                    << "2. Название\n"
                    << "3. Год выпуска\n"
                    << "4. Цена\n"
                    << "5. Жанр\n"
                    << "Введите свой вариант: ";
                scanf("%d", &move);
                move--;
                garbage_collector(list);
                sort_library((SortField)(move), list->items, utils::get_lenght(list));
                move = 0;
                break;
            case 7:
                for(int i = 0; i < utils::get_lenght(list); i++){
                    buffer_ptr = utils::get_item(list, i);
                    if (buffer_ptr == nullptr)
                        continue;
                    delete_book(*(Book *)(buffer_ptr));
                    delete (Book *)(buffer_ptr);
                }
                delete[] list->items;
                delete list;
                return 0;
            case 8:
                garbage_collector(list);
                move = 0;
                break;
        }
    }
    return 0;
}