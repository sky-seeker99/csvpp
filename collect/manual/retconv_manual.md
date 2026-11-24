# CSV Line Break Conversion for Excel

(`0x0D 0x0A` → `0x0A`)

## 1. About the Program

This program was designed as a filter for CSVMAKE2.

It can also be run as a standalone program.

It converts line breaks in CSV files to a format that is easier to use in Excel.

When a CSV file containing line breaks in its data is opened in Excel, a middle dot may appear inside a cell. This happens because Excel uses `0x0A (LF)` for line breaks within cells.

For example, suppose you create the following CSV file in Notepad:

```text
a,b,"c
d"
```

The line endings (CR: `0x0D`, LF: `0x0A`) can be shown as follows:

```text
a,b,"c[CRLF]
d"
```

When this file is opened in Excel, the `c[CRLF]d` portion may appear as:

```text
c·d
```

The middle dot represents `0x0D` (CR).

This program removes the CR represented by that dot.

## 2. Usage

This is a console program.

### Syntax

```text
retconv input_csv_file output_csv_file [-buff buffer_size]
```

### Options

- `-buff`: Specifies the buffer size used for each read/write operation (KB). This option is usually unnecessary, but a larger value may help with large files. The default is 10 KB.

### Example

```text
retconv c:\csv\bbb.csv c:\csv\ccc.csv
```

### Using as a Filter Program with CSVMAKE2

```text
csvmake2 d:\aaa.xls -x retconv c:\csv\bbb.csv c:\csv\ccc.csv
```

## 3. Version History

- **Ver 1.00** Initial release.
- **Ver 1.01** Added an error message when the input and output file names are the same.
- **Ver 1.01** Updated the manual; no program changes.
- **Ver 1.02** Changed the program to run without an error when two or more parameters are specified.
- **Ver 1.03** Added support for Level 2 kanji characters.
- **Ver 1.05** Added support for files larger than 4 GB and added the `-buff` option.
