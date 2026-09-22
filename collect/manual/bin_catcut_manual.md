# バイナリファイル連結・分割プログラム

## 1. ソフトの紹介

本プログラムは、バイナリファイルの連結や一部切り出しなどを行うコンソールプログラムです。

## 2. 使用方法

本プログラムはコンソールプログラムです。

### 実行形式

```text
bin_catcut in_file out_file [-new] [-r_offset offset] [-w_offset offset] [-size size] [-buff buffer_size]
```

オプションを何も指定しない場合は、`out_file` の後に `in_file` の内容が付加されます。

### オプション

- `-new`：新規作成します。
- `-r_offset`：入力ファイルのオフセットバイト数を指定します。指定しない場合は先頭から読み出します。
- `-w_offset`：出力ファイルのオフセットバイト数を指定します。指定しない場合はファイルの最後から付加されます。
- `-size`：読み書きするサイズを指定します。指定しない場合は、入力ファイルのサイズから入力ファイルのオフセットバイト数を引いた値になります。
- `-buff`：1回の読み書きに使用するバッファサイズを指定します（単位：KByte）。
  通常は指定する必要はありませんが、ファイルが大きい場合などには、大きな値を指定すると有効です。
  指定しない場合は10KByteとなります。

※ 数字には16進数を使用できます。先頭に `0x` を付けます。  
例：`0x1000`、`0xa0df`

### 使用例

#### ファイル連結

```text
bin_catcut in1.bin out.bin -new
bin_catcut in2.bin out.bin
bin_catcut in3.bin out.bin
```

#### 100バイト単位で分割

```text
bin_catcut in.bin out1.bin -new -size 100
bin_catcut in.bin out2.bin -new -size 100 -r_offset 100
bin_catcut in.bin out3.bin -new -size 100 -r_offset 200
```

## 3. 履歴

- **Ver 1.00**　初公開！
- **Ver 1.01**　4Gバイトを超えるファイルも扱えるようにしました。
- **Ver 1.01a**　バグフィックス。
- **Ver 1.02**　バッファサイズのバグフィックス。
