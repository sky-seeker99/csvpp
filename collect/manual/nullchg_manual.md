# NULL Removal and Replacement Program

## 1. About the Program

This program removes NULL characters from text files, especially CSV files, or replaces them with single-byte spaces or a specified unique string.

## 2. Usage

This is a console program.

### Syntax

```text
nullchg input_file output_file [-chgsp] [-chg replacement_string] [-buff buffer_size]
```

### Options

- `-buff`: Specifies the buffer size used for each read/write operation (KB). This option is usually unnecessary, but a larger value may help with large files. The default is 10 KB.
- `-chgsp`: Replaces NULL characters with single-byte spaces.
- `-chg`: Replaces NULL characters with the specified unique string.

If neither `-chgsp` nor `-chg` is specified, NULL characters are deleted.

### Examples

```text
nullchg.exe Sheet1.csv Sheet1.csv.del
nullchg.exe Sheet1.csv Sheet1.csv.sp -chgsp
nullchg.exe Sheet1.csv Sheet1.csv.uniq -chg [[NULL]]
```

## 3. Version History

- **Ver 1.00** Initial release.
