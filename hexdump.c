/* Hexdumps a file, a byte  at a time
 *
 * Only argument is number of bytes to read from file
 */

#include <stdio.h>
#include <stdlib.h>

#define columns 16

int main(int argc, char* argv[]) {
    int bufferSize;
    if (argc == 2 ) {
        bufferSize = atoi(argv[1]);
    } else {
        bufferSize = columns;
    }
    unsigned char buffer[bufferSize];
    FILE *ptr;

    ptr = fopen("demo.bmp","rb");

    fread(buffer, sizeof(buffer), 1, ptr);

    for (int i = 0; i < bufferSize / columns; i++) {
        for (int j = 0; j < columns; j += 2)
            printf("%02X%02X ", buffer[j+i], buffer[j+i+1]);
        printf("\n");
    }
    int roundedDown = bufferSize & ~(columns-1);
    if (bufferSize != roundedDown) {
        for (int i = 0; i < bufferSize % columns; i += 2)
            printf("%02X%02X ", buffer[roundedDown+i], buffer[roundedDown+i+1]);
        printf("\n");
    }

    return 0;
}
