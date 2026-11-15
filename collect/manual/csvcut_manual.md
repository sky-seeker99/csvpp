# CSV Field Extraction Program

## 1. About the Program

This program extracts specified fields from a CSV file and creates a new CSV file.

## 2. Usage

This is a console program.

Syntax:

```text
csvcut input_csv_file output_csv_file fields_to_extract
```

### Example

```text
csvcut c:\csv\int.csv c:\csv\out.csv 1,5-9,11
```

To use standard input and output, run the command as follows:

```text
type c:\csv\int.csv | csvcut - - 1,5-9,11 > c:\csv\out.csv
```

### Specifying Fields

- Field numbering starts at **1**.
- Specify `-` as the input CSV file name to read from standard input.
- Specify `-` as the output CSV file name to write to standard output.
- Separate field numbers with commas (`,`).
- Use a hyphen (`-`) to specify a range of fields.

For example, specifying:

```text
1,5-9,11
```

extracts fields **1, 5, 6, 7, 8, 9, and 11**.

## 3. Version History

- Ver 1.00 Initial release.
- Ver 1.01 Added standard input and output support; changed field numbering to start at 1.
- Ver 1.02 Added support for double quotation marks.
- Ver 1.03 Added support for Level 2 kanji characters.
- Ver 1.04 Fixed a bug that removed half-width spaces.
- Ver 1.05 Changed the conversion engine so fields can be processed regardless of their length.
