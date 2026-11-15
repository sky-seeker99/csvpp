# Extended Excel-to-CSV Conversion Program

## 1. About the Program

This utility exports every worksheet from **all Excel files** in a specified directory as CSV files.

Useful when converting a large number of files to CSV.

## 2. Usage

This is a console program.

### Syntax

```text
csvmake3 Excelファイルのあるディレクトリ 出力先ディレクトリ [フィルタProgram] [拡張子] [-tmp] [-proc] [-s シート名 シート名 …] [-S シート名 シート名 …]
```

### Options

- `-s`  
  Specifies worksheet names to convert. Wildcards can be used.

- `-S`  
  Specifies worksheet names to exclude. Wildcards can be used.

- `-tmp`  
  CSV fileをいったんテンポラリファイルに出力してから、元のCSV fileにコピーします。

- `-proc`  
  `csvmake3` 実行後、Excelのプロセスが残っていないかチェックし、残っていた場合は削除します。

### Examples

```text
csvmake3 c:\xls_dir c:\csv
csvmake3 c:\xls_dir c:\csv csvtab txt
csvmake3 c:\xls_dir c:\csv -s aaa bbb sheet* -S sheet_x*
csvmake3 c:\xls_dir c:\csv csvtab txt -s aaa bbb sheet* -S sheet_x*
```

## 3. フィルタProgramについて

A filter program converts files after they have been converted to CSV.

フィルタProgram（またはバッチファイル）を自分で作成する場合は、Use the following arguments.

1. **第1引数**：変換前CSV file
2. **第2引数**：Converted toファイル
3. **第3引数**：シーケンス番号（三桁、前ゼロ付き）
4. **第4引数**：出力先ディレクトリ名
5. **第5引数**：シート名

## 4. 賢い使用方法

`c:\csv` ディレクトリに出力したい場合は、以下のバッチファイルを作成します。

### バッチファイルの中身

```bat
csvmake3 %1 c:\csv
```

このファイルを作成したら、このバッチファイルに対して、Excelファイルが入っているディレクトリをドラッグ＆ドロップします。

すると、Programが起動してCreates a CSV file.

## 5. Version History

- **Ver 1.00**　初公開！
- **Ver 1.01**　1ファイルごとに処理し、リソース不足を解消。  
  大量のExcelファイルの変換が可能になりました。
- **Ver 1.02**　ディレクトリ指定が相対パスに対応しました。
- **Ver 1.03**　フィルタProgramの機能を追加。  
  マニュアルを修正しました。Programの変更はありません。
- **Ver 1.04**　フィルタProgramのパラメータを追加。
- **Ver 1.05**　出力先に書き込めない場合にエラーMessageを出力。
- **Ver 1.06**　フィルタProgramを使用した際、出力先ディレクトリに空白があると正しく動作しなかった不具合を修正。
- **Ver 1.07**　`-proc`、`-tmp`、`-s`、`-S` Optionを追加。
