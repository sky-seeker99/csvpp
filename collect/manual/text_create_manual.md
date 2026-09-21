# テキストファイル生成プログラム

## 1. ソフトの紹介

本プログラムは、テキストファイルをさまざまなパターンで生成するプログラムです。

## 2. 使用方法

本プログラムはコンソールプログラムです。

実行形式は以下のとおりです。

```text
text_create ルールファイル [-buff buffer_size]
```

ルールファイル名はフルパスで指定してください。

ルールファイルはCSV形式のファイルです。

`-buff` は、1回の読み書きに使用するバッファサイズ（単位：KByte）を指定します。通常は指定する必要はありませんが、ファイルサイズが大きい場合などには、大きな値を指定すると有効です。指定しない場合は10 KByteです。

### 例

```text
text_create rule.csv
```

## 3. 使用例

以下にCSVファイルの例を示します。

```csv
#file,ptn3.txt
#key,cc

#writeln,aa,aaAAAAAAAAAAAAAAAAAAAAA1
#writeln,aa,
#writeln,aa,aaAAAAAAAAAAAAAAAAAAAAA1
#writeln,aa,aaAAAAAAAAAAAAAAAAAAAAA2
#writeln,aa,aaAAAAAAAAAAAAAAAAAAAAA3
#writeln,aa,aaAAAAAAAAAAAAAAAAAAAAA4
#writeln,aa,aaAAAAAAAAAAAAAAAAAAAAA5
#writeln,aa,aaAAAAAAAAAAAAAAAAAAAAA6

#writeln,bb,bbBBBBBBBBBBBBBBBBBBBBB1
#write,bb,2
#write,bb,3
#write,bb,4
#write,bb,5
#write,bb,6
#writeln,bb,7

#writeln,cc,ccCCCCCCCCCCCCCCCCCCCCC1
#writeln,cc,ccCCCCCCCCCCCCCCCCCCCCC2
#writeln,cc,ccCCCCCCCCCCCCCCCCCCCCC3
#writeln,cc,ccCCCCCCCCCCCCCCCCCCCCC4
#writeln,cc,ccCCCCCCCCCCCCCCCCCCCCC5
#writeln,cc,ccCCCCCCCCCCCCCCCCCCCCC6
#writeln,cc,ccCCCCCCCCCCCCCCCCCCCCC7
#writeln,cc,ccCCCCCCCCCCCCCCCCCCCCC8
#writeln,cc,ccCCCCCCCCCCCCCCCCCCCCC9

#file,ptn1.txt
#key,aa

#file,ptn2.txt
#key,bb
#key,cc

#file,ptn3.txt
#key,dd

#file,ptn3.txt
#key,aa
#key,bb
#file,ptn3.txt
#key,cc
```

### キーとデータの割り振り

`#write` または `#writeln` の次のデータがキーとなり、その後のデータがそのキーに対応するデータになります。

上記の例では、キーは `aa`、`bb`、`cc` となり、それぞれのキーに対するデータは以下のようになります。

#### `[aa]`

```text
aaAAAAAAAAAAAAAAAAAAAAA1

aaAAAAAAAAAAAAAAAAAAAAA1
aaAAAAAAAAAAAAAAAAAAAAA2
aaAAAAAAAAAAAAAAAAAAAAA3
aaAAAAAAAAAAAAAAAAAAAAA4
aaAAAAAAAAAAAAAAAAAAAAA5
aaAAAAAAAAAAAAAAAAAAAAA6
```

#### `[bb]`

```text
bbBBBBBBBBBBBBBBBBBBBBB1
234567
```

#### `[cc]`

```text
ccCCCCCCCCCCCCCCCCCCCCC1
ccCCCCCCCCCCCCCCCCCCCCC2
ccCCCCCCCCCCCCCCCCCCCCC3
ccCCCCCCCCCCCCCCCCCCCCC4
ccCCCCCCCCCCCCCCCCCCCCC5
ccCCCCCCCCCCCCCCCCCCCCC6
ccCCCCCCCCCCCCCCCCCCCCC7
ccCCCCCCCCCCCCCCCCCCCCC8
ccCCCCCCCCCCCCCCCCCCCCC9
```

これらのデータが、それぞれのファイルに割り振られて出力されます。

### ファイルへの出力

`ptn1.txt` は以下のキーを対象とします。

```text
[aa]
```

`ptn2.txt` は以下のキーを対象とします。

```text
[bb]
[cc]
```

`ptn3.txt` は以下のキーを対象とします。

```text
[cc]
```

`[dd]` は存在しないキーのため、出力されません。

その後、以下のキーが対象となります。

```text
[aa]
[bb]
[cc]
```

### 出力結果

#### `ptn1.txt`

```text
aaAAAAAAAAAAAAAAAAAAAAA1

aaAAAAAAAAAAAAAAAAAAAAA1
aaAAAAAAAAAAAAAAAAAAAAA2
aaAAAAAAAAAAAAAAAAAAAAA3
aaAAAAAAAAAAAAAAAAAAAAA4
aaAAAAAAAAAAAAAAAAAAAAA5
aaAAAAAAAAAAAAAAAAAAAAA6
```

