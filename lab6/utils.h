#ifndef UTILS_H
#define UTILS_H

char * input();
const char * const_input();

int cmp_str(char * p1, char * p2);

struct dinamic_array{
    void ** items;
    int capacity;
    int next_index;
};

namespace utils{
    void init_dinamic_array(dinamic_array * array_ptr);
    void init_dinamic_array(dinamic_array * array_ptr, int capacity);
    void * get_item(dinamic_array * array_ptr, int index);
    void add_item(dinamic_array * array_ptr, void * item);
    void delete_item(dinamic_array * array_ptr, int index);
    int get_lenght(dinamic_array * array_ptr);
}

#endif