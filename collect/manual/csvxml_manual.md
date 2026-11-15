# CSV-to-XML Conversion Program

## 1. About the Program

This program converts CSV files to XML files.

Supports data larger than 2 GB.

## 2. Usage

This is a console program.

### Syntax

```text
csvxml csv_file xml_file [-tag tag_config_file] [-header header_file] [-buff size] [-e]
```

### Options

- `-e`：エスケープコードへの変換を行いません。
- `-tag`：タグ設定Specifies a file.
- `-header`：ヘッダSpecifies a file.
- `-buff`: Specifies the buffer size for each read/write operation (KB). Usually not required, but a larger value may help with large files.The default is 10 KB.

### Examples

```text
csvxml data.csv data.xml
csvxml data.csv data.xml -tag tag.csv -header header.txt
```

## 3. タグ設定ファイル

タグ設定ファイルでは、全体を定義するタグ名、レコード単位のタグ名、項目のタグ名を指定します。

### 設定例

```text
#total_tag,DOC
#record_tag,REC
#tag,hinmei
#tag,tanka
#tag,suuryo
```

タグを指定しない場合は、以下のタグ名になります。

- 全体を定義するタグ名：`DOC`
- レコード単位のタグ名：`REC`
- 項目のタグ名：`TAG` + 番号

### (1) 全体を定義するタグ名の指定

#### 形式

```text
#total_tag,root tag name
```

#### Examples

```text
#total_tag,DOC
```

### (2) レコード単位のタグ名の指定

#### 形式

```text
#record_tag,record tag name
```

#### Examples

```text
#record_tag,REC
```

### (3) 項目のタグ名の指定

#### 形式

```text
#tag,field tag name
```

#### Examples

```text
#tag,suuryo
```

### (4) Escape conversion

XMLでは、以下の文字がエスケープコードに変換されます。

| 文字 | エスケープコード |
|---|---|
| `&`（アンパサンド） | `&amp;` |
| `>`（大なり記号） | `&gt;` |
| `<`（小なり記号） | `&lt;` |
| `"`（二重引用符） | `&quot;` |
| `'`（単一引用符） | `&apos;` |

The `-e` option disables this escaping.

## 4. ヘッダファイル

The header file specifies the contents of the first and second lines of the XML file.

### Example

```xml
<?xml version="1.0" encoding="Shift_JIS"?>
<?xml:stylesheet type="text/xsl" href="aaa.xsl"?>
```

For details, refer to the XML specification.

## 5. Version History

- **Ver 1.00**　リリース
- **Ver 1.01**　ヘッダファイル、タグ設定ファイルをOptionにしました。
- **Ver 1.02**　エスケープコード変換機能を追加。`-e` Optionを追加。
