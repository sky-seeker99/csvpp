# CSV-to-TAB Conversion Program

## 1. About the Program

This program was designed as a filter for CSVMAKE.

It can also be run as a standalone program.

It converts CSV files to TAB-delimited files.

## 2. Usage

This is a console program.

### Syntax

```text
csvtab csv_file tab_file [-buff buffer_size] [-dbl_no_cut]
```

### Options

- `-buff`: Specifies the buffer size used for each read/write operation (KB). This option is usually unnecessary, but a larger value may help with large files. The default is 10 KB.
- `-dbl_no_cut`: Preserves double quotation marks that would otherwise be removed.

### Examples

```text
csvtab c:\csv\bbb.csv c:\csv\ccc.txt
```

```text
type c:\csv\bbb.csv | csvtab - - > c:\csv\ccc.txt
```

Specify `-` as the CSV file name to read from standard input. Specify `-` as the TAB file name to write to standard output.

### Using as a Filter Program with CSVMAKE

```text
csvmake d:\aaa.xls c:\csv csvtab txt
```

## 3. Version History

- **Ver 1.00** Initial release.
- **Ver 1.00** Updated the manual; no program changes.
- **Ver 1.01** Changed the program to run without an error when two or more parameters are specified.
- **Ver 1.02** Added support for Level 2 kanji characters.
- **Ver 1.03** Prevented spaces around text from being removed.
- **Ver 1.04** Fixed a bug that added a line break to the final line. Added standard input and output support.
- **Ver 1.05** Added support for files larger than 4 GB and added the `-buff` and `-dbl_no_cut` options.
- **Ver 1.06** Fixed a bug in handling data enclosed in double quotation marks.
