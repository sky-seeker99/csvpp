# Text File Processing Program

Text File Processing Program

## 1. About the Program

This program processes text files according to user-defined rules.
Because the rules use a state machine, they can perform complex replacements, insertions, deletions, and other operations.
Wildcards can also be used in file names.

## 2. Usage

This is a console program.
The syntax is as follows.
text_ctl ルールファイル Files to convert [`-r`] [`-l` ログファイル] [`-buff` buffer_size]

Specify the full path to the file to convert.
The rule file is in CSV format.
Specify `-r` to search without modifying the file.
`-buff`は一回の読み書きに要する大きさ(単位はKByte)を指定します。通常は指定しませんが、ファイルサイズが大きい場合などには大きな値を指定すると有効です。The default is 10 KB.

例は以下の通りです。
text_ctl rule.csv c:\csv\*.cpp
text_ctl rule.csv c:\csv\*.cpp `-r`
text_ctl rule.csv c:\csv\*.cpp `-r` `-l` log.txt

## 3. Examples

例えば、aaa.v というファイルの module ～ endmodule 間の内容を加工する場合を想定します。

### aaa.v

module xxx
～
endmodule

module yyy
～
endmodule

module zzz
～
endmodule

At this point,Create a rule file as follows.

`#st`,IDLE
`#if`,module
  `#noif`,endmodule
    `#printf`,Step1
    `#go`,SET_A
  `#endif`
`#endif`

`#st`,SET_A
`#if`,endmodule
  `#go`,IDLE
`#else`
`#endif`

`#st`はステートマシンの状態を表します。
The example above has two states: IDLE and SET_A.
IDLE stateでは、テキストの1行に module があり、endmodule が存在しない場合に `#printf` と `#go` を実行します。
`#printf` はその行を表示します。`#go` はステートを SET_A に移します。
SET_A stateでは、endmodule が存在した場合に IDLE stateへ戻ります。

上記の記述例から具体的に加工の方法を加えますと、

`#st`,IDLE
`#if`,module
  `#noif`,endmodule
    `#printf`,Step1
    `#go`,SET_A
  `#endif`
`#endif`

`#st`,SET_A
`#if`,endmodule
  `#go`,IDLE
`#else`
  `#if`,always
    `#printf`,always
    `#ins`,"// sync_reset ""reset"""
  `#endif`
  `#if`,case
    `#printf`,register
    `#chg`,`#@@#` // paralellcase
  `#endif`
  `#if`,# register define ############################
    `#printf`,delete
    `#del`
  `#endif`
  `#if`,~reset_n
    `#printf`,repalce
    `#replace`,~reset_n,~rst_n
  `#endif`
`#endif`

上記のように記述します。

SET_A stateで always がある場合、// sync_reset "reset"
を行として追加します。
case の場合、その行の末尾に // paralellcase
を追加します。`#@@#` is replaced with the matched text.
# register define ############################
を見つけた時はその行を削除します。
~reset_n を見つけた場合、~reset_n を ~rst_n に置換します。

## 4. コマンドの詳細

### 1.ステートマシンのState name定義

Defines state machine state names.
最初に定義された状態から実行されます。

**形式**

`#st`,State name

**Example**

`#st`,IDLE

### 2.`#if`,`#noif`,`#else`,`#endif`文

`#if` は、指定した文字列が存在するかどうかを比較します。
`#noif` は、指定した文字列が存在しないことを比較します。
`#else` は、if 文に対する逆の条件になります。
`#endif` は、`#if` / `#noif` に対する終端です。
Optionに `aA_same` を指定すると、アルファベットの大文字と小文字を同一として検索します。

**形式**

`#if`,Comparison string,[`aA_same`]
`#noif`,Comparison string,[`aA_same`]
`#else`
`#endif`

**Example**

`#if`,module
  `#printf`,msg1
`#endif`

`#noif`,endmodule
  `#printf`,msg2
`#else`
  `#printf`,msg3
`#endif`

`#if`,module,`aA_same`
  `#printf`,msg1
`#endif`

### 3.コメントアウト

// がコメントアウトを示します。
// がある行はコメントとして扱われます。

**形式**

//,～,

**Example**

//,`#if`,module

### 4.状態移動

`#go` は状態遷移の命令です。
`#act` は状態を遷移させず、指定した状態をアクティブにします。これを指定すると、状態が並列に動作します。
`#st`op は、指定した状態がアクティブな場合に、その状態を停止させます。`#act` または `#go` の指定がある場合は、`#act`、`#go` が優先されます。

**形式**

`#go`,Target state
`#act`,Target state
`#st`op,Target state

**Example**

