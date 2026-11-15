# Excel-to-CSV Conversion Program

## 1. About the Program

This utility exports every worksheet in an Excel workbook as a CSV file.

Useful when you want to create CSV files without having to open Excel.

## 2. Usage

This is a console program.

The syntax is as follows.

```text
csvmake ExcelFile name 出力先ディレクトリ [フィルタProgram] [拡張子] [-tmp] [-proc] [-s シート名 シート名・・・] [-S シート名 シート名・・・]
```

### Options

- **`-s`**  
  Specifies worksheet names to convert. Wildcards can be used.
- **`-S`**  
  Specifies worksheet names to exclude. Wildcards can be used.
- **`-tmp`**  
  Writes the CSV file to a temporary file first, then copies it to the destination CSV file.
- **`-proc`**  
  After `csvmake` runs, checks for any remaining Excel processes and terminates them.

### 実行例

```text
csvmake aaa.xls c:\csv
csvmake aaa.xls c:\csv csvtab txt
csvmake aaa.xls c:\csv -s aaa bbb sheet* -S sheet_x*
csvmake aaa.xls c:\csv csvtab txt -s aaa bbb sheet* -S sheet_x*
```

## 3. フィルタProgramについて

A filter program converts files after they have been converted to CSV.

フィルタProgram（またはバッチファイル）を自分で作成する場合は、Use the following arguments.

1. **1番目の引数**：変換前CSV file
2. **2番目の引数**：Converted toファイル
3. **3番目の引数**：シーケンス番号（3桁、前ゼロ付き）
4. **4番目の引数**：出力先ディレクトリ名
5. **5番目の引数**：シート名

## 4. 賢い使用方法

`c:\csv` ディレクトリに出力したい場合は、以下のバッチファイルを作成します。

### バッチファイルの内容

```bat
csvmake %1 c:\csv
```

このバッチファイルを作成したら、バッチファイルに対してExcelファイル（xlsファイル）をドラッグ＆ドロップします。

するとProgramが起動し、Creates a CSV file.

## 5. Version History

- Ver 1.00　初公開
- Ver 1.01　フィルタProgramの機能を追加
- ――――――　マニュアルを修正（Programの変更はありません）
- Ver 1.02　変換したいシート名、変換したくないシート名を指定できるように変更
- Ver 1.03　フィルタProgramのパラメータを追加
- Ver 1.04　Excelファイルを相対パスで指定するとエラーになるバグを修正
- Ver 1.05　出力先に書き込めない場合にエラーMessageを出力するように変更
- Ver 1.06　出力先を相対パスにした場合の不具合を修正
- Ver 1.07　フィルタProgramを使用した場合、出力先ディレクトリに空白があると正しく動作しなかったバグを修正
- Ver 1.08　`-proc`、`-tmp` Optionを追加
