# CSVファイル（YCbCr/RGB）→JPEGファイル変換プログラム

## 1. ソフトの紹介

本プログラムは、YCbCr成分またはRGB成分に変換したCSVファイルから、JPEGファイルを出力するプログラムです。

## 2. 使用方法

本プログラムはコンソールプログラムです。

### 実行形式

```text
csvjpeg CSVファイル JPEGファイル [bmp]
```

### 使用例

```text
csvjpeg c:\csv\pict.csv c:\csv\pict.jpg
csvjpeg c:\csv\pict.csv c:\csv\pict.bmp bmp
```

## 3. CSVファイル

### RGBの場合

```text
//,X-Size,Y-Size
#SIZE,200,150
//,X-Point,Y-Point,R,G,B
#RGB,0,0,'h65,'h89,'h95
#RGB,1,0,'h9f,'hc3,'hcf
```

### YCbCrの場合

```text
//,X-Size,Y-Size
#SIZE,200,150
//,X-Point,Y-Point,Y,Cb,Cr
#YCbCr,0,0,'h7f,'h8c,'h6d
#YCbCr,1,0,'hb9,'h8c,'h6d
```

### 数値の指定方法

データおよび座標は、先頭に `'h` または `0x` を付けると16進数になります。

先頭に何も付けない場合は、10進数として指定します。

## 4. 履歴

- **Ver 1.00**　初公開！
- **Ver 1.00**　マニュアルを修正しました。プログラムの変更はありません。
- **Ver 1.01**　画素データが1桁だとエラーになる不具合を修正。  
  また、`0x` による16進数指定と、10進数指定に対応。
- **Ver 1.02**　BMPファイルを出力できるようにしました。
- **Ver 1.03**　CSVファイル読込みライブラリの変更に伴うプログラムの変更。機能変更はありません。
