# CSVファイル→HTMLファイル変換プログラム

## 1. ソフトの紹介

CSVファイルからHTMLファイルに変換します。

## 2. 使用方法

本プログラムはコンソールプログラムです。

### 実行形式

```text
csvhtml CSVファイル名 HTMLファイル名
```

### 使用例

```text
csvhtml c:\csv\in.csv c:\csv\out.html
```

## 3. 変換内容

変換内容を以下に示します。

### 例1

**変換前**

```text
#cmd,<!--AAAAA
#cmd,cmd0
#cmd,cmd1
#cmd,cmd2
#cmd,//-->
```

**変換後**

```html
<!--AAAAA
cmd0
cmd1
cmd2
//-->
```

### 例2

**変換前**

```text
#tag,HTML
#tag,HEAD
```

**変換後**

```html
<HTML><HEAD>
```

### 例3

**変換前**

```text
#tag,META,name,"GENERATOR"
#tag,META,content,"xxx WebSphere XXXXpage Builder V6.0.0 for Windows"
```

**変換後**

```html
<META name="GENERATOR" content="xxx WebSphere XXXXpage Builder V6.0.0 for Windows">
```

### 例4

**変換前**

```text
#tag,!DOCTYPE,HTML
#tag,!DOCTYPE,PUBLIC
#tag,!DOCTYPE,"-//W3C//DTD HTML 4.01 Transitional//EN"
```

**変換後**

```html
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
```

### 例5

**変換前**

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

**変換後**

```html
<TD width="645"><B><FONT face="ＭＳ ゴシック">CSV</FONT>ファイル→Verilog-HDL（ＲＴＬ） 変換プログラム <FONT face="ＭＳ ゴシック">Ver1.00</FONT> <A href="csvvrtl100.lzh">csvvrtｌ100.LZH (148KB)</A></B></TD>
```

### 例6

**変換前**

```text
#tag,BR
#tagchg
#tag,BR
```

**変換後**

```html
<BR><BR>
```

### 例7

**変換前**

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

**変換後**

```html
<!doctype html public "-//w3c//dtd html 4.0 transitional//EN">
<html lang="ja">
<head>
```

`#rc_mode` は、`#rcode` が改行であることを示します。  
`#rc_mode` 以降は、`#rcode` 以外では改行しません。

## 4. 履歴

- **Ver 1.00**　初公開！
- **Ver 1.00a**　仕様ミスを修正。
- **Ver 1.00b**　バグフィックス。
- **マニュアル修正**　マニュアルを修正しました。プログラムの変更はありません。
- **Ver 1.01**　第2水準の漢字に対応。
- **Ver 1.02**　半角スペースが文字の両脇にあっても削除しないようにしました。
- **Ver 1.03**　`#rc_mode`、`#rcode` を追加。
