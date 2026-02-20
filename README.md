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
