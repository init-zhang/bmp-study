/**
 * Read the data of a BMP image file
 *
 * Usage:
 * readimage [flags] [file]
 *
 * Flags:
 * -h  Print the RGB value rather than TrueColor pixel.
 * -d  Print the RGB denary values rather than TrueColor pixel.
 * -p  Print width padding.
 *
 * Flags must be separated by a space:
 * `./readimage.o -h -p` prints the hex value with padding.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    bool printHex;
    bool printDenary;
    bool includePadding;
} options;

// Prevent padding between size-sensitive structures. Padding can break the
// size of members and result in incorrect values.

#pragma pack(push, 1)
typedef struct {
    uint16_t magicNumber;
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
} fileHeader;

typedef struct {
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t colorPlanes;
    uint16_t bitsPerPixel;
} dibHeader;
#pragma pack(pop)

int checkFile(FILE *file) {
    uint16_t magicNumber;
    fread(&magicNumber, sizeof(uint16_t), 1, file);
    printf("Magic number of file is: %u\n", magicNumber);
    // Hex value for `BM` is 0x424D, but as magic number is read as an
    // uint16_t, we must reverse the endian too.
    if (magicNumber != 0x4D42) {
        printf("File magic number is not of BMP file.\n");
        return 1;
    } else {
        return 0;
    }
}

void readPixels(FILE *file, fileHeader header, dibHeader dib, options opts) {
    int bytesPerPixel = dib.bitsPerPixel >> 3;
    int rowWidth = (bytesPerPixel * dib.width + bytesPerPixel) & ~bytesPerPixel;
    uint8_t buffer[rowWidth];
    long int bufferSize = sizeof(buffer);
    int pixelCount = 0;
    int x = 0;
    int y = dib.height - 1;
    int endAddress = bufferSize * dib.height + header.offset;
    int pixel;
    uint8_t r;
    uint8_t g;
    uint8_t b;

    printf("========\n");
    printf("Buffer size: %lu\n", bufferSize);
    if (bufferSize == dib.width * bytesPerPixel) printf("Buffer size and width match, no padding.\n");
    else printf("Buffer size and width do not match, there will be padding. View using `-p` flag.\n");
    printf("End address: %u\n", endAddress);

    fseek(file, endAddress - bufferSize,  SEEK_SET);

    // Read file from bottom row up because of how images are stored. The top
    // row of the image as the last line of pixels within BMP images.

     while (y != 0) {
        fread(&buffer, bufferSize, 1, file);
        pixel = 0;

        for (; pixel < dib.width; pixel++) {
            if (x >= dib.width) {
                x = 0;
                y--;
                printf("\033[0m\n");
            }

            // Read color values in reverse order due to little-endian.
            b = buffer[pixel*bytesPerPixel];
            g = buffer[pixel*bytesPerPixel+1];
            r = buffer[pixel*bytesPerPixel+2];

            if (opts.printHex) {
                printf("#%x%x%x ", r, g, b);
            } else if (opts.printDenary) {
                printf("(%u, %u, %u) ", r, g, b);
            } else {
                // Use TrueColor escape code to display pixels.
                printf("\033[48;2;%u;%u;%um  ", r, g, b);
            }

            x++;
            pixelCount++;
        }

        // Multiply last pixel by bytesPerPixel to get the first byte index of
        // padding (if it exists).
        // Last pixel index -> first byte index of padding.
        long int currentIndex = pixel * bytesPerPixel;

        if (opts.includePadding && currentIndex < bufferSize) {
            printf("\033[0m | ");
            for (int i = currentIndex; i < bufferSize; i++) {
                if (opts.printHex) printf("%x ", buffer[i]);
                else printf("%u ", buffer[i]);
            }
        }

        // -1 jumps back to the start of the current row. Another -1 jumps back
        // to the start of the row above.
        fseek(file, -2 * bufferSize, SEEK_CUR);
     }

    printf("\033[0m\n");
    printf("Pixel count: %d\n", pixelCount);
}

int main(int argc, char* argv[]) {
    options opts = {0};
    char* fileName = "demo.bmp";
    FILE *file;

    for (int i = 1; i < argc; i++) {
        printf("%u: %s\n", i, argv[i]);
        if (strcmp(argv[i], "-h") == 0) {
            opts.printHex = true;
            printf("Printing RGB values instead of TrueColor pixel.\n");
        } else if (strcmp(argv[i], "-d") == 0) {
            opts.printDenary = true;
            printf("Printing denary RGB values instead TrueColor pixel.\n");
        } else if (strcmp(argv[i], "-p") == 0) {
            opts.includePadding = true;
            printf("Including padding as well.\n");
        } else {
            fileName = argv[i];
        }
    }

    printf("Opening file: %s\n", fileName);
    printf("========\n");

    file = fopen(fileName, "rb");

    if (!file) {
        printf("File could not be read.\n");
        return 1;
    }

    if (checkFile(file) == 1) {
        fclose(file);
        return 1;
    }

    printf("File magic number is of BMP file, reading header.\n");

    fileHeader header;
    fseek(file, 0, SEEK_SET);
    fread(&header, sizeof(fileHeader), 1, file);

    printf("Magic number: %u\n", header.magicNumber);
    printf("File size: %u\n", header.fileSize);
    printf("Reserved 1: %u\n", header.reserved1);
    printf("Reserved 2: %u\n", header.reserved2);
    printf("Offset: %u\n", header.offset);

    dibHeader dib;
    fread(&dib, sizeof(dib), 1, file);

    printf("========\n");
    printf("DIB header size: %u\n", dib.headerSize);
    printf("Image width: %d\n", dib.width);
    printf("Image height: %d\n", dib.height);
    printf("Color planes: %d\n", dib.colorPlanes);
    printf("Bits per pixel: %d\n", dib.bitsPerPixel);

    if (dib.colorPlanes != 1) {
        printf("Color planes must be 1.\n");
        return 1;
    }

    readPixels(file, header, dib, opts);

    fclose(file);

    return 0;
}
