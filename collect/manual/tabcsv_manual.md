# TAB-to-CSV Conversion Program

## 1. About the Program

This program was designed as a filter for CSVMAKE2.

It can also be run as a standalone program.

Converts TAB files to CSV files.

## 2. Usage

This is a console program.

### Syntax

```text
tabcsv TAB file CSV file [-buff buffer_size] [-dbl_no_cut]
```

### Options

- `-buff`: Specifies the buffer size for each read/write operation (KB). Usually not required, but a larger value may help with large files.The default is 10 KB.
- `-dbl_no_cut`：不要なダブルクォーテーションを削除しないようにします。

### Examples

```text
tabcsv c:\csv\bbb.txt c:\csv\ccc.csv
```

### CSVMAKE2でフィルタProgramとして使用する場合

```text
csvmake2 d:\aaa.xls -x tabcsv c:\csv\bbb.txt c:\csv\ccc.txt
```

## 3. Version History

- **Ver 1.00**　初公開！
- **Ver 1.00**　マニュアルを修正しました。Programの変更はありません。
- **Ver 1.01**　パラメータ数が2つ以上の場合でも、エラーにせず実行するようにしました。
- **Ver 1.02**　第2水準の漢字に対応。
- **Ver 1.03**　4Gバイトを超えるファイルも扱えるようにしました。`-buff`、`-dbl_no_cut` Optionを追加。
