# CSV-to-Excel Conversion Program

## 1. About the Program

CSV形式のファイルの内容をExcelファイルに追加するProgramです。

The CSV file name is used as the worksheet name.If a worksheet with that name already exists, its contents are copied and only the data is pasted into the matching sheet.

Formatting, shapes, and other non-data elements are preserved.

> **注意**
> - Excelファイルが存在しない場合はエラーになります。新規に作成する場合は、あらかじめExcelファイルを新規作成してください。
> - シート名が半角で32文字以上の場合は、31文字として処理します。

## 2. Usage

This is a console program.

The syntax is as follows.

```text
csvmake2 ExcelFile name [-x フィルタProgram] [-nv] [-new] [-paste] [-xml] [-proc] CSV file name1 CSV file name2 … CSV file namen
```

### Options

- **`-proc`**  
  `csvmake2` 実行後にExcelのプロセスが残っていないかチェックし、残っていた場合は削除します。
- **`-nv`**  
  Hides the Excel window.
- **`-new`**  
  Creates a new Excel workbook.
- **`-xml`**  
  XML形式で出力します。ExcelFile nameの拡張子を `xml` にしてください。
- **`-paste`**  
  CSV file内の数式を、そのままExcelファイルに貼り付けます。

例えば、以下の内容のファイルがあるとします。

```text
a,"=A1"
```

Optionを指定しない場合は、以下の結果だけがExcelファイルにコピーされます。

```text
a,a
```

`-paste` Optionを指定すると、The result is as follows.

```text
a,=A1
```

### 実行例

```text
csvmake2 d:aa.xls c:\csvbb.csv c:\csv\ccc.csv
csvmake2 d:aa.xls -nv c:\csvbb.csv c:\csv\ccc.csv
csvmake2 d:aa.xls -x retconv c:\csvbb.csv c:\csv\ccc.csv
```

## 3. フィルタProgramについて

A filter program converts the CSV file before it is imported into the Excel workbook.

Converted toのCSV fileをExcelファイルに追加します。

フィルタProgram（またはバッチファイル）を自分で作成する場合は、Use the following arguments.

1. **1番目の引数**：変換前CSV file
2. **2番目の引数**：Converted toCSV file

## 4. 賢い使用方法

`d:aa.xls` に出力したい場合は、以下のバッチファイルを作成します。

### バッチファイルの内容

```bat
csvmake d:aa.xls %1 %2 %3 %4 %5 %6 %7 %8 %9
```

このバッチファイルを作成したら、バッチファイルに対して複数のCSV fileを選択してドラッグ＆ドロップします。

すると、Programが起動し、`d:aa.xls` にシートを追加または更新します。

## 5. 注意点

Excel 2003の環境では、マクロのセキュリティレベルを以下に設定する必要があります。

**ツール → Option → マクロセキュリティ**

- セキュリティレベルを「高」から「中」に変更
- 信頼できる発行元を削除

## 6. Version History

- Ver 1.00　初公開
- Ver 1.01　コピー後、毎回保存するように変更
- Ver 1.02　フィルタProgramの機能を追加
- ――――――　マニュアルを修正（Programの変更はありません）
- Ver 1.03　Excelの画面を表示しないOptionを追加。相対パスで実行可能に変更。バグを修正
- Ver 1.04　`-nv` Optionのバグを修正
- Ver 1.05　シート名が半角で32文字以上の場合は31文字として処理
- Ver 1.06　Excelファイルが使用中の場合もCSV fileの表示（エラー表示）を行うように変更
- Ver 1.07　指定したExcelファイルがない場合、新規にファイルを作成するように変更
- Ver 1.08　`-new` Optionを追加
- Ver 1.09　フィルタProgramを使用した場合、CSV fileのパスに空白があると正しく動作しなかったバグを修正
- Ver 1.10　`-paste` Optionを追加
- Ver 1.11　`-xml` Optionを追加
- Ver 1.12　`-proc` Optionを追加
