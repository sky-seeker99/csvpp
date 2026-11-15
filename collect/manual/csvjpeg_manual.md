# CSV (YCbCr/RGB)-to-JPEG Conversion Program

## 1. About the Program

This program creates a JPEG image from a CSV file containing YCbCr or RGB component data.

## 2. Usage

This is a console program.

### Syntax

```text
csvjpeg csv_file jpeg_file [bmp]
```

### Examples

```text
csvjpeg c:\csv\pict.csv c:\csv\pict.jpg
csvjpeg c:\csv\pict.csv c:\csv\pict.bmp bmp
```

## 3. CSV File Format

### RGB Format

```text
//,X-Size,Y-Size
#SIZE,200,150
//,X-Point,Y-Point,R,G,B
#RGB,0,0,'h65,'h89,'h95
#RGB,1,0,'h9f,'hc3,'hcf
```

### YCbCr Format

```text
//,X-Size,Y-Size
#SIZE,200,150
//,X-Point,Y-Point,Y,Cb,Cr
#YCbCr,0,0,'h7f,'h8c,'h6d
#YCbCr,1,0,'hb9,'h8c,'h6d
```

### Specifying Numeric Values

Prefix data values and coordinates with `'h` or `0x` to specify hexadecimal values.

If no prefix is used, values are interpreted as decimal.

## 4. Version History

- **Ver 1.00** Initial release.
- **Ver 1.00** Updated the manual; no program changes.
- **Ver 1.01** Fixed a bug that caused an error when pixel data had only one digit. Added support for hexadecimal values prefixed with `0x` and for decimal values.
- **Ver 1.02** Added the ability to output BMP files.
- **Ver 1.03** Updated the program to use a changed CSV reading library; no functional changes.
