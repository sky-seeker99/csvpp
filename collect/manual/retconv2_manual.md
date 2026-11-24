# CSV Line Break Conversion for Excel 2

(`0x0D` → `0x0D 0x0A`)

## 1. About the Program

This program was designed as a filter for CSVMAKE.

It can also be run as a standalone program.

It performs the reverse conversion of `retconv`, converting CR line endings to CRLF.

## 2. Usage

This is a console program.

### Syntax

```text
retconv2 input_csv_file output_csv_file [-buff buffer_size]
```

### Options

- `-buff`: Specifies the buffer size used for each read/write operation (KB). This option is usually unnecessary, but a larger value may help with large files. The default is 10 KB.

### Example

```text
retconv2 c:\csv\bbb.csv c:\csv\ccc.csv
```

### Using as a Filter Program with CSVMAKE

```text
csvmake d:\aaa.xls c:\csv retconv2 csv
```

## 3. Version History

- **Ver 1.00** Initial release.
- **Ver 1.00** Updated the manual; no program changes.
- **Ver 1.01** Changed the program to run without an error when two or more parameters are specified.
- **Ver 1.02** Added support for Level 2 kanji characters.
- **Ver 1.05** Added support for files larger than 4 GB and added the `-buff` option.
