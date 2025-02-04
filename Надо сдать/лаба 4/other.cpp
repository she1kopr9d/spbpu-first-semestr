#include "other.h"
#include <iostream>
#include <cassert>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

#define MIN(A, B) ((((A) <= (B)) ? (A) : (B)))

int inc_by_value(int value) {
    return value + 1;
}

void inc_by_pointer(int* ptr) {
    if (ptr) {
        *ptr += 1;
    }
}

void inc_by_reference(int& ref) {
    ref += 1;
}

void swap(int* ptr1, int* ptr2) {
    int * temp = ptr1;
    ptr1 = ptr2;
    ptr2 = temp;
}

void swap(int & r1, int & r2){
    int temp = r1;
    r1 = r2;
    r2 = temp;
}

int min(const int * arr, int n){
    assert(n > 0);
    int m = arr[0];
    for (int i = 1; i < n; i++)
        m = MIN(m, arr[i]);
    return m;
}

int min(int * const* arr, int n, int k){
    assert(n > 0 && k > 0);
    if (n == 0)
        return -1;
    int m = min(arr[0], k);
    for (int i = 1; i < n; i++)
        m = MIN(m, min(arr[i], k));
    return m;
}

int** createRandomArray(int rows, int cols, int minValue, int maxValue) {
    int** array = new int*[rows];
    
    for (int i = 0; i < rows; ++i) {
        array[i] = new int[cols];
        for (int j = 0; j < cols; ++j) {
            array[i][j] = minValue + std::rand() % (maxValue - minValue + 1);
        }
    }

    return array;
}

void printArray(int** array, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << array[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void deleteArray(int** array, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] array[i];
    }
    delete[] array;
}

int string_cmp(const char * l1, const char * l2){
    assert(l1 && l2);
    while ((*l1 != '\0') && ((*l1++ - *l2++) == 0));
    return (*--l1 - *--l2);
}

int day_of_year(const int (&months)[2][12], int day, int month, int year) {
    int day_of_year = day;
    bool leap_year = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    if (leap_year) {
        for (int i = 0; i < month - 1; ++i) {
            day_of_year += months[1][i];
        }
    }
    else{
        for (int i = 0; i < month - 1; ++i) {
            day_of_year += months[0][i];
        }
    }
    
    return day_of_year;
}

void day_of_month(const int (&months)[2][12], int day_of_year, int year, int& day, int& month) {
    bool leap_year = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    
    month = 0;
    if (leap_year) {
        while (day_of_year > months[1][month]) {
            day_of_year -= months[1][month];
            ++month;
        }
    }
    else{
        while (day_of_year > months[0][month]) {
            day_of_year -= months[0][month];
            ++month;
        }
    }
    ++month;
    day = day_of_year;
}

void print_array(int * arr, int n){
    for(int i = 0; i < n; i++){
        if (arr[i] == -1){
            std::cout << "\n";
            return;
        }
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

int add_unique(int ** arr, int n, int new_value){
    bool flag = false;
    for (int i = 0; i < n; i++)
        if (arr[0][i] == new_value)
            return n;
    
    int new_n = n+1;
    int * buffer = new int[new_n];
    for (int i = 0; i < n; i++){
        buffer[i] = arr[0][i];
    }
    buffer[new_n-1] = new_value;
    delete[] arr[0];
    arr[0] = buffer;
    return new_n;
}

int recsumar(int n){
    return n != 1 ? (n + recsumar(n-1)) : 1;
}

char * get_line(){
    int cap = 2;
    int index = 0;
    char * buffer = new char[cap];
    buffer[cap-1] = '\0';
    char symbol_buffer = std::cin.get();
    while (symbol_buffer != '\n'){
        buffer[index++] = symbol_buffer;
        if (index+1 == cap){
            cap *= 2;
            char * second_buffer = new char[cap];
            for(int j = 0; j < cap/2; j++){
                second_buffer[j] = buffer[j];
            }
            delete[] buffer;
            buffer = second_buffer;
        }
        symbol_buffer = std::cin.get();
    }
    buffer[index] = '\0';
    return buffer;
}

int get_lenght(const char * string){
    int n = 0;
    while (string[n] != '\0')
        n++;
    return n;
}

int getBit(char symbol, int index)
{
    return (symbol & (1 << index)) >> index;
}

int * toBit(const char * string, int n){
    int * bitView = new int[n*8];
    char select_symbol;
    for (int index_symbol = 0; index_symbol < n; index_symbol++){
        select_symbol = string[index_symbol];
        for (int index_bit = 0; index_bit < 8; index_bit++){
            bitView[index_symbol*8+index_bit] = getBit(select_symbol, index_bit);
        }
    }
    return bitView;
}

int toBitInBuffer(const char * string, int n, int * buffer){
    int close_index = -1;
    bool isFirst = false;
    for (int i = 0; i < n; i++){
        buffer[i] = getBit(string[i/8], i%8);
        if (isFirst == true)
            continue;
        if (buffer[i] == 0)
            close_index = i;
        else
            isFirst = true;
    }
    return close_index + 1;
}

int numToBits(int num, int * buffer){
    char * line = new char[4];
    int * raw_bits = new int[32];
    for (int i = 0; i < 4; i++){
        line[i] = static_cast<char>(num << (i * 8));
    }
    int close_index = toBitInBuffer(line, 32, raw_bits);
    int * bits = new int[32 - close_index];
    for (int i = close_index; i < 32; i ++)
        bits[i] = raw_bits[i];
    buffer = bits;
    delete[] raw_bits;
    return 32 - close_index;
}

int toNum(int * binNum, int start, int offset){
    int num = 0;
    int n = start + offset;
    for (int i = start; i < (n - 1); i++){
        num += binNum[i];
        num = num << 1;
    }
    num += binNum[n-1];
    return num;
}
const char ENCODING_TABLE[33] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456";
const int BITS_PER_CHAR = 5;

int encoded32_size(int raw_size) {
    return (raw_size * 8 + BITS_PER_CHAR - 1) / BITS_PER_CHAR;
}

int decoded32_size(int encode_size) {
    return (encode_size * BITS_PER_CHAR) / 8;
}

int encode32(const char *raw_data, int raw_size, char *dst) {
    if (!raw_data || raw_size < 0 || !dst) return 1;

    int bit_buffer = 0;
    int bit_count = 0;
    int dst_index = 0;

    for (int i = 0; i < raw_size; ++i) {
        bit_buffer = (bit_buffer << 8) | raw_data[i];
        bit_count += 8;

        while (bit_count >= BITS_PER_CHAR) {
            int index = (bit_buffer >> (bit_count - BITS_PER_CHAR)) & 0x1F;
            dst[dst_index++] = ENCODING_TABLE[index];
            bit_count -= BITS_PER_CHAR;
        }
    }

    if (bit_count > 0) {
        int index = (bit_buffer << (BITS_PER_CHAR - bit_count)) & 0x1F;
        dst[dst_index++] = ENCODING_TABLE[index];
    }
    return 0;
}

int decode32(const char *encoded_data, int encoded_size, char *dst) {
    if (!encoded_data || encoded_size < 0 || !dst) return 1;

    int bit_buffer = 0;
    int bit_count = 0;
    int dst_index = 0;

    for (int i = 0; i < encoded_size; ++i) {
        const char *char_pos = strchr(ENCODING_TABLE, toupper(encoded_data[i]));
        if (!char_pos) return 2;

        int value = char_pos - ENCODING_TABLE;
        bit_buffer = (bit_buffer << BITS_PER_CHAR) | value;
        bit_count += BITS_PER_CHAR;

        while (bit_count >= 8) {
            dst[dst_index++] = (bit_buffer >> (bit_count - 8)) & 0xFF;
            bit_count -= 8;
        }
    }

    return 0;
}


void var_args(int first, ...) {
    va_list args;
    int count = 0;
    va_start(args, first);
    if (first == 0){
        printf("Количество переменнтых: %i\n", count);
        return;
    }
    printf("Аргумент %i: %i\n", ++count, first);
    int current;
    while ((current = va_arg(args, int)) != 0) {
        printf("Аргумент %d: %d\n", ++count, current);
    }
    va_end(args);
    printf("Количество переменнтых: %i\n", count);
}

int* my_min(int* array, int size) {
    if (size <= 0) {
        return NULL;
    }
    
    int* min_element = array;
    for (int i = 1; i < size; i++) {
        if (array[i] < *min_element) {
            min_element = &array[i];
        }
    }
    return min_element;
}