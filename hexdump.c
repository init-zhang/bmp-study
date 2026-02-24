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
 * @param lineNumber  the address of the first byte for this line, used
 *                    for line numbers
 * @param start       the address of the first byte to display
 * @param length      number of bytes to display
 */
void printRow(FILE *ptr, unsigned char *buffer, int lineNumber, int start, int length) {
    int address;
    fread(buffer, bufferSize, 1, ptr);
    printf(lineNumberFormat, lineNumber);
    for (int i = 0; i < bufferSize; i++) {
        address = lineNumber + i;
        if (address >= start && address < start+length) {
            printf("%02X ", buffer[i]);
        } else {
            printf("-- ");
        }
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    int startAddress = 0;
    int length = 16;

    switch (argc) {
        case 3:
            startAddress = atoi(argv[1]);
            length = atoi(argv[2]);
            break;
        case 2:
            length = atoi(argv[1]);
            break;
    }

    unsigned char buffer[bufferSize];
    FILE *ptr;

    ptr = fopen("demo.bmp","rb");

    int roundedUp = (length + (columns-1)) & ~(columns-1);

    for (int i = 0; i < roundedUp; i += columns)
        printRow(ptr, buffer, i, startAddress, length);

    return 0;
}
