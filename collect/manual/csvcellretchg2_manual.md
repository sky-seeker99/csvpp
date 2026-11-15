# CSV Cell Line Break Conversion Program 2

## 1. About the Program

This program removes line breaks from data in CSV files exported by Excel or replaces them with a specified string.

## 2. Usage

This is a console program.

### Syntax

```text
csvcellretchg2 input_file output_file [replacement_string] [-dbl_no_cut] [-buff buffer_size]
```

Specify the full paths to the input and output files.

### Options

- `-buff`: Specifies the buffer size used for each read/write operation (KB). This option is usually unnecessary, but a larger value may be useful for large files. The default is 10 KB.
- `-dbl_no_cut`: Preserves double quotation marks that would otherwise be removed.

### Examples

```text
csvcellretchg2 c:\csv\in.csv c:\csv\out.csv
```

Removes line breaks from the CSV file.

```text
csvcellretchg2 c:\csv\in.csv c:\csv\out.csv @@@@@
```

Replaces line breaks in the CSV file with `@@@@@`.

### Standard Input and Output

Specify `-` as the input file name to read from standard input.
Specify `-` as the output file name to write to standard output.

Note that line endings written to standard output are always `0x0D,0x0A`.

### Standard Input and Output Example

```text
type c:\csv\in.csv | csvcellretchg2 - - > c:\csv\out.csv
```

## 3. Version History

- **Ver 1.01** Initial release.
- **Ver 1.02** Added the `-dbl_no_cut` option.
