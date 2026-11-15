# CSV Line Break Conversion for Excel 2

（`0x0D` → `0x0D 0x0A`）

## 1. About the Program

This program was designed as a filter for CSVMAKE.

It can also be run as a standalone program.

Performs the reverse conversion of `retconv`.

## 2. Usage

This is a console program.

### Syntax

```text
retconv2 変換前CSV file Converted toCSV file [-buff buffer_size]
```

### Options

- `-buff`: Specifies the buffer size for each read/write operation (KB). Usually not required, but a larger value may help with large files.The default is 10 KB.

### Examples

```text
retconv2 c:\csv\bbb.csv c:\csv\ccc.csv
```

### CSVMAKEでフィルタProgramとして使用する場合

```text
csvmake d:\aaa.xls c:\csv retconv2 csv
```

## 3. Version History

- **Ver 1.00**　初公開！
- **Ver 1.00**　マニュアルを修正しました。Programの変更はありません。
- **Ver 1.01**　パラメータ数が2つ以上の場合でも、エラーにせず実行するようにしました。
- **Ver 1.02**　第2水準の漢字に対応。
- **Ver 1.05**　4Gバイトを超えるファイルも扱えるようにしました。`-buff` Optionを追加。