#### `ptn2.txt`

```text
bbBBBBBBBBBBBBBBBBBBBBB1
ccCCCCCCCCCCCCCCCCCCCCC1
ccCCCCCCCCCCCCCCCCCCCCC2
ccCCCCCCCCCCCCCCCCCCCCC3
ccCCCCCCCCCCCCCCCCCCCCC4
ccCCCCCCCCCCCCCCCCCCCCC5
ccCCCCCCCCCCCCCCCCCCCCC6
ccCCCCCCCCCCCCCCCCCCCCC7
ccCCCCCCCCCCCCCCCCCCCCC8
ccCCCCCCCCCCCCCCCCCCCCC9
```

#### `ptn3.txt`

```text
ccCCCCCCCCCCCCCCCCCCCCC1
ccCCCCCCCCCCCCCCCCCCCCC2
ccCCCCCCCCCCCCCCCCCCCCC3
ccCCCCCCCCCCCCCCCCCCCCC4
ccCCCCCCCCCCCCCCCCCCCCC5
ccCCCCCCCCCCCCCCCCCCCCC6
ccCCCCCCCCCCCCCCCCCCCCC7
ccCCCCCCCCCCCCCCCCCCCCC8
ccCCCCCCCCCCCCCCCCCCCCC9
aaAAAAAAAAAAAAAAAAAAAAA1

aaAAAAAAAAAAAAAAAAAAAAA1
aaAAAAAAAAAAAAAAAAAAAAA2
aaAAAAAAAAAAAAAAAAAAAAA3
aaAAAAAAAAAAAAAAAAAAAAA4
aaAAAAAAAAAAAAAAAAAAAAA5
aaAAAAAAAAAAAAAAAAAAAAA6
bbBBBBBBBBBBBBBBBBBBBBB1
234567
ccCCCCCCCCCCCCCCCCCCCCC1
ccCCCCCCCCCCCCCCCCCCCCC2
ccCCCCCCCCCCCCCCCCCCCCC3
ccCCCCCCCCCCCCCCCCCCCCC4
ccCCCCCCCCCCCCCCCCCCCCC5
ccCCCCCCCCCCCCCCCCCCCCC6
ccCCCCCCCCCCCCCCCCCCCCC7
ccCCCCCCCCCCCCCCCCCCCCC8
ccCCCCCCCCCCCCCCCCCCCCC9
```

## 4. コマンドの詳細

### 4.1 ファイルの定義

**形式**

```text
#file,ファイル名
```

**使用例**

```text
#file,c:\aaa.txt
```

### 4.2 ファイル出力パターンの定義

**形式**

```text
#key,パターン名
```

**使用例**

```text
#key,aaa
```

### 4.3 パターンの出力内容

**形式**

```text
#write,パターン名,文字列データ     -> 改行なし
#writeln,パターン名,文字列データ   -> 改行あり
```

**使用例**

```text
#write,aaa,ABCDEFGHIJKLMN
#writeln,aaa,ABCDEFGHIJKLMN
```

### 4.4 左スペースの出力設定

パターンを出力する際の、左側のスペース数を指定します。

**形式**

```text
#sp,パターン名,左スペース数
#sp++,パターン名,現在の左スペース数から加算する数
#sp--,パターン名,現在の左スペース数から減算する数
#sp_push,パターン名,保存キー
#sp_pop,パターン名,保存キー
```

- `#sp`：左スペース数を指定した値に設定します。
- `#sp++`：現在の左スペース数に指定した値を加算します。
- `#sp--`：現在の左スペース数から指定した値を減算します。
- `#sp_push`：現在の左スペース数を指定した保存キーに保存します。
- `#sp_pop`：保存キーに保存されている左スペース数を、現在の左スペース数に設定します。

**使用例**

```text
#writeln,aa,if (a==0){
#sp++,aa,2
#writeln,aa,b=c;
#sp--,aa,2
#writeln,aa,}
```

出力結果：

```text
if (a==0){
  b=c;
}
```

`#sp` を使用すると、直接スペース数を指定できます。

```text
#writeln,aa,if (a==0){
#sp,aa,2
#writeln,aa,b=c;
#sp,aa,0
#writeln,aa,}
```

出力結果：

```text
if (a==0){
  b=c;
}
```

### 4.5 ファイルの読み込み

**形式**

```text
#wr_file,パターン名,読み込むファイル名
```

**使用例**

```text
#wr_file,aaa,c:\aaa.dat
```

`c:\aaa.dat` を読み込み、`aaa` パターンに取り込みます。

複数のファイルを指定することもできます。

```text
#wr_file,aaa,c:\a0.dat
#wr_file,aaa,c:\a1.dat
```

上記のように記述すると、複数のファイルの内容がマージされて出力されます。

## 5. 履歴

- Ver 1.00　リリース
- Ver 1.01　`#wr` を `#write`、`#writeln` に変更
- Ver 1.02　`#sp`、`#sp++`、`#sp--` を追加
- Ver 1.03　`#wr_file` を追加
- Ver 1.04　`#sp_push`、`#sp_pop` を追加
