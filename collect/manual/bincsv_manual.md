# Binary-to-CSV Conversion Program

## 1. About the Program

This console program dumps binary files in CSV format.

Supports hexadecimal, decimal, and binary output.

## 2. Usage

This is a console program.

### Syntax

```text
bincsv [-b|-d] バイナリファイル CSV file [-start start_address] [-size size] [-buff buff_size] [-width width_size]
```

### Options

- If no option is specified, values are displayed in hexadecimal.
- `-d`: Displays values in decimal.
- `-b`: Displays values in binary.
- `-start`: Specifies the address at which reading starts.If omitted, reading starts at the beginning of the file.
- `-size`：読み出すサイズを指定します。If omitted, the entire file is read.
- `-width`：1行あたりのバイト数を指定します。
- `-buff`: Specifies the buffer size for each read/write operation (KB). Usually not required, but a larger value may help with large files.The default is 10 KB.

※ 数値には16進数を使用できます。先頭に `0x` を付けます。  
例：`0x1000`、`0xa0df`

### Examples

```text
bincsv c:\csv\pict.jpg c:\csv\pict.csv
bincsv -d c:\csv\pict.jpg c:\csv\pict.csv
bincsv -b c:\csv\pict.jpg c:\csv\pict.csv
```

## 3. CSV File Format

### 出力例

```text
#size,32061
#head,ADDRESS,'h00,'h01,'h02,'h03,'h04,'h05,'h06,'h07,'h08,'h09,'h0A,'h0B,'h0C,'h0D,'h0E,'h0F
#chg,'h00000000,'hFF,'hD8,'hFF,'hE0,'h00,'h10,'h4A,'h46,'h49,'h46,'h00,'h01,'h02,'h01,'h00,'h64
#chg,'h00000010,'h00,'h64,'h00,'h00,'hFF,'hED,'h00,'hB8,'h50,'h68,'h6F,'h74,'h6F,'h73,'h68,'h6F
～
#chg,'h00007D30,'h89,'h50,'h11,'hDC,'h7F,'h92,'h09,'hC1,'h41,'h6C,'hBF,'hFF,'hD9
```

## 4. Version History

- **Ver 1.00**　初公開！
- **Ver 1.00**　マニュアルを修正しました。Programの変更はありません。
- **Ver 1.01**　10進数、2進数にも対応しました。
- **Ver 1.02**　`-start`、`-size`、`-buff` を追加。4GByteを超えるファイルに対応しました。
- **Ver 1.03**　`-width` Optionを追加。
