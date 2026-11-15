# Text File GenerationProgram

## 1. About the Program

This program generates text files using a variety of patterns.

## 2. Usage

This is a console program.

The syntax is as follows.

```text
text_create ルールファイル [-buff buffer_size]
```

ルールSpecify the full path to the file.

The rule file is in CSV format.

`-buff` は、1回の読み書きに使用するバッファサイズ（単位：KByte）を指定します。通常は指定する必要はありませんが、ファイルサイズが大きい場合などには、大きな値を指定すると有効です。The default is 10 KB.

### Example

```text
text_create rule.csv
```

## 3. Examples

The following is an example CSV file.

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

### Assigning Keys and Data

`#write` または `#writeln` の次のデータがキーとなり、その後のデータがそのキーに対応するデータになります。

In the example above,キーは `aa`、`bb`、`cc` となり、それぞれのキーに対するデータはThe result is as follows.

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

The data is distributed to and written to the corresponding files.

### Writing to Files

`ptn1.txt` はThe following keys are included.

```text
[aa]
```

`ptn2.txt` はThe following keys are included.

```text
[bb]
[cc]
```

`ptn3.txt` はThe following keys are included.

```text
[cc]
```

`[dd]` は存在しないキーのため、出力されません。

その後、The following keys are included.

```text
[aa]
[bb]
[cc]
```

### Output

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
#file,File name
```

**Example**

```text
#file,c:\aaa.txt
```

### 4.2 ファイル出力パターンの定義

**形式**

```text
#key,パターン名
```

**Example**

```text
#key,aaa
```

### 4.3 パターンの出力内容

**形式**

```text
#write,パターン名,String data    -> 改行なし
#writeln,パターン名,String data  -> 改行あり
```

**Example**

```text
#write,aaa,ABCDEFGHIJKLMN
#writeln,aaa,ABCDEFGHIJKLMN
```

### 4.4 左スペースの出力設定

パターンを出力する際の、左側のスペース数を指定します。

**形式**

```text
#sp,パターン名,Number of leading spaces
#sp++,パターン名,Amount to add to the current number of leading spaces
#sp--,パターン名,Amount to subtract from the current number of leading spaces
#sp_push,パターン名,保存キー
#sp_pop,パターン名,保存キー
```

- `#sp`：Number of leading spacesを指定した値に設定します。
- `#sp++`：現在のNumber of leading spacesに指定した値を加算します。
- `#sp--`：現在のNumber of leading spacesから指定した値を減算します。
- `#sp_push`：現在のNumber of leading spacesを指定した保存キーに保存します。
- `#sp_pop`：保存キーに保存されているNumber of leading spacesを、現在のNumber of leading spacesに設定します。

**Example**

```text
#writeln,aa,if (a==0){
#sp++,aa,2
#writeln,aa,b=c;
#sp--,aa,2
#writeln,aa,}
```

Output：

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

Output：

```text
if (a==0){
  b=c;
}
```

### 4.5 ファイルの読み込み

**形式**

```text
#wr_file,パターン名,File to read
```

**Example**

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

## 5. Version History

- Ver 1.00　リリース
- Ver 1.01　`#wr` を `#write`、`#writeln` に変更
- Ver 1.02　`#sp`、`#sp++`、`#sp--` を追加
- Ver 1.03　`#wr_file` を追加
- Ver 1.04　`#sp_push`、`#sp_pop` を追加
