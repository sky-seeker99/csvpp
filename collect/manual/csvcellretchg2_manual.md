# CSV Cell Line Break Conversion Program 2

## 1. About the Program

This program removes line breaks from data in CSV files exported by Excel or replaces them with a specified string.

## 2. Usage

This is a console program.

### Syntax

```text
csvcellretchg2 Input file nameOutput file name [replacement_string] [-dbl_no_cut] [-buff buffer_size]
```

Specify the full path to the file.

### Options

- `-buff`: Specifies the buffer size for each read/write operation (KB).
  通常は指定する必要はありませんが、ファイルが大きい場合などには、大きな値を指定すると有効です。
  The default is 10 KB.
- `-dbl_no_cut`：不要なダブルクォーテーションを削除しないようにします。

### Examples

```text
csvcellretchg2 c:\csv\in.csv c:\csv\out.csv
```

CSV fileの改行を削除します。

```text
csvcellretchg2 c:\csv\in.csv c:\csv\out.csv @@@@@
```

CSV fileの改行を `@@@@@` に置き換えます。

### Standard Input and Output

Specify `-` as the input file name to read from standard input.
Specify `-` as the output file name to write to standard output.

Standard outputの場合のLine endingは、必ず `0x0d,0x0a` になりますので注意してください。

### Standard Input and OutputのExample

```text
type c:\csv\in.csv | csvcellretchg2 - - > c:\csv\out.csv
```

## 3. Version History

- **Ver 1.01**　初公開！
- **Ver 1.02**　`-dbl_no_cut` Optionを追加。
