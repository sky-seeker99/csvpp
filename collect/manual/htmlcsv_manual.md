# HTML-to-CSV Conversion Program

## 1. About the Program

HTMLファイルをCSV fileに変換します。

## 2. Usage

This is a console program.

### Syntax

```text
htmlcsv [-r] HTML file name CSV file name
```

### Examples

```text
htmlcsv c:\csv\in.html c:\csv\out.csv
htmlcsv -r c:\csv\in.html c:\csv\out.csv
```

`-r` Optionを指定した場合は、改行まで変換します。  
（Line breaks inside tags are ignored.します。）

## 3. 変換内容

### Example 1

**変換前**

```html
<!--AAAAA
cmd0
cmd1
cmd2
//-->
```

**Converted to**

```text
#cmd,<!--AAAAA
#cmd,cmd0
#cmd,cmd1
#cmd,cmd2
#cmd,//-->
```

### Example 2

**変換前**

```html
<HTML><HEAD>
```

**Converted to**

```text
#tag,HTML
#tag,HEAD
```

### Example 3

**変換前**

```html
<META name="GENERATOR" content="xxx WebSphere XXXXpage Builder V6.0.0 for Windows">
```

**Converted to**

```text
#tag,META,name,"GENERATOR"
#tag,META,content,"xxx WebSphere XXXXpage Builder V6.0.0 for Windows"
```

### Example 4

**変換前**

```html
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
```

**Converted to**

```text
#tag,!DOCTYPE,HTML
#tag,!DOCTYPE,PUBLIC
#tag,!DOCTYPE,"-//W3C//DTD HTML 4.01 Transitional//EN"
```

### Example 5

**変換前**

```html
<TD width="645"><B><FONT face="ＭＳ ゴシック">CSV</FONT>ファイル→Verilog-HDL（ＲＴＬ） 変換Program <FONT face="ＭＳ ゴシック">Ver1.00</FONT> <A href="csvvrtl100.lzh">csvvrtｌ100.LZH (148KB)</A></B></TD>
```

**Converted to**

```text
#tag,TD,width,"645"
#tag,B
#tag,FONT,face,"MS Gothic"
#wr,CSV
#tag,/FONT
#wr,File-to-Verilog-HDL (RTL) Conversion Program
#tag,FONT,face,"MS Gothic"
#wr,Ver1.00
#tag,/FONT
#tag,A,href,"csvvrtl100.lzh"
#wr,csvvrtｌ100.LZH (148KB)
#tag,/A
#tag,/B
#tag,/TD
```

### Example 6

**変換前**

```html
<BR><BR>
```

**Converted to**

```text
#tag,BR
#tagchg
#tag,BR
```

### Example 7

`-r` Optionを付けて実行した場合。

**変換前**

```html
<!doctype html public "-//w3c//dtd html 4.0 transitional//EN">
<html lang="ja">
<head>
```

**Converted to**

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

## 4. Version History

- **Ver 1.00**　初公開！
- **Ver 1.00a**　仕様ミスを修正。
- **Ver 1.01**　第2水準の漢字に対応。
- **Ver 1.02**　いろいろなバグをフィックス。
- **Ver 1.03**　リターンコードまで詳細に調べるModeを追加。
