#include <cstdio>
#include <iostream>
#include <fstream>

#include "utils.h"

#define PATH "catalog.txt"

void write_to_file(dinamic_array * array_ptr){

    FILE* file = fopen(PATH, "w");

    void * ptr;

    for (int i = 0; i < utils::get_lenght(array_ptr); i++) {
        ptr = utils::get_item(array_ptr, i);
        if (ptr == nullptr)
            continue;
        if (fputs((const char *)(ptr), file) == EOF) {
            fclose(file);
        }
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
            utils::add_item(array_ptr, answer);
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
                    << "1. Выписать список строк\n"
                    << "2. Добавить строку\n"
                    << "3. Удалить строку\n"
                    << "4. Загрузить строки из файла\n"
                    << "5. Выгрузить строки в файл\n"
                    << "6. Сортировать каталог\n"
                    << "7. Выход из программы\n"
                    << "Введите свой вариант: ";
                scanf("%d", &move);
                break;
            case 1:
                for(int i = 0; i < utils::get_lenght(list); i++){
                    buffer_ptr = utils::get_item(list, i);
                    if (buffer_ptr != nullptr)
                        std::cout << (char *)(buffer_ptr) << std::endl;
                }
                move = 0;
                break;
            case 2:
                while (getchar() != '\n');
                printf("Введите строку: ");
                ptr = const_input();
                utils::add_item(list, (void *)(ptr));
                move = 0;
                break;
            case 3:
                for(int i = 0; i < utils::get_lenght(list); i++){
                    buffer_ptr = utils::get_item(list, i);
                    if (buffer_ptr != nullptr)
                        std::cout << i << ": " << (char *)(buffer_ptr) << std::endl;
                }
                printf("Выберите строку, которую хотите удалить: ");
                std::cin >> move;
                utils::delete_item(list, move);
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
            case 7:
                void * ptr;
                for(int i = 0; i < utils::get_lenght(list); i++){
                    ptr = utils::get_item(list, i);
                    if (ptr == nullptr)
                        continue;
                    delete[] (char *)(ptr);
                }
                delete[] list->items;
                delete list;
                return 0;
        }
    }
    return 0;
}