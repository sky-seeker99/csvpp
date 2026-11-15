# CSV (YCbCr/RGB)-to-JPEG Conversion Program

## 1. About the Program

Creates a JPEG image from a CSV file containing YCbCr or RGB components.

## 2. Usage

This is a console program.

### Syntax

```text
csvjpeg CSV file JPEGファイル [bmp]
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

データおよび座標は、先頭に `'h` または `0x` を付けると16進数になります。

If no prefix is used, the value is interpreted as decimal.

## 4. Version History

- **Ver 1.00**　初公開！
- **Ver 1.00**　マニュアルを修正しました。Programの変更はありません。
- **Ver 1.01**　画素データが1桁だとエラーになる不具合を修正。  
  また、`0x` による16進数指定と、10進数指定に対応。
- **Ver 1.02**　BMPファイルを出力できるようにしました。
- **Ver 1.03**　CSV file読込みライブラリの変更に伴うProgramの変更。機能変更はありません。
