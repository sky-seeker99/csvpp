# JPEG-to-CSV (YCbCr/RGB) Conversion Program

## 1. About the Program

Exports JPEG or BMP image data as CSV containing YCbCr or RGB components.

## 2. Usage

This is a console program.

### Syntax

```text
jpegcsv JPEGファイル CSV file RGB|YCbCr [bmp]
```

### Examples

```text
jpegcsv c:\csv\pict.jpg c:\csv\pict.csv RGB
```

RGB成分に変換します。

```text
jpegcsv c:\csv\pict.jpg c:\csv\pict.csv YCbCr
```

YCbCr成分に変換します。

```text
jpegcsv c:\csv\pict.bmp c:\csv\pict.csv YCbCr bmp
```

BMPファイルをYCbCr成分に変換します。

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

- **Ver 1.00**　初公開！
- **Ver 1.01**　変換を強化。  
  マニュアルを修正しました。Programの変更はありません。
- **Ver 1.02**　BMPファイル変換機能を追加。
