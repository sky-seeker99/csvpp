# Line Ending Conversion Program

## 1. About the Program

This console program converts between Windows, Mac, and Unix line endings.

Wildcards can be used in file names.

## 2. Usage

This is a console program.

### Syntax

```text
retchg -m|-w|-u Files to convert [-buff buffer_size]
```

Specify the full path to the file to convert.

### Options

- `-m`：Mac用Line endingに変換します。
- `-w`：Windows用Line endingに変換します。
- `-u`：Unix用Line endingに変換します。
- `-buff`: Specifies the buffer size for each read/write operation (KB).

`-buff` は通常は指定する必要はありませんが、ファイルが大きい場合などには、大きな値を指定すると有効です。

指定しない場合は、10KByteとなります。

### Examples

```text
retchg -w c:\csv\*.txt
```

```text
retchg -m c:\csv\*.html
```

```text
retchg -u c:\csv\*.csv
```

```text
retchg -u c:\csv\*.csv -buff 100
```

## 3. Version History

- **Ver 1.00**　初公開！
- **Ver 1.01**　第2水準の漢字に対応。
- **Ver 1.02**　4Gバイトを超えるファイルも扱えるようにしました。
