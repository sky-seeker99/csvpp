# CSV-to-Binary Conversion Program

## 1. About the Program

This program CSV fileに記述された内容に従ってバイナリファイルを作成します。

It can also apply patches to binary files.

## 2. Usage

This is a console program.

### Syntax

```text
csvbin CSV file バイナリファイル [-buff buff_size] [-tag tag_name]
```

### Options

- `-buff`: Specifies the buffer size for each read/write operation (KB). Usually not required, but a larger value may help with large files.The default is 10 KB.
- `-tag`：デフォルトでは `#chg` を使用します。`tag_name` を指定すると、`#chg` の代わりに指定したキーを使用します。

※ 数値には16進数を使用できます。先頭に `0x` を付けます。  
例：`0x1000`、`0xa0df`

### Examples

```text
csvbin c:\csv\pict.csv c:\csv\pict.jpg
```

## 3. CSV File Format

### Example

```text
#chg,'h00000000,'hFF,'hD8,'hFF,'hE0
#chg,'h00000010,00,64,00,00,FF
#chg,'h00000020,'b1110111,'b1110000
```

`'h` は16進数、`'b` は2進数、何も付けない場合は10進数として扱います。

### `#chg`

`#chg` は、ファイルの指定位置にデータを書き込みます。

#### 形式

```text
#chg,位置,データ1,データ2～,データn
```

### `#chg` の変更

`#chg` を `#key` に変更する場合は、以下のように `-tag` Optionを指定します。

```text
csvbin c:\csv\pict.csv c:\csv\pict.jpg -tag #key
```

## 4. Version History

- **Ver 1.00**　初公開！
- **Ver 1.00**　マニュアルを修正しました。Programの変更はありません。
- **Ver 1.01**　CSV file読込みライブラリの変更に伴うProgramの変更。機能変更はありません。
- **Ver 1.02**　`-buff` を追加。4GByteを超えるファイルに対応。
- **Ver 1.03**　CSV fileのセル内に改行があっても正しく読み込めるようにしました。
- **Ver 1.04**　`-tag` を追加。
