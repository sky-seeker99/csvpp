# HTML-to-CSV Conversion Program

## 1. About the Program

Converts HTML files to CSV files.

## 2. Usage

This is a console program.

### Syntax

```text
htmlcsv [-r] html_file csv_file
```

### Examples

```text
htmlcsv c:\csv\in.html c:\csv\out.csv
htmlcsv -r c:\csv\in.html c:\csv\out.csv
```

With the `-r` option, line breaks are also processed. Line breaks inside tags are ignored.

## 3. Conversion Details

### Example 1

**Before**

```html
<!--AAAAA
cmd0
cmd1
cmd2
//-->
```

**After**

```text
#cmd,<!--AAAAA
#cmd,cmd0
#cmd,cmd1
#cmd,cmd2
#cmd,//-->
```

### Example 2

**Before**

```html
<HTML><HEAD>
```

**After**

```text
#tag,HTML
#tag,HEAD
```

### Example 3

**Before**

```html
<META name="GENERATOR" content="xxx WebSphere XXXXpage Builder V6.0.0 for Windows">
```

**After**

```text
#tag,META,name,"GENERATOR"
#tag,META,content,"xxx WebSphere XXXXpage Builder V6.0.0 for Windows"
```

### Example 4

**Before**

```html
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
```

**After**

```text
#tag,!DOCTYPE,HTML
#tag,!DOCTYPE,PUBLIC
#tag,!DOCTYPE,"-//W3C//DTD HTML 4.01 Transitional//EN"
```

### Example 5

**Before**

```html
<TD width="645"><B><FONT face="MS Gothic">CSV</FONT>file-to-Verilog-HDL (RTL) Conversion Program <FONT face="MS Gothic">Ver1.00</FONT> <A href="csvvrtl100.lzh">csvvrtｌ100.LZH (148KB)</A></B></TD>
```

**After**

```text
#tag,TD,width,"645"
#tag,B
#tag,FONT,face,"MS Gothic"
#wr,CSV
#tag,/FONT
#wr,file-to-Verilog-HDL (RTL) Conversion Program
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

**Before**

```html
<BR><BR>
```

**After**

```text
#tag,BR
#tagchg
#tag,BR
```

### Example 7

When run with the `-r` option:

**Before**

```html
<!doctype html public "-//w3c//dtd html 4.0 transitional//EN">
<html lang="en">
<head>
```

**After**

```text
#rc_mode
#tag,!doctype,html
#tag,!doctype,public
#tag,!doctype,"-//w3c//dtd html 4.0 transitional//EN"
#rcode
#tag,html,lang,"en"
#rcode
#tag,head
#rcode
```

`#rc_mode` indicates that `#rcode` is used to represent a line break.
`#rcode` represents a line break in the text file.

## 4. Version History

- **Ver 1.00** Initial release.
- **Ver 1.00a** Fixed a specification error.
- **Ver 1.01** Added support for Level 2 kanji characters.
- **Ver 1.02** Fixed various bugs.
- **Ver 1.03** Added a mode for detailed inspection of line ending codes.
