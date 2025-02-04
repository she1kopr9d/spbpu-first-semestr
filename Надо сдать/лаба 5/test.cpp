#include "utils.h"
#include <iostream>

int main(){
    const char * data;
    data = const_input();
    std::cout << data << '\n';
    delete[] data;
    return 0;
}