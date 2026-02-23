/* Hexdumps a file, a short (16 bits) at a time
 * Does not accurately display endianness because hex for 2 bytes is displayed
 * as big endian after being converted into a short
 * e.g. 424D is displayed 4D42 in output
 *
 * Only argument is number of shorts to read from file
 */

#include <stdio.h>
#include <stdlib.h>

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
