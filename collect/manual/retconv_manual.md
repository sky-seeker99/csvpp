# CSV Line Break Conversion for Excel

（`0x0D 0x0A` → `0x0A`）

## 1. About the Program

This program was designed as a filter for CSVMAKE2.

It can also be run as a standalone program.

Converts line breaks in CSV files to a format that is easier to use in Excel.

通常、データ内に改行があるCSV fileをExcelで開くと、セル内に「・」が表示されることがあります。

これは、Excelのセル内Line endingが `0x0A (LF)` であるためです。

例えば、メモ帳で次のようなCSV fileを作成したとします。

```text
a,b,"c
d"
```

Line ending（CR: `0x0D`、LF: `0x0A`）を表示すると、次のようになります。

```text
a,b,"c[CRLF]
d"
```

これをExcelで読み込むと、`c[CRLF]d` の部分が

```text
c・d
```

のように表示されます。

「・」が `0x0D` を表しています。

This program この「・」の部分を削除します。

## 2. Usage

This is a console program.

### Syntax

```text
retconv 変換前CSV file Converted toCSV file [-buff buffer_size]
```

### Options

- `-buff`: Specifies the buffer size for each read/write operation (KB). Usually not required, but a larger value may help with large files.The default is 10 KB.

### Examples

```text
retconv c:\csv\bbb.csv c:\csv\ccc.csv
```

### CSVMAKE2でフィルタProgramとして使用する場合

```text
csvmake2 d:\aaa.xls -x retconv c:\csv\bbb.csv c:\csv\ccc.csv
```

## 3. Version History

- **Ver 1.00**　初公開！
- **Ver 1.01**　Input fileとOutput fileが同名の場合、エラーを表示するようにしました。
- **Ver 1.01**　マニュアルを修正しました。Programの変更はありません。
- **Ver 1.02**　パラメータ数が2つ以上の場合でも、エラーにせず実行するようにしました。
- **Ver 1.03**　第2水準の漢字に対応。
- **Ver 1.05**　4Gバイトを超えるファイルも扱えるようにしました。`-buff` Optionを追加。
