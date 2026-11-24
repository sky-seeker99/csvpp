# Text File Concatenation and Splitting Program

## 1. About the Program

This console program concatenates text files and extracts selected portions.

## 2. Usage

This is a console program.

Syntax:

```text
txt_catcut in_file out_file [-new] [-r_offset offset] [-w_offset offset] [-size size] [-buff buffer_size]
```

### Options

If no options are specified, the contents of `in_file` are appended to `out_file`.

| Option | Description |
|---|---|
| `-new` | Creates a new file. |
| `-r_offset` | Specifies the input line offset. If omitted, reading starts at the beginning of the file. |
| `-w_offset` | Specifies the output line offset. If omitted, data is appended to the end of the file. |
| `-size` | Specifies the amount of data to read and write. If omitted, the value is the total number of lines in the input file minus the input line offset. |
| `-buff` | Specifies the buffer size used for each read/write operation (KB). This option is usually unnecessary, but a larger value may be useful for large files. The default is 10 KB. |

### Notes

- Line offsets are counted starting from **1** for the first line.
- Numbers can be specified in hexadecimal by prefixing them with `0x`. For example: `0x1000`, `0xa0df`.

## 3. Examples

### Concatenating Files

The following example concatenates the contents of `in1.txt`, `in2.txt`, and `in3.txt` in order into `out.txt`.

```text
txt_catcut in1.txt out.txt -new
txt_catcut in2.txt out.txt
txt_catcut in3.txt out.txt
```

### Splitting into 100-Byte Blocks

The following example splits the input file into 100-byte blocks.

```text
txt_catcut in.txt out1.txt -new -size 100
txt_catcut in.txt out2.txt -new -size 100 -r_offset 101
txt_catcut in.txt out3.txt -new -size 100 -r_offset 201
```

## 4. Version History

- Ver 1.00 Initial release.
- Ver 1.01 Added support for files larger than 4 GB.
