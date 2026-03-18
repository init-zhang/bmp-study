#include <stdio.h>
#include <stdlib.h>

typedef struct {
    

#define columns 8

int main(int argc, char* argv[]) {
    int bufferSize;
    if (argc == 2 ) {
        bufferSize = atoi(argv[1]);
    } else {
        bufferSize = columns;
    }
    unsigned short buffer[bufferSize];
    FILE *ptr;

    ptr = fopen("demo.bmp","rb");

    fread(buffer, sizeof(buffer), 1, ptr);

    for (int i = 0; i < bufferSize / columns; i++) {
        for (int j = 0; j < columns; j++)
            printf("%04X ", buffer[i*columns+j]);
        printf("\n");
    }
    int roundedDown = bufferSize & ~(columns-1);
    if (bufferSize != roundedDown) {
        for (int i = 0; i < bufferSize % columns; i++)
            printf("%04X ", buffer[roundedDown + i]);
        printf("\n");
    }

    return 0;
}
