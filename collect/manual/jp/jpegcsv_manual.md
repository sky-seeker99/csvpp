# JPEGファイル→CSVファイル（YCbCr/RGB）変換プログラム

## 1. ソフトの紹介

本プログラムは、JPEGファイルまたはBMPファイルをYCbCr成分またはRGB成分に変換したデータを、CSVファイル形式で出力するプログラムです。

## 2. 使用方法

本プログラムはコンソールプログラムです。

### 実行形式

```text
jpegcsv JPEGファイル CSVファイル RGB|YCbCr [bmp]
```

### 使用例

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

## 4. 履歴

- **Ver 1.00**　初公開！
- **Ver 1.01**　変換を強化。  
  マニュアルを修正しました。プログラムの変更はありません。
- **Ver 1.02**　BMPファイル変換機能を追加。
