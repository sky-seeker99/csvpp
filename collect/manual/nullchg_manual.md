# NULL削除・置換プログラム

## 1. ソフトの紹介

テキストファイル（特にCSVファイル）に混ざっているNULLを削除したり、半角スペースや指定したユニークコードに変換したりするプログラムです。

## 2. 使用方法

本プログラムはコンソールプログラムです。

### 実行形式

```text
nullchg 入力ファイル 出力ファイル [-chgsp] [-chg ユニークコード] [-buff buffer_size]
```

### オプション

- `-buff`：1回の読み書きに使用するバッファサイズを指定します（単位：KByte）。通常は指定する必要はありませんが、ファイルが大きい場合などには、大きな値を指定すると有効です。指定しない場合は10KByteとなります。
- `-chgsp`：NULLを半角スペースに変換します。
- `-chg`：NULLを指定したユニークコードに変換します。

※ `-chgsp`、`-chg` のどちらも指定しない場合は、NULLを削除します。

### 使用例

```text
nullchg.exe Sheet1.csv Sheet1.csv.del
nullchg.exe Sheet1.csv Sheet1.csv.sp -chgsp
nullchg.exe Sheet1.csv Sheet1.csv.uniq -chg [[NULL]]
```

## 3. 履歴

- **Ver 1.00**　初公開！
