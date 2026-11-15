# CSV-to-TAB Conversion Program

## 1. About the Program

This program was designed as a filter for CSVMAKE.

It can also be run as a standalone program.

Converts CSV files to TAB-delimited files.

## 2. Usage

This is a console program.

### Syntax

```text
csvtab CSV file TAB file [-buff buffer_size] [-dbl_no_cut]
```

### Options

- `-buff`: Specifies the buffer size for each read/write operation (KB). Usually not required, but a larger value may help with large files.The default is 10 KB.
- `-dbl_no_cut`：不要なダブルクォーテーションを削除しないようにします。

### Examples

```text
csvtab c:\csv\bbb.csv c:\csv\ccc.txt
```

```text
type c:\csv\bbb.csv | csvtab - - > c:\csv\ccc.txt
```

※ Specify `-` as the CSV file name to read from standard input.  
※ Specify `-` as the TAB file name to write to standard output.

### CSVMAKEでフィルタProgramとして使用する場合

```text
csvmake d:\aaa.xls c:\csv csvtab txt
```

## 3. Version History

- **Ver 1.00**　初公開！
- **Ver 1.00**　マニュアルを修正しました。Programの変更はありません。
- **Ver 1.01**　パラメータ数が2つ以上の場合でも、エラーにせず実行するようにしました。
- **Ver 1.02**　第2水準の漢字に対応。
- **Ver 1.03**　半角スペースが文字の両側にあっても削除しないようにしました。
- **Ver 1.04**　最終行に改行が追加されてしまうバグを修正。Standard input、Standard outputの機能を追加。
- **Ver 1.05**　4Gバイトを超えるファイルも扱えるようにしました。`-buff`、`-dbl_no_cut` Optionを追加。
- **Ver 1.06**　ダブルクォーテーション付きデータの処理にバグがあり、修正しました。
