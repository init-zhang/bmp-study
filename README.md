# BMP Study

BMP file format study

## Header Format

Assuming `BITMAPINFOHEADER` header format

```
+--+-+----------------------------+
|0 |2|magic number                | BMP file header
+--+-+----------------------------+
|2 |4|BMP size                    |
+--+-+----------------------------+
|6 |2|reserved                    |
+--+-+----------------------------+
|8 |2|reserved                    |
+--+-+----------------------------+
|10|4|starting address of image   |
+--+-+----------------------------+
|   BITMAPINFOHEADER exclusive    | BIB header
+--+-+----------------------------+
|14|4|size of this header         |
+--+-+----------------------------+
|18|4|width                       |
+--+-+----------------------------+
|22|4|height                      |
+--+-+----------------------------+
|26|2|number of color planes      |
+--+-+----------------------------+
|28|2|number of bits per pixel    |
+--+-+----------------------------+
|30|4|compression methd           |
+--+-+----------------------------+
|34|4|image size - raw bitmap data|
+--+-+----------------------------+
|38|4|horizontal resolution       |
+--+-+----------------------------+
|42|4|vertical resolution         |
+--+-+----------------------------+
|46|4|number of colors 2^n        |
+--+-+----------------------------+
|50|4|number of important colors  |
+--+-+----------------------------+
```

## Notes

Header fields use the `WORD` and `DWORD` data types from Windows. A word is 16 bits, whilst dword is 32 bits, making them representable as 4 and 8 hex digits respectively.

Within `xxd`, this means every column is a word long, whilst 2 columns represent a dword.

Integer values are all stored in little-endian format.

Rows are padded up to a multiple of 4 bytes. Thus the formula for bits per row is:

```
(bitsPerPixel * imageWidth + 31) / 32 * 32
```

Or

$$
\left\lfloor
  \frac{\text{bits per pixel} \cdot \text{image width} + 31}{32}
\right\rfloor
\cdot 32
$$

Using the C code `(bitsPerPixel * imageWidth + 31) & ~31`, we can round up to the nearest 32 bits.

An `~31` int is equal to `...100000`. An and operation causes the last 5 bits to be removed, effectively rounding down to the nearest multiple of 32.

Bitmap file header is 14 bytes, long. Use `xxd -l 14 demo.bmp`. The offset or starting of address of the pixel array is the last 4 bytes (2 columns).
