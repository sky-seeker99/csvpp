# Shift-JIS/EUC-JP Conversion Program 2

## 1. About the Program

This console program converts between Shift-JIS and EUC-JP encodings.

Wildcards can be used in file names.

## 2. Usage

This is a console program.

### Syntax

```text
eucsjis2 sjis_euc|euc_sjis input_file output_file
```

Specify the full paths to the input and output files.

### Conversion Modes

- `sjis_euc`: Converts Shift-JIS to EUC-JP. Line endings are converted to `0x0A`.
- `euc_sjis`: Converts EUC-JP to Shift-JIS. Line endings are converted to `0x0D, 0x0A`.

### Selecting the Line Ending Format

- `sjis_euc_win` / `euc_sjis_win`: Converts line endings to `0x0D, 0x0A`.
- `sjis_euc_unix` / `euc_sjis_unix`: Converts line endings to `0x0A`.

### Standard Input and Output

Specify `-` as the input file name to read from standard input.

Specify `-` as the output file name to write to standard output.

Note that line endings written to standard output are always `0x0D, 0x0A`.

### Examples

```text
eucsjis2 sjis_euc c:\csv\in.txt c:\csv\out.txt
type c:\csv\in.txt | eucsjis2 euc_sjis - - > c:\csv\out.txt
```

## 3. Converting User-Defined Characters

To convert user-defined characters in Shift-JIS encoded text, place an `eucsjis.csv` file in the directory containing `eucsjis.exe`.

Define the conversion rules in `eucsjis.csv`.

The included `eucsjis.csv` contains rules researched by the author for converting Shift-JIS codes to EUC-JP codes.

### Format

```text
#sjis_euc,first_byte_code,second_byte_code_upper_limit,second_byte_code_lower_limit,first_byte_code_offset,second_byte_code_offset
#euc_sjis,first_byte_code,second_byte_code_upper_limit,second_byte_code_lower_limit,first_byte_code_offset,second_byte_code_offset
```

- `#sjis_euc`: Specifies rules for converting Shift-JIS codes to EUC-JP codes.
- `#euc_sjis`: Specifies rules for converting EUC-JP codes to Shift-JIS codes.

### Configuration Example

```text
#sjis_euc,250,73,64,2,177
#sjis_euc,250,83,74,-77,107
```

## 4. Version History

- **Ver 1.00** Initial release.
- **Ver 1.02** Added the ability to specify user-defined character conversion rules in a file.
- **Ver 1.02a** Fixed a bug that added unnecessary carriage return codes.
- **Ver 1.03** Improved performance.
