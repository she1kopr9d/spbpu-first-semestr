#include <iostream>
#include <stdio.h>
#include <stdlib.h>

void * pointer_offset(int offset, void * ptr){
    return (void *)((long)(ptr+offset));
}

int main(){
    long t = 0xfffffff;
    long *** arr = new long ** [t];

    std::cout << t << std::endl;

    // for ( int i = 0; i < t; i ++){
    //     arr[i] = new long * [t];
    //     for (int j = 0; j < t; j ++){
    //         arr[i][j] = new long [t];
    //         std::cout << arr[i][j] << " " << i << " " << j << std::endl;
    //     }
    // }
    return 0;
}