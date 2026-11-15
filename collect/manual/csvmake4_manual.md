# Extended CSV-to-Excel Conversion Program

## 1. About the Program

指定したディレクトリ内のすべてのCSV形式のファイルの内容をExcelファイルに追加します。

また、File nameがシート名になるため、すでにシートが存在する場合は内容をコピーして、該当するシートに内容だけを貼り付けます。

（Formatting, shapes, and other non-data elements are preserved.）

## 2. Usage

This is a console program.

### Syntax

```text
csvmake4 ExcelFile name CSV fileのあるディレクトリ [-nv] [-new] [-proc] [-xml] [-paste] [フィルタProgram] [拡張子]
```

### Options

- `-proc`  
  `csvmake4` 実行後、Excelのプロセスが残っていないかチェックし、残っていた場合は削除します。

- `-nv`  
  Excelの画面を表示しません。

- `-new`  
  Creates a new Excel workbook.

- `-xml`  
  XMLフォーマットで出力します。Excelファイルの拡張子を `xml` にしてください。

- `-paste`  
  CSV file内の数式文字列を、そのままExcelファイルに貼り付けます。

例えば、次のCSV fileがある場合、

```text
a,"=A1"
```

`-paste` Optionを指定しない場合は、

```text
a,a
```

という結果のみExcelファイルにコピーされます。

`-paste` Optionを指定すると、

```text
a,=A1
```

となります。

### Examples

```text
csvmake4 d:\aaa.xls c:\csv
csvmake4 d:\aaa.xls c:\csv tabcsv txt
csvmake4 d:\aaa.xls c:\csv -nv
csvmake4 d:\aaa.xls c:\csv -nv -new
```

## 3. フィルタProgramについて

フィルタProgramは、CSV fileへの変換前に実行されるCSV file変換Programです。

変換されたCSV fileをExcelファイルに追加します。

フィルタProgram（またはバッチファイル）を自分で作成する場合は、Use the following arguments.

1. **第1引数**：変換前ファイル
2. **第2引数**：Converted toCSV file

## 4. 賢い使用方法

`d:\aaa.xls` に出力したい場合は、以下のバッチファイルを作成します。

### バッチファイルの中身

```bat
csvmake d:\aaa.xls %1
```

このファイルを作成したら、このバッチファイルに対して、複数のCSV fileがあるディレクトリを選択してドラッグ＆ドロップします。

すると、Programが起動して、`d:\aaa.xls` にシートを追加または更新します。

## 5. Version History

- **Ver 1.00**　初公開！
- **Ver 1.01**　フィルタProgramの機能を追加。  
  マニュアルを修正しました。Programの変更はありません。
- **Ver 1.02**　`-nv`、`-new` Optionを追加。xlsファイルがない場合は新規にファイルを作成します。
- **Ver 1.03**　フィルタProgramを使用した際、CSV fileのあるディレクトリに空白があると正しく動作しなかった不具合を修正。
- **Ver 1.04**　`-proc`、`-xml`、`-paste` Optionを追加。
