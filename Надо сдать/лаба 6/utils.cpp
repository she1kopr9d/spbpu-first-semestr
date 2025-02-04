#include <cstdio>
#include "utils.h"

char * input(){
    char c;
    int buffer_index = 0;
    int buffer_capacity = 1;
    char * buffer = new char[buffer_capacity];
    buffer[0] = '\0';
    do{
        if (buffer_index == buffer_capacity){
            buffer_capacity *= 2;
            char * buffer_2 = new char[buffer_capacity];
            for(int i = 0; i < (buffer_capacity / 2); i++){
                buffer_2[i] = buffer[i];
            }
            delete[] buffer;
            buffer = buffer_2;
        }
        scanf("%c", &c);
        buffer[buffer_index++] = c;
    } while (c != '\n');
    buffer[buffer_index-1] = '\0';
    char * answer = new char[buffer_index];
    for (int i = 0; i < buffer_index; i++){
        answer[i] = buffer[i];
    }
    delete[] buffer;
    return answer;
}

const char * const_input(){
    return const_cast<char *>(input());
}

int cmp_str(char * p1, char * p2){
    while ((*p1 != '\0') && ((*p1++ - *p2++) == 0));
    return (*--p1 - *--p2);
}

int cmp_str(void * p1, void * p2){
    return cmp_str((char *)p1, (char *)p2);
}

int get_lenght(char * line){
    int lenght = 0;
    while (line[lenght++] != '\0');
    return lenght;
}

int get_lenght(void * ptr){
    return get_lenght((char *)ptr);
}

const char * str_copy(const char * line){
    int lenght = get_lenght((char *)line);
    char * cp = new char[lenght];
    for (int i = 0; i < lenght; i++)
        cp[i] = line[i];
    return const_cast<char *>(cp);
}

const char * str_copy(void * ptr){
    return str_copy((const char *)ptr);
}

void utils::init_dinamic_array(dinamic_array * array_ptr){
    dinamic_array & array = *(array_ptr);
    array.next_index = 0;
    array.capacity = 1;
    array.items = new void * [array.capacity];
}

void utils::init_dinamic_array(dinamic_array * array_ptr, int capacity){
    dinamic_array & array = *(array_ptr);
    array.next_index = 0;
    array.capacity = capacity;
    array.items = new void * [array.capacity];
}

void * utils::get_item(dinamic_array * array_ptr, int index){
    dinamic_array & array = *(array_ptr);
    return array.items[index];
}

void utils::add_item(dinamic_array * array_ptr, void * item){
    dinamic_array & array = *(array_ptr);
    if (array.capacity <= array.next_index){
        void ** buffer = new void * [array.capacity*2];
        for(int i = 0; i < array.capacity; i++){
            buffer[i] = utils::get_item(array_ptr, i);
        }
        delete[] array.items;
        array.items = buffer;
        array.capacity *= 2;
    }
    array.items[array.next_index] = item;
    array.next_index++;
}

void utils::add_unique_item(dinamic_array * array_ptr, void * item, int (* cmp)(void * p1, void * p2)){
    dinamic_array & array = *(array_ptr);
    for(int i = 0; i < array.next_index; i++)
        if (cmp(utils::get_item(array_ptr, i), item) == 0){
            delete[] (const char *)item; // delete copy
            return;
        }
    utils::add_item(array_ptr, item);
}

void utils::delete_item(dinamic_array * array_ptr, int index){
    dinamic_array & array = *(array_ptr);
    array.items[index] = nullptr;
}

int utils::get_lenght(dinamic_array * array_ptr){
    dinamic_array & array = *(array_ptr);
    return array.next_index;
}

int get_valid_int(int min, int max){
    int value = min - 1;
    printf("Введите значение: ");
    scanf("%d", &value);
    while(1){
        if ((min <= value) && (value <= max)){
            return value;
        } else {
            printf("Вы ввели неверное значение, введите сново: ");
            while (getchar() != '\n');
            scanf("%d", &value);
        }  
    }
}

double get_valid_double(double min, double max){
    double value = min - 1;
    printf("Введите значение: ");
    scanf("%lf", &value);
    while(1){
        if ((min <= value) && (value <= max)){
            return value;
        } else {
            printf("Вы ввели неверное значение, введите сново: ");
            while (getchar() != '\n');
            scanf("%lf", &value);
        }  
    }
}

void utils::garbage_collector(dinamic_array * list){
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