#include <stdio.h>


int main(int argc, char** argv) {
    unsigned char buffer[16];
    FILE *ptr;

    ptr = fopen("demo.bmp","rb");

    fread(buffer,sizeof(buffer),1,ptr);

    for (int i = 0; i<16; i++)
        printf("%02X ", buffer[i]);
    printf("\n");

    return 0;
}
