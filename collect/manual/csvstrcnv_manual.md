# CSV Text Format Conversion Program

## 1. About the Program

This program was designed as a filter for CSVMAKE2.

It can also be run as a standalone program.

Converts CSV data so Excel treats numeric values as text when opening the file.

## 2. Usage

This is a console program.

### Syntax

```text
csvstrcnv [+all] [+num] [+numex] [+dbl] [+single] CSVInput file CSVOutput file [-buff buffer_size]
```

### Options

- `-buff`: Specifies the buffer size for each read/write operation (KB). Usually not required, but a larger value may help with large files.The default is 10 KB.
- `+all`：すべてのデータを文字属性に変換します。
- `+num`：数値のみを文字属性に変換します。
- `+numex`：数値、`/`、`:` のみを文字属性に変換します。
- `+dbl`：ダブルクォーテーションで囲まれたデータのみを文字属性に変換します。
- `+single`：シングルクォーテーションで囲まれたデータのみを文字属性に変換します。

### Examples

```text
csvstrcnv +all c:\csv\bbb.csv c:\csv\ccc.csv
```

### CSVMAKE2でフィルタProgramとして使用する場合

```text
csvmake2 d:\aaa.xls -x "csvstrcnv +all" c:\csv\bbb.csv c:\csv\ccc.csv
```

## 3. Version History

- **Ver 1.00**　初公開！
- **Ver 1.01**　高速化しました。
- **Ver 1.02**　Optionを追加。
- **Ver 1.02a**　バグフィックス。
- **Ver 1.03**　4Gバイトを超えるファイルも扱えるようにしました。`-buff` Optionを追加。
