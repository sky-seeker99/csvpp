# HTMLファイル→CSVファイル変換プログラム

## 1. ソフトの紹介

HTMLファイルをCSVファイルに変換します。

## 2. 使用方法

本プログラムはコンソールプログラムです。

### 実行形式

```text
htmlcsv [-r] HTMLファイル名 CSVファイル名
```

### 使用例

```text
htmlcsv c:\csv\in.html c:\csv\out.csv
htmlcsv -r c:\csv\in.html c:\csv\out.csv
```

`-r` オプションを指定した場合は、改行まで変換します。  
（タグ内の改行は無視します。）

## 3. 変換内容

### 例1

**変換前**

```html
<!--AAAAA
cmd0
cmd1
cmd2
//-->
```

**変換後**

```text
#cmd,<!--AAAAA
#cmd,cmd0
#cmd,cmd1
#cmd,cmd2
#cmd,//-->
```

### 例2

**変換前**

```html
<HTML><HEAD>
```

**変換後**

```text
#tag,HTML
#tag,HEAD
```

### 例3

**変換前**

```html
<META name="GENERATOR" content="xxx WebSphere XXXXpage Builder V6.0.0 for Windows">
```

**変換後**

```text
#tag,META,name,"GENERATOR"
#tag,META,content,"xxx WebSphere XXXXpage Builder V6.0.0 for Windows"
```

### 例4

**変換前**

```html
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
```

**変換後**

```text
#tag,!DOCTYPE,HTML
#tag,!DOCTYPE,PUBLIC
#tag,!DOCTYPE,"-//W3C//DTD HTML 4.01 Transitional//EN"
```

### 例5

**変換前**

```html
<TD width="645"><B><FONT face="ＭＳ ゴシック">CSV</FONT>ファイル→Verilog-HDL（ＲＴＬ） 変換プログラム <FONT face="ＭＳ ゴシック">Ver1.00</FONT> <A href="csvvrtl100.lzh">csvvrtｌ100.LZH (148KB)</A></B></TD>
```

**変換後**

```text
#tag,TD,width,"645"
#tag,B
#tag,FONT,face,"ＭＳ ゴシック"
#wr,CSV
#tag,/FONT
#wr,ファイル→Verilog-HDL（ＲＴＬ） 変換プログラム
#tag,FONT,face,"ＭＳ ゴシック"
#wr,Ver1.00
#tag,/FONT
#tag,A,href,"csvvrtl100.lzh"
#wr,csvvrtｌ100.LZH (148KB)
#tag,/A
#tag,/B
#tag,/TD
```

### 例6

**変換前**

```html
<BR><BR>
```

**変換後**

```text
#tag,BR
#tagchg
#tag,BR
```

### 例7

`-r` オプションを付けて実行した場合。

**変換前**

```html
<!doctype html public "-//w3c//dtd html 4.0 transitional//EN">
<html lang="ja">
<head>
```

**変換後**

```text
#rc_mode
#tag,!doctype,html
#tag,!doctype,public
#tag,!doctype,"-//w3c//dtd html 4.0 transitional//EN"
#rcode
#tag,html,lang,"ja"
#rcode
#tag,head
#rcode
```

`#rc_mode` は、`#rcode` があることを示します。  
`#rcode` は、テキストファイル上での改行を示します。

## 4. 履歴

- **Ver 1.00**　初公開！
- **Ver 1.00a**　仕様ミスを修正。
- **Ver 1.01**　第2水準の漢字に対応。
- **Ver 1.02**　いろいろなバグをフィックス。
- **Ver 1.03**　リターンコードまで詳細に調べるモードを追加。
