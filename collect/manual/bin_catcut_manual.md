# Binary File Concatenation and Splitting Program

## 1. About the Program

This console program concatenates binary files and extracts selected portions of a file.

## 2. Usage

This is a console program.

### Syntax

```text
bin_catcut in_file out_file [-new] [-r_offset offset] [-w_offset offset] [-size size] [-buff buffer_size]
```

If no options are specified, the contents of `in_file` are appended to `out_file`.

### Options

- `-new`: Creates a new output file.
- `-r_offset`: Specifies the byte offset in the input file. If omitted, reading starts at the beginning of the file.
- `-w_offset`: Specifies the byte offset in the output file. If omitted, data is appended to the end of the file.
- `-size`: Specifies the number of bytes to read and write. If omitted, the value is the input file size minus the input file offset.
- `-buff`: Specifies the buffer size used for each read/write operation (KB). This option is usually unnecessary, but a larger value may be useful for large files. The default is 10 KB.

Note: Numbers can be specified in hexadecimal by prefixing them with `0x`.
Examples: `0x1000`, `0xa0df`

### Examples

#### Concatenating Files

```text
bin_catcut in1.bin out.bin -new
bin_catcut in2.bin out.bin
bin_catcut in3.bin out.bin
```

#### Splitting into 100-Byte Blocks

```text
bin_catcut in.bin out1.bin -new -size 100
bin_catcut in.bin out2.bin -new -size 100 -r_offset 100
bin_catcut in.bin out3.bin -new -size 100 -r_offset 200
```

## 3. Version History

- **Ver 1.00** Initial release.
- **Ver 1.01** Added support for files larger than 4 GB.
- **Ver 1.01a** Bug fixes.
- **Ver 1.02** Fixed a buffer size bug.
