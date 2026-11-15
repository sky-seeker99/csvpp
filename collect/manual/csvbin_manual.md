# CSV-to-Binary Conversion Program

## 1. About the Program

This program creates a binary file from data described in a CSV file.

It can also apply patches to binary files.

## 2. Usage

This is a console program.

### Syntax

```text
csvbin csv_file binary_file [-buff buff_size] [-tag tag_name]
```

### Options

- `-buff`: Specifies the buffer size used for each read/write operation (KB). This option is usually unnecessary, but a larger value may be useful for large files. The default is 10 KB.
- `-tag`: The default tag is `#chg`. If `tag_name` is specified, that key is used instead of `#chg`.

Note: Numbers can be specified in hexadecimal by prefixing them with `0x`.
Examples: `0x1000`, `0xa0df`

### Example

```text
csvbin c:\csv\pict.csv c:\csv\pict.jpg
```

## 3. CSV File Format

### Example

```text
#chg,'h00000000,'hFF,'hD8,'hFF,'hE0
#chg,'h00000010,00,64,00,00,FF
#chg,'h00000020,'b1110111,'b1110000
```

Prefix a value with `'h` to specify hexadecimal or with `'b` to specify binary. Values without a prefix are treated as decimal.

### `#chg` Directive

The `#chg` directive writes data at the specified position in the file.

#### Syntax

```text
#chg,position,data1,data2,...,dataN
```

### Changing the `#chg` Tag

To use `#key` instead of `#chg`, specify the `-tag` option as follows:

```text
csvbin c:\csv\pict.csv c:\csv\pict.jpg -tag #key
```

## 4. Version History

- **Ver 1.00** Initial release.
- **Ver 1.00** Updated the manual; no program changes.
- **Ver 1.01** Updated the program to use a changed CSV reading library; no functional changes.
- **Ver 1.02** Added the `-buff` option and support for files larger than 4 GB.
- **Ver 1.03** Fixed CSV reading so that line breaks inside cells are handled correctly.
- **Ver 1.04** Added the `-tag` option.
