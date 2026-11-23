# Excel-to-CSV Conversion Program

## 1. About the Program

This utility exports every worksheet in an Excel workbook as a CSV file.

It is useful when you need to create CSV files without opening Excel.

## 2. Usage

This is a console program.

Syntax:

```text
csvmake excel_file output_directory [filter_program] [extension] [-tmp] [-proc] [-s worksheet_name worksheet_name ...] [-S worksheet_name worksheet_name ...]
```

### Options

- **`-s`**: Specifies the worksheet names to convert. Wildcards can be used.
- **`-S`**: Specifies the worksheet names to exclude from conversion. Wildcards can be used.
- **`-tmp`**: Writes each CSV file to a temporary file first, then copies it to the destination.
- **`-proc`**: After `csvmake` runs, checks for any remaining Excel processes and terminates them.

### Examples

```text
csvmake aaa.xls c:\csv
csvmake aaa.xls c:\csv csvtab txt
csvmake aaa.xls c:\csv -s aaa bbb sheet* -S sheet_x*
csvmake aaa.xls c:\csv csvtab txt -s aaa bbb sheet* -S sheet_x*
```

## 3. Filter Programs

A filter program converts a file after it has been exported to CSV.

If you create your own filter program or batch file, use the following arguments:

1. **Argument 1**: Source CSV file
2. **Argument 2**: Output file
3. **Argument 3**: Sequence number (three digits, zero-padded)
4. **Argument 4**: Output directory name
5. **Argument 5**: Worksheet name

## 4. Convenient Use

To export files to the `c:\csv` directory, create a batch file as follows.

### Batch File Contents

```bat
csvmake %1 c:\csv
```

After creating this batch file, drag and drop an Excel workbook (`.xls` file) onto it.

The program starts and creates the CSV files.

## 5. Version History

- Ver 1.00 Initial release.
- Ver 1.01 Added filter program support.
- Manual update; no program changes.
- Ver 1.02 Added the ability to specify worksheets to include or exclude from conversion.
- Ver 1.03 Added parameters for filter programs.
- Ver 1.04 Fixed a bug that occurred when an Excel file was specified using a relative path.
- Ver 1.05 Added an error message when the output destination cannot be written to.
- Ver 1.06 Fixed an issue with using a relative path for the output destination.
- Ver 1.07 Fixed a bug that caused the program to fail when the output directory contained spaces and a filter program was used.
- Ver 1.08 Added the `-proc` and `-tmp` options.
