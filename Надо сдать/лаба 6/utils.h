#ifndef UTILS_H
#define UTILS_H

char * input();
const char * const_input();

int cmp_str(char * p1, char * p2);
int cmp_str(void * p1, void * p2);

int get_lenght(char * line);
int get_lenght(void * ptr);

const char * str_copy(const char * line);
const char * str_copy(void * ptr);

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
    void add_unique_item(dinamic_array * array_ptr, void * item, int (* cmp)(void * p1, void * p2));
    void delete_item(dinamic_array * array_ptr, int index);
    int get_lenght(dinamic_array * array_ptr);
    void garbage_collector(dinamic_array * list);
}

int get_valid_int(int min, int max);
double get_valid_double(double min, double max);

#endif