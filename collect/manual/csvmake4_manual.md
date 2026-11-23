# Extended CSV-to-Excel Conversion Program

## 1. About the Program

Adds the contents of all CSV files in a specified directory to an Excel workbook.

Each CSV file name is used as a worksheet name. If a worksheet with that name already exists, its contents are copied and only the data is pasted into the matching sheet.

Formatting, shapes, and other non-data elements are preserved.

## 2. Usage

This is a console program.

### Syntax

```text
csvmake4 excel_file csv_directory [-nv] [-new] [-proc] [-xml] [-paste] [filter_program] [extension]
```

### Options

- `-proc`: After `csvmake4` runs, checks for any remaining Excel processes and terminates them.
- `-nv`: Hides the Excel window.
- `-new`: Creates a new Excel workbook.
- `-xml`: Outputs in XML format. Use `xml` as the Excel file extension.
- `-paste`: Pastes formula strings from the CSV file into the Excel workbook as formulas.

For example, suppose a CSV file contains:

```text
a,"=A1"
```

Without the `-paste` option, only the following result is copied to the Excel workbook:

```text
a,a
```

With the `-paste` option, the result is:

```text
a,=A1
```

### Examples

```text
csvmake4 d:\aaa.xls c:\csv
csvmake4 d:\aaa.xls c:\csv tabcsv txt
csvmake4 d:\aaa.xls c:\csv -nv
csvmake4 d:\aaa.xls c:\csv -nv -new
```

## 3. Filter Programs

A filter program converts files to CSV before they are imported into the Excel workbook.

The converted CSV files are then added to the workbook.

If you create your own filter program or batch file, use the following arguments:

1. **Argument 1**: Source file
2. **Argument 2**: Converted CSV file

## 4. Convenient Use

To output to `d:\aaa.xls`, create a batch file as follows.

### Batch File Contents

```bat
csvmake d:\aaa.xls %1
```

After creating this batch file, select the directory containing the CSV files and drag and drop it onto the batch file.

The program starts and adds or updates worksheets in `d:\aaa.xls`.

## 5. Version History

- **Ver 1.00** Initial release.
- **Ver 1.01** Added filter program support. Updated the manual; no program changes.
- **Ver 1.02** Added the `-nv` and `-new` options. If the XLS file does not exist, a new workbook is created.
- **Ver 1.03** Fixed a bug that caused failures when the directory containing CSV files had spaces and a filter program was used.
- **Ver 1.04** Added the `-proc`, `-xml`, and `-paste` options.
