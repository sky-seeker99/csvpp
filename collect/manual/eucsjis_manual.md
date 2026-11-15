# Shift-JIS/EUC-JP Conversion Program

## 1. About the Program

This console program converts between Shift-JIS and EUC-JP encodings.

Wildcards can be used in file names.

## 2. Usage

This is a console program.

### Syntax

```text
eucsjis sjis_euc|euc_sjis Files to convert
```

Specify the full path to the file to convert.

### 変換方法

- `sjis_euc`：SJISからEUCに変換します。このとき、Line endingは `0x0A` に変換します。
- `euc_sjis`：EUCからSJISに変換します。このとき、Line endingは `0x0D, 0x0A` に変換します。

### Line endingを指定する場合

- `sjis_euc_win` / `euc_sjis_win`：Line endingを `0x0D, 0x0A` に変換します。
- `sjis_euc_unix` / `euc_sjis_unix`：Line endingを `0x0A` に変換します。

### Examples

```text
eucsjis sjis_euc c:\csv\*.txt
eucsjis euc_sjis c:\csv\*.txt
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
- **Readme**　Readmeの付け忘れ。
- **Ver 1.01**　バグフィックス、Line Ending Conversion。
- **Ver 1.02**　外字の変換規則をファイルで指定できるようにしました。
- **Ver 1.02a**　不要なリターンコードを付加していたバグを修正。
- **Ver 1.03**　高速化しました。
