# Binary File Processing Program

## 1. About the Program

This program バイナリファイルをユーザーが定義したルールに従って加工するProgramです。

ルールはステートマシンを用いるため、複雑な置換や挿入、削除などが可能です。

また、File nameにワイルドカードを使用できます。

## 2. Usage

This is a console program.

### Syntax

```text
bin_ctl ルールファイル Files to convert [-r] [-buff buffer_size]
```

Specify the full path to the file to convert.

The rule file is in CSV format.

- `-r`：書き換えは行わず、検索のみを行います。
- `-buff`: Specifies the buffer size for each read/write operation (KB).
  通常は指定する必要はありませんが、ファイルが大きい場合などには、大きな値を指定すると有効です。
  The default is 10 KB.

### Examples

```text
bin_ctl rule.csv c:\csv\*.cpp
```

```text
bin_ctl rule.csv c:\csv\*.cpp -r
```

## 3. Examples

例えば、`aaa.dat` というファイルで、`FF FF` のデータの後にある `A8 10` のデータの次のデータ内容を加工する場合を想定します。

### aaa.dat

```text
00 00 00 00 20 00 00 00 FF FF 00 00 FF FF 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
A8 10 00 00 20 00 00 00 FF FF 03 00 FF FF 01 00
00 00 00 00 10 10 11 04 00 00 00 00 00 00 00 00
```

In this case, create the rule file as follows.

```text
#st,IDLE
  #srch,0xff,0xff
  #go,SET_A

#st,SET_A
  #srch,0xa8,0x10
  #set,addr,srch_offset+1
  #printf,addr=%I64x,addr
  #chg,addr,1,0x56
  #go,IDLE
```

`#st` はステートマシンの状態を表します。

上記の例には、`IDLE` と `SET_A` の状態があります。

In the `IDLE` state, the program searches for `FF FF`.When `FF FF` is found, `#go` is executed.

`SET_A` 状態では `A8 10` をサーチし、見つかったら次のデータを `56` に書き換え、アドレスを表示します。

It then returns to the `IDLE` state.

## 4. Example

### (1) ステートマシンのState name定義

Defines state machine state names.

Execution starts with the first state defined.

ステートマシンはバイナリのパターンをサーチします。マッチすると、マッチしたところから状態遷移の持つProgramを実行します。

サーチデータは `#srch` で定義してください。

`srch_offset` 変数は見つかったアドレスになります。

#### 形式

```text
#st,State name
#srch,データ,データ,データ,～
```

#### Examples

```text
#st,IDLE
#srch,0x10,0x20,0x30
```

### (2) `#if`、`#else`、`#endif` 文

`#if` は条件分岐を行います。

`#else` は `#if` に対する逆の条件になります。

`#endif` は `#if` に対する終端です。

#### 形式

```text
#if,条件式
#else
#endif
```

#### Examples

```text
#if,a==0x90
  #printf,msg1
#endif
```

```text
#if,b==c+1
  #printf,msg2
#else
  #printf,msg3
#endif
```

### (3) 代入式

変数の定義と計算式の実行を行います。

#### 形式

```text
#set,変数名,式
```

#### Examples

```text
#set,a,b+10
```

### (4) 状態移動

`#go` は状態遷移の命令です。

`#act` は状態を遷移させず、指定した状態をアクティブにします。これを指定すると、状態が並列に動作します。

`#stop` は指定した状態がアクティブのときに停止させます。`#act` や `#go` の指定がある場合は、`#act`、`#go` が優先されます。

#### 形式

```text
#go,Target state
#act,Target state
#stop,Target state
```

#### Examples

```text
#st,IDLE
#srch,0x10
#read,a,srch_addr+1
#if,a==0
  #go,SET_A
  #act,SET_B
#endif

#st,SET_A
#srch,0x20
#read,b,srch_addr+1
#read,c,srch_addr+2
#if,b==0
  #stop,SET_B
  #go,IDLE
#else
  #if,c==0
    #printf,match
  #endif
#endif

#st,SET_B
#srch,0x30,0x30
#read,b,srch_addr+2
#if,b==0
  #printf,printf
#endif
```

### (5) バイナリ操作

`#chg` はデータの書き換え、削除、挿入を行います。

#### 形式

```text
#chg,アドレス,対象サイズ,書き換えデータ,書き換えデータ,書き換えデータ,～
```

> 対象サイズ分を削除して、書き換えデータ分を挿入します。挿入データがなければ削除し、対象サイズが0ならば挿入します。

#### Examples

```text
#chg,srch_addr+10,1,a+b
#chg,srch_addr+10,1
#chg,srch_addr+10,0,0x10,a,b
```

### (6) 指定アドレスデータ読み出し

`#read` 命令は、指定アドレスの内容を読み出します。

#### 形式

```text
#read,変数名,アドレス
```

#### Examples

```text
#read,a,srch_addr+10
```

### (7) ステートマシンのアクティブ初期設定

`#st_init` は、ステートマシンをアクティブにするための初期設定です。

本設定がない場合は、一番初めに定義したステートマシンがアクティブになります。

#### 形式

```text
#st_init,State 1,State 2–,State n
```

#### Examples

```text
#st_init,idle,idle_2
```

### (10) コンソール表示

`#printf` は表示を行います。

#### 形式

```text
#printf,書式,式,式,式,式～
```

書式は、式を10進表示したい場合は `%I64d`、16進表示したい場合は `%I64x` を指定してください。

#### Examples

```text
#printf,addr=%I64x,srch_addr
```

## 5. Version History

- **Ver 0.90**　仮リリース
