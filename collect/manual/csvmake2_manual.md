# CSV-to-Excel Conversion Program

## 1. About the Program

This program imports the contents of CSV files into an Excel workbook.

The CSV file name is used as the worksheet name. If a worksheet with that name already exists, its contents are copied and only the data is pasted into the matching sheet.

Formatting, shapes, and other non-data elements are preserved.

> **Notes**
> - If the Excel workbook does not exist, an error occurs. To create a new workbook, create an empty Excel file first.
> - Worksheet names that are 32 or more single-byte characters long are truncated to 31 characters.

## 2. Usage

This is a console program.

Syntax:

```text
csvmake2 excel_file [-x filter_program] [-nv] [-new] [-paste] [-xml] [-proc] csv_file1 csv_file2 ... csv_filen
```

### Options

- **`-proc`**: After `csvmake2` runs, checks for any remaining Excel processes and terminates them.
- **`-nv`**: Hides the Excel window.
- **`-new`**: Creates a new Excel workbook.
- **`-xml`**: Outputs in XML format. Use `xml` as the Excel file name extension.
- **`-paste`**: Pastes formulas from the CSV file into the Excel workbook as formulas.

For example, suppose a CSV file contains:

```text
a,"=A1"
```

Without any options, only the following result is copied to the Excel workbook:

```text
a,a
```

With the `-paste` option, the result is:

```text
a,=A1
```

### Examples

```text
csvmake2 d:\aaa.xls c:\csv\bbb.csv c:\csv\ccc.csv
csvmake2 d:\aaa.xls -nv c:\csv\bbb.csv c:\csv\ccc.csv
csvmake2 d:\aaa.xls -x retconv c:\csv\bbb.csv c:\csv\ccc.csv
```

## 3. Filter Programs

A filter program converts a CSV file before it is imported into the Excel workbook.

The converted CSV file is then added to the workbook.

If you create your own filter program or batch file, use the following arguments:

1. **Argument 1**: Source CSV file
2. **Argument 2**: Converted CSV file

## 4. Convenient Use

To output to `d:\aaa.xls`, create a batch file as follows.

### Batch File Contents

```bat
csvmake d:\aaa.xls %1 %2 %3 %4 %5 %6 %7 %8 %9
```

After creating this batch file, select multiple CSV files and drag and drop them onto the batch file.

The program starts and adds or updates worksheets in `d:\aaa.xls`.

## 5. Notes

In Excel 2003, set the macro security level as follows:

**Tools → Options → Macro Security**

- Change the security level from **High** to **Medium**.
- Remove trusted publishers.

## 6. Version History

- Ver 1.00 Initial release.
- Ver 1.01 Changed the program to save the workbook after each copy.
- Ver 1.02 Added filter program support.
- Manual update; no program changes.
- Ver 1.03 Added an option to hide the Excel window, enabled execution with relative paths, and fixed bugs.
- Ver 1.04 Fixed a bug in the `-nv` option.
- Ver 1.05 Worksheet names that are 32 or more single-byte characters long are now truncated to 31 characters.
- Ver 1.06 Changed the program to display the CSV file, including error messages, even when the Excel workbook is in use.
- Ver 1.07 Changed the program to create a new workbook if the specified Excel file does not exist.
- Ver 1.08 Added the `-new` option.
- Ver 1.09 Fixed a bug that caused failures when the CSV file path contained spaces while using a filter program.
- Ver 1.10 Added the `-paste` option.
- Ver 1.11 Added the `-xml` option.
- Ver 1.12 Added the `-proc` option.
