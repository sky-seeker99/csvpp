# JPEG-to-CSV (YCbCr/RGB) Conversion Program

## 1. About the Program

This program exports image data from JPEG or BMP files as CSV containing YCbCr or RGB components.

## 2. Usage

This is a console program.

### Syntax

```text
jpegcsv jpeg_file csv_file RGB|YCbCr [bmp]
```

### Examples

```text
jpegcsv c:\csv\pict.jpg c:\csv\pict.csv RGB
```

Converts the image data to RGB components.

```text
jpegcsv c:\csv\pict.jpg c:\csv\pict.csv YCbCr
```

Converts the image data to YCbCr components.

```text
jpegcsv c:\csv\pict.bmp c:\csv\pict.csv YCbCr bmp
```

Converts a BMP file to YCbCr components.

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

## 4. Version History

- **Ver 1.00** Initial release.
- **Ver 1.01** Improved the conversion. Updated the manual; no program changes.
- **Ver 1.02** Added BMP file conversion support.
