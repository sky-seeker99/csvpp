# Binary-to-CSV Conversion Program

## 1. About the Program

This console program dumps binary files in CSV format.

It supports hexadecimal, decimal, and binary output.

## 2. Usage

This is a console program.

### Syntax

```text
bincsv [-b|-d] binary_file csv_file [-start start_address] [-size size] [-buff buff_size] [-width width_size]
```

### Options

- If no option is specified, values are displayed in hexadecimal.
- `-d`: Displays values in decimal.
- `-b`: Displays values in binary.
- `-start`: Specifies the address at which reading starts. If omitted, reading starts at the beginning of the file.
- `-size`: Specifies the number of bytes to read. If omitted, the entire file is read.
- `-width`: Specifies the number of bytes displayed per line.
- `-buff`: Specifies the buffer size used for each read/write operation (KB). This option is usually unnecessary, but a larger value may help with large files. The default is 10 KB.

Note: Numbers can be specified in hexadecimal by prefixing them with `0x`.
Examples: `0x1000`, `0xa0df`

### Examples

```text
bincsv c:\csv\pict.jpg c:\csv\pict.csv
bincsv -d c:\csv\pict.jpg c:\csv\pict.csv
bincsv -b c:\csv\pict.jpg c:\csv\pict.csv
```

## 3. CSV File Format

### Output Example

```text
#size,32061
#head,ADDRESS,'h00,'h01,'h02,'h03,'h04,'h05,'h06,'h07,'h08,'h09,'h0A,'h0B,'h0C,'h0D,'h0E,'h0F
#chg,'h00000000,'hFF,'hD8,'hFF,'hE0,'h00,'h10,'h4A,'h46,'h49,'h46,'h00,'h01,'h02,'h01,'h00,'h64
#chg,'h00000010,'h00,'h64,'h00,'h00,'hFF,'hED,'h00,'hB8,'h50,'h68,'h6F,'h74,'h6F,'h73,'h68,'h6F
...
#chg,'h00007D30,'h89,'h50,'h11,'hDC,'h7F,'h92,'h09,'hC1,'h41,'h6C,'hBF,'hFF,'hD9
```

## 4. Version History

- **Ver 1.00** Initial release.
- **Ver 1.00** Updated the manual; no program changes.
- **Ver 1.01** Added support for decimal and binary output.
- **Ver 1.02** Added the `-start`, `-size`, and `-buff` options and support for files larger than 4 GB.
- **Ver 1.03** Added the `-width` option.
