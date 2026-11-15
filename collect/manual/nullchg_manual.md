# NULL Removal and Replacement Program

## 1. About the Program

テキストファイル（特にCSV file）に混ざっているNULLを削除したり、半角スペースや指定したユニークコードに変換したりするProgramです。

## 2. Usage

This is a console program.

### Syntax

```text
nullchg Input file Output file [-chgsp] [-chg replacement_string] [-buff buffer_size]
```

### Options

- `-buff`: Specifies the buffer size for each read/write operation (KB). Usually not required, but a larger value may help with large files.The default is 10 KB.
- `-chgsp`：NULLを半角スペースに変換します。
- `-chg`：NULLを指定したユニークコードに変換します。

※ `-chgsp`、`-chg` のどちらも指定しない場合は、NULLを削除します。

### Examples

```text
nullchg.exe Sheet1.csv Sheet1.csv.del
nullchg.exe Sheet1.csv Sheet1.csv.sp -chgsp
nullchg.exe Sheet1.csv Sheet1.csv.uniq -chg [[NULL]]
```

## 3. Version History

- **Ver 1.00**　初公開！
