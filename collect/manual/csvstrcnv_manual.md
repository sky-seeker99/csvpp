# CSV Text Format Conversion Program

## 1. About the Program

This program was designed as a filter for CSVMAKE2.

It can also be run as a standalone program.

It converts CSV data so that Excel treats numbers as text when opening the file.

## 2. Usage

This is a console program.

### Syntax

```text
csvstrcnv [+all] [+num] [+numex] [+dbl] [+single] input_csv_file output_csv_file [-buff buffer_size]
```

### Options

- `-buff`: Specifies the buffer size used for each read/write operation (KB). This option is usually unnecessary, but a larger value may help with large files. The default is 10 KB.
- `+all`: Converts all data to text format.
- `+num`: Converts numeric data to text format.
- `+numex`: Converts values containing only numbers, `/`, and `:` to text format.
- `+dbl`: Converts only data enclosed in double quotation marks to text format.
- `+single`: Converts only data enclosed in single quotation marks to text format.

### Example

```text
csvstrcnv +all c:\csv\bbb.csv c:\csv\ccc.csv
```

### Using as a Filter Program with CSVMAKE2

```text
csvmake2 d:\aaa.xls -x "csvstrcnv +all" c:\csv\bbb.csv c:\csv\ccc.csv
```

## 3. Version History

- **Ver 1.00** Initial release.
- **Ver 1.01** Improved performance.
- **Ver 1.02** Added options.
- **Ver 1.02a** Bug fixes.
- **Ver 1.03** Added support for files larger than 4 GB and added the `-buff` option.
