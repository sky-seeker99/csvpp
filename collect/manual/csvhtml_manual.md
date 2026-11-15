# CSV-to-HTML Conversion Program

## 1. About the Program

Converts CSV files to HTML files.

## 2. Usage

This is a console program.

### Syntax

```text
csvhtml csv_file html_file
```

### Example

```text
csvhtml c:\csv\in.csv c:\csv\out.html
```

## 3. Conversion Details

The following examples show how the conversion works.

### Example 1

**Before**

```text
#cmd,<!--AAAAA
#cmd,cmd0
#cmd,cmd1
#cmd,cmd2
#cmd,//-->
```

**After**

```html
<!--AAAAA
cmd0
cmd1
cmd2
//-->
```

### Example 2

**Before**

```text
#tag,HTML
#tag,HEAD
```

**After**

```html
<HTML><HEAD>
```

### Example 3

**Before**

```text
#tag,META,name,"GENERATOR"
#tag,META,content,"xxx WebSphere XXXXpage Builder V6.0.0 for Windows"
```

**After**

```html
<META name="GENERATOR" content="xxx WebSphere XXXXpage Builder V6.0.0 for Windows">
```

### Example 4

**Before**

```text
#tag,!DOCTYPE,HTML
#tag,!DOCTYPE,PUBLIC
#tag,!DOCTYPE,"-//W3C//DTD HTML 4.01 Transitional//EN"
```

**After**

```html
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
```

### Example 5

**Before**

```text
#tag,TD,width,"645"
#tag,B
#tag,FONT,face,"MS Gothic"
#wr,CSV
#tag,/FONT
#wr,-to-Verilog-HDL (RTL) Conversion Program
#tag,FONT,face,"MS Gothic"
#wr,Ver1.00
#tag,/FONT
#tag,A,href,"csvvrtl100.lzh"
#wr,csvvrtｌ100.LZH (148KB)
#tag,/A
#tag,/B
#tag,/TD
```

**After**

```html
<TD width="645"><B><FONT face="MS Gothic">CSV</FONT>-to-Verilog-HDL (RTL) Conversion Program <FONT face="MS Gothic">Ver1.00</FONT> <A href="csvvrtl100.lzh">csvvrtｌ100.LZH (148KB)</A></B></TD>
```

### Example 6

**Before**

```text
#tag,BR
#tagchg
#tag,BR
```

**After**

```html
<BR><BR>
```

### Example 7

**Before**

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

**After**

```html
<!doctype html public "-//w3c//dtd html 4.0 transitional//EN">
<html lang="en">
<head>
```

`#rc_mode` indicates that `#rcode` represents a line break.
After `#rc_mode` is specified, line breaks are inserted only at `#rcode` directives.

## 4. Version History

- **Ver 1.00** Initial release.
- **Ver 1.00a** Fixed a specification error.
- **Ver 1.00b** Bug fixes.
- **Manual update** Updated the manual; no program changes.
- **Ver 1.01** Added support for Level 2 kanji characters.
- **Ver 1.02** Prevented spaces surrounding text from being removed.
- **Ver 1.03** Added the `#rc_mode` and `#rcode` directives.
