# Shift-JIS/EUC-JP Conversion Program 2

## 1. About the Program

This console program converts between Shift-JIS and EUC-JP encodings.

Wildcards can be used in file names.

## 2. Usage

This is a console program.

### Syntax

```text
eucsjis2 sjis_euc|euc_sjis Input file nameOutput file name
```

Specify the full path to the file.

### 変換方法

- `sjis_euc`：SJISからEUCに変換します。このとき、Line endingは `0x0A` に変換します。
- `euc_sjis`：EUCからSJISに変換します。このとき、Line endingは `0x0D, 0x0A` に変換します。

### Line endingを指定する場合

- `sjis_euc_win` / `euc_sjis_win`：Line endingを `0x0D, 0x0A` に変換します。
- `sjis_euc_unix` / `euc_sjis_unix`：Line endingを `0x0A` に変換します。

### Standard Input and Output

Specify `-` as the input file name to read from standard input.

Specify `-` as the output file name to write to standard output.

Standard outputを使用する場合、Line endingは必ず `0x0D, 0x0A` になりますので注意してください。

### Examples

```text
eucsjis2 sjis_euc c:\csv\in.txt c:\csv\out.txt
type c:\csv\in.txt | eucsjis2 euc_sjis - - > c:\csv\out.txt
```

## 3. 外字の変換

SJISコードの漢字で外字を使用する場合は、`eucsjis.exe` のあるディレクトリに `eucsjis.csv` ファイルを置きます。

`eucsjis.csv` には、変換規則を記述します。

添付の `eucsjis.csv` ファイルには、作者が調査したSJISコードからEUCコードへの変換規則が記述されています。

### フォーマット

```text
#sjis_euc,1文字目のコード,2文字目のコード上限,2文字目のコード下限,1文字目のコード差分,2文字目のコード差分
#euc_sjis,1文字目のコード,2文字目のコード上限,2文字目のコード下限,1文字目のコード差分,2文字目のコード差分
```

- `#sjis_euc`：SJISコードからEUCコードへの変換規則を指定します。
- `#euc_sjis`：EUCコードからSJISコードへの変換規則を指定します。

### 設定例

```text
#sjis_euc,250,73,64,2,177
#sjis_euc,250,83,74,-77,107
```

## 4. Version History

- **Ver 1.00**　初公開！
- **Ver 1.02**　外字の変換規則をファイルで指定できるようにしました。
- **Ver 1.02a**　不要なリターンコードを付加していたバグを修正。
- **Ver 1.03**　高速化しました。
