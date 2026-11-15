# CSV Cell Line Break Conversion Program

## 1. About the Program

This program removes line breaks from data in CSV files exported by Excel or replaces them with a specified string.

## 2. Usage

This is a console program.

### Syntax

```text
csvcellretchg CSV file [replacement_string] [-dbl_no_cut] [-buff buffer_size]
```

### Options

- `-buff`: Specifies the buffer size for each read/write operation (KB).
  通常は指定する必要はありませんが、ファイルが大きい場合などには、大きな値を指定すると有効です。
  The default is 10 KB.
- `-dbl_no_cut`：不要なダブルクォーテーションを削除しないようにします。

### Examples

```text
csvcellretchg c:\csv\*.csv
```

`c:\csv` の拡張子が `.csv` のファイルの改行を削除します。

```text
csvcellretchg c:\csv\*.csv @@@@@
```

`c:\csv` の拡張子が `.csv` のファイルの改行を `@@@@@` に置き換えます。

## 3. Version History

- **Ver 1.00**　初公開！
- **Ver 1.01**　4Gバイトを超えるファイルも扱えるようにしました。`-buff` Optionを追加。
- **Ver 1.02**　`-dbl_no_cut` Optionを追加。
