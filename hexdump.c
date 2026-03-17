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
#define bufferSize 32

/**
 * Prints a chunk of bytes from a file of length bufferSize
 *
 * @param ptr          file descriptor to read from
 * @param buffer       buffer to write file chunk into
 * @param chunkNumber  the address of the first byte for this chunk,
 *                     must be a factor of `columns`
 * @param start        the address of the first byte to display
 * @param length       number of bytes to display
 */
void printChunk(FILE *ptr, unsigned char *buffer, int lineNumber, int start, int length) {
    int address;
    fread(buffer, bufferSize, 1, ptr);
    for (int i = 0; i < bufferSize; i++) {
        address = lineNumber + i;

        // At the start of a column
        if (i % columns == 0) {
            printf(lineNumberFormat, address);
        }

        printf("%02X ", buffer[i]);

        // At the end of a column
        if ((i + 1) % columns == 0)
            printf("\n");
    }
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

    int startIndex = startAddress & ~(bufferSize-1);
    int endIndex = (startIndex + length + (bufferSize-1)) & ~(bufferSize-1);

    printf("%d to %d\n", startIndex, endIndex);

    fseek(ptr, startIndex, SEEK_SET);
    for (int i = startIndex; i < endIndex; i += bufferSize)
        printChunk(ptr, buffer, i, startAddress, length);

    return 0;
}
