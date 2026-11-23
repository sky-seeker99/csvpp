# Extended Excel-to-CSV Conversion Program

## 1. About the Program

This utility exports every worksheet from all Excel workbooks in a specified directory as CSV files.

It is useful when you need to convert a large number of Excel files to CSV.

## 2. Usage

This is a console program.

### Syntax

```text
csvmake3 input_directory output_directory [filter_program] [extension] [-tmp] [-proc] [-s worksheet_name worksheet_name ...] [-S worksheet_name worksheet_name ...]
```

### Options

- `-s`: Specifies worksheet names to convert. Wildcards can be used.
- `-S`: Specifies worksheet names to exclude from conversion. Wildcards can be used.
- `-tmp`: Writes each CSV file to a temporary file first, then copies it to the destination CSV file.
- `-proc`: After `csvmake3` runs, checks for any remaining Excel processes and terminates them.

### Examples

```text
csvmake3 c:\xls_dir c:\csv
csvmake3 c:\xls_dir c:\csv csvtab txt
csvmake3 c:\xls_dir c:\csv -s aaa bbb sheet* -S sheet_x*
csvmake3 c:\xls_dir c:\csv csvtab txt -s aaa bbb sheet* -S sheet_x*
```

## 3. Filter Programs

A filter program converts files after they have been exported to CSV.

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
csvmake3 %1 c:\csv
```

After creating this batch file, drag and drop the directory containing the Excel files onto it.

The program starts and creates the CSV files.

## 5. Version History

- **Ver 1.00** Initial release.
- **Ver 1.01** Changed processing to handle one file at a time, resolving resource shortages and enabling conversion of large numbers of Excel files.
- **Ver 1.02** Added support for relative paths when specifying directories.
- **Ver 1.03** Added filter program support. Updated the manual; no program changes.
- **Ver 1.04** Added parameters for filter programs.
- **Ver 1.05** Added an error message when the output destination cannot be written to.
- **Ver 1.06** Fixed a bug that caused failures when the output directory contained spaces and a filter program was used.
- **Ver 1.07** Added the `-proc`, `-tmp`, `-s`, and `-S` options.
