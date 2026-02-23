/**
 * Hexdumps a file, a byte at a time
 * Display the line number in decimal
 *
 * Only argument is number of bytes to read from file
 */

#include <stdio.h>
#include <stdlib.h>

#define columns 16
// Can be changed to hexadecimal by replacing d with x
#define lineNumberFormat "%02d: "

/**
 * Prints a row of bytes from a file of length bufferSize
 *
 * @param ptr         file pointer to read from
 * @param buffer      buffer to write file row into
 * @param bufferSize  size of buffer, avoids sizeof call for each row
 */
void printRow(FILE *ptr, int *buffer, int bufferSize) {
    fread(buffer, bufferSize, 1, ptr)
}

int main(int argc, char* argv[]) {
    int bufferSize;
    int startAddress;
    int endAddress;

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
        printf(lineNumberFormat, i*columns);
        for (int j = 0; j < columns; j += 2)
            printf("%02X%02X ", buffer[i*columns+j], buffer[i*columns+j+1]);
        printf("\n");
    }
    int roundedDown = bufferSize & ~(columns-1);
    if (bufferSize != roundedDown) {
        printf(lineNumberFormat, roundedDown);
        for (int i = 0; i < bufferSize % columns; i += 2)
            printf("%02X%02X ", buffer[roundedDown+i], buffer[roundedDown+i+1]);
        printf("\n");
    }

    return 0;
}
