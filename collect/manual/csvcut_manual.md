# CSV Field Extraction Program

## 1. About the Program

Extracts specified fields from a CSV file and generates a new CSV file.

## 2. Usage

This is a console program.

The syntax is as follows.

```text
csvcut Input CSV file Output CSV file Columns to extract
```

### Example

```text
csvcut c:\csv\int.csv c:\csv\out.csv 1,5-9,11
```

To use standard input and output, run the command as follows.

```text
type c:\csv\int.csv | csvcut - - 1,5-9,11 > c:\csv\out.csv
```

### 項目の指定方法

- Field numbering starts at **1**.
- Input CSV file名に `-` を指定すると、Standard inputを使用します。
- Output CSV file名に `-` を指定すると、Standard outputを使用します。
- Separate field numbers with commas (`,`).
- Use a hyphen (`-`) to specify a range of fields.

例えば、

```text
1,5-9,11
```

と指定すると、**1、5、6、7、8、9、11** の項目を抜き出します。

## 3. Version History

- Ver 1.00　初公開
- Ver 1.01　Standard input・Standard outputの機能を追加。項目を1から数える方式に変更
- Ver 1.02　ダブルクォーテーションに対応
- Ver 1.03　第2水準の漢字に対応
- Ver 1.04　半角スペース削除のバグを修正
- Ver 1.05　変換エンジンを変更し、項目のデータがどれだけ長くても処理できるように変更
