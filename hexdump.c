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
#define bufferSize 16

/**
 * Prints a row of bytes from a file of length bufferSize
 *
 * @param ptr         file pointer to read from
 * @param buffer      buffer to write file row into
 * @param lineNumber  the address of the first byte, used for line numbers
 */
void printRow(FILE *ptr, unsigned char *buffer, int lineNumber) {
    fread(buffer, bufferSize, 1, ptr);
    printf(lineNumberFormat, lineNumber);
    for (int i = 0; i < bufferSize; i++)
        printf("%02X ", buffer[i]);
    printf("\n");
}

int main(int argc, char* argv[]) {
    int startAddress;
    int length;

    if (argc == 2 ) {
        length = atoi(argv[1]);
    } else {
        length = 16;
    }

    unsigned char buffer[bufferSize];
    FILE *ptr;

    ptr = fopen("demo.bmp","rb");

    int roundedUp = (length + (columns-1)) & ~(columns-1);

    for (int i = 0; i < roundedUp; i += columns)
        printRow(ptr, buffer, i);

    return 0;
}
