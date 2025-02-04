
#ifndef OTHER_H
#define OTHER_H

int inc_by_value(int value);

void inc_by_pointer(int* ptr);

void inc_by_reference(int& ref);

void swap(int* ptr1, int* ptr2);

void swap(int & r1, int & r2);

int min(const int * arr, int n);

int min(int * const* arr, int n, int k);

int** createRandomArray(int rows, int cols, int minValue, int maxValue);

void printArray(int** array, int rows, int cols);

void deleteArray(int** array, int rows);

int string_cmp(const char * l1, const char * l2);

int day_of_year(const int (&months)[2][12], int day, int month, int year);

void day_of_month(const int (&months)[2][12], int day_of_year, int year, int& day, int& month);

int add_unique(int ** arr, int n, int new_value);

void print_array(int * arr, int n);

int recsumar(int n);

char * get_line();
int get_lenght(const char * string);

int getBit(char symbol, int index);
int * toBit(const char * string, int n);
int toNum(int * binNum, int start, int offset);
int toBitInBuffer(const char * string, int n, int * buffer);
int numToBits(int num, int * buffer);
int sizeBinNum(int num);
int * numInBits(int num);

int decode_alfabet(char symbol);

int encoded32_size(int raw_size);
int decoded32_size(int encode_size);
int encode32(const char *raw_data, int raw_size, char *dst);
int decode32(const char *encoded_data, int encoded_size, char *dst);

void var_args(int first, ...);
#define VAR_ARGS(...) var_args(__VA_ARGS__, 0)

int* my_min(int* array, int size);
#endif