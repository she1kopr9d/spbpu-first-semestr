#include <cstdio>

const char * const_input(){
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
    return const_cast<char *>(answer);
}