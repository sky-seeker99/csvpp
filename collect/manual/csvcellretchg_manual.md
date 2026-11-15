# CSV Cell Line Break Conversion Program

## 1. About the Program

This program removes line breaks from data in CSV files exported by Excel or replaces them with a specified string.

## 2. Usage

This is a console program.

### Syntax

```text
csvcellretchg csv_file [replacement_string] [-dbl_no_cut] [-buff buffer_size]
```

### Options

- `-buff`: Specifies the buffer size used for each read/write operation (KB). This option is usually unnecessary, but a larger value may be useful for large files. The default is 10 KB.
- `-dbl_no_cut`: Preserves double quotation marks that would otherwise be removed.

### Examples

```text
csvcellretchg c:\csv\*.csv
```

Removes line breaks from `.csv` files in `c:\csv`.

```text
csvcellretchg c:\csv\*.csv @@@@@
```

Replaces line breaks in `.csv` files in `c:\csv` with `@@@@@`.

## 3. Version History

- **Ver 1.00** Initial release.
- **Ver 1.01** Added support for files larger than 4 GB and added the `-buff` option.
- **Ver 1.02** Added the `-dbl_no_cut` option.