`#st`,IDLE
`#if`,module
  `#noif`,endmodule
    `#go`,SET_A
    `#act`,SET_B
  `#endif`
`#endif`

`#st`,SET_A
`#if`,endmodule
  `#st`op,SET_B
  `#go`,IDLE
`#else`
  `#if`,always
    `#printf`,always
  `#endif`
`#endif`

`#st`,SET_B
`#if`,sample1_fp
  `#printf`,printf
`#endif`

### 5.行挿入

`#ins` / `#ins`_after 命令は、指定した文字列を行として挿入します。
`#ins` は、検索文字列を含む行の前に挿入します。
`#ins`_after は、検索文字列を含む行の後に挿入します。

**形式**

`#ins`,Text to insert
`#ins`_after,Text to insert

**Example**

`#ins`,aaaaaaa
`#ins`_after,aaaaaaa

### 6.行削除

`#del` 命令は、指定した行を削除します。

**形式**

`#del`

**Example**

`#del`

### 6.行加工

`#chg` 命令は、行を加工します。`#@@#` is replaced with the text that was read.

**形式**

`#chg`,Processing instruction

**Example**

`#chg`,`#@@#` // aaa

例えば、For example, if the input text is `case(xxx)`, it is converted to `case(xxx) // aaa`.

### 7.文字列置換

`#replace` 命令は、指定した文字列を置換します。

**形式**

`#replace`,Text to find,Replacement text,[`aA_same`]
Optionに `aA_same` を指定すると、アルファベットの大文字と小文字を同一として置換します。

**Example**

`#replace`,reset_n,rst_n
`#replace`,reset_n,rst_n,`aA_same`

### 8.デバッグ

`#debug` は、CSV fileを読み込んだ状況を表示します。

**形式**

`#debug`

**Example**

`#debug`

### 9.ステートマシンのアクティブ初期設定

`#st`_init は、ステートマシンをアクティブにするための初期設定です。この設定がない場合は、最初に定義したステートマシンがアクティブになります。

**形式**

`#st`_init,State 1,State 2–,State n

**Example**

`#st`_init,idle,idle_2

### 10.ログ収集

`#log` は、指定した箇所を基準として、前の n 行から後の m 行までの内容をログとして収集します。出力形式は `#line_chg` に従います。

**形式**

`#log`,Number of preceding lines,Number of following lines

**Example**

`#log`,3,4

### 11.指定行の書き換え

`#line_chg` は、指定した行を書き換えます。

**形式**

`#line_chg`,行数,内容

**Example**

`#line_chg`,100,aaaaadd

※内容にカンマがある時は内容をダブルコーテーションで括って下さい。また、内容にダブルコーテーションがある時は２回ダブルコーテーションを記述してください。

### 12.命令のトレース

`#itrace` は、命令をトレースします。

**形式**

`#itrace`

**Example**

`#itrace`

### 13.バッファのトレース

`#trace` は、バッファをトレースします。

**形式**

`#trace`

**Example**

`#trace`

### 14.改行削除

`#retdel` は、改行を削除し、次の行とつなげます。

**形式**

`#retdel`

**Example**

`#retdel`

### 15.行にファイル挿入

`#ins`_file / `#ins`_file_after 命令は、指定したテキストファイルの内容を行として挿入します。
`#ins`_file は、検索文字列を含む行の前に挿入します。
`#ins`_file_after は、検索文字列を含む行の後に挿入します。

**形式**

`#ins`_file,Text file name
`#ins`_file_after,Text file name

**Example**

`#ins`_file,ccc.txt
`#ins`_file_after,ccc.txt

## 5. Version History

Ver 0.90  仮リリース
Ver 0.91  `-r` Option追加
Ver 0.92  バグフィックス、すべてのステートが終わった時、サーチ＆書き換えを終わらせるようにした。
　　　　　初期ステート名を複数指定できるようにした。ログをとる機能を追加しました。
Ver 0.93  バグフィックス
Ver 0.94  バグフィックス、デバッグ機能追加
Ver 0.95  `#retdel`を追加
Ver 0.97  `#ins`_afterを追加
Ver 0.98  高速化しました。不要なリターンコードを付加していたバグをフィックス。
Ver 1.00  バックグラウンドジョブで走らせるようにしました。
Ver 1.01  コマンドがNULLの時、エラーで停止してしまうバグをフィックス
Ver 1.02  4Gバイト超のファイルも扱えるようにしました。`-buff`Option追加
Ver 1.03  CSV fileのCELL内に改行があっても正しく読めるようにした。
Ver 1.04  Optionの`aA_same`追加
Ver 1.04a Optionの`aA_same`のバグフィックス
Ver 1.05  `#ins`_file,`#ins`_file_afterを追加
