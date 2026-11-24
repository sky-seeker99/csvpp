# TAB-to-CSV Conversion Program

## 1. About the Program

This program was designed as a filter for CSVMAKE2.

It can also be run as a standalone program.

It converts TAB-delimited files to CSV files.

## 2. Usage

This is a console program.

### Syntax

```text
tabcsv tab_file csv_file [-buff buffer_size] [-dbl_no_cut]
```

### Options

- `-buff`: Specifies the buffer size used for each read/write operation (KB). This option is usually unnecessary, but a larger value may help with large files. The default is 10 KB.
- `-dbl_no_cut`: Preserves unnecessary double quotation marks instead of removing them.

### Example

```text
tabcsv c:\csv\bbb.txt c:\csv\ccc.csv
```

### Using as a Filter Program with CSVMAKE2

```text
csvmake2 d:\aaa.xls -x tabcsv c:\csv\bbb.txt c:\csv\ccc.txt
```

## 3. Version History

- **Ver 1.00** Initial release.
- **Ver 1.00** Updated the manual; no program changes.
- **Ver 1.01** Changed the program to run without an error when two or more parameters are specified.
- **Ver 1.02** Added support for Level 2 kanji characters.
- **Ver 1.03** Added support for files larger than 4 GB and added the `-buff` and `-dbl_no_cut` options.
