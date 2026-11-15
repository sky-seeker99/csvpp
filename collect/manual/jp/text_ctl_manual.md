# テキストファイル加工プログラム

テキストファイル加工プログラム

## 1. ソフトの紹介

本プログラムは、テキストファイルをユーザーが定義したルールに従って加工するプログラムです。
ルールにはステートマシンを使用しているため、複雑な置換、挿入、削除などの処理が可能です。
また、ファイル名にはワイルドカードを使用できます。

## 2. 使用方法

本プログラムはコンソールプログラムです。
実行形式は以下のとおりです。
text_ctl ルールファイル 変換ファイル名 [`-r`] [`-l` ログファイル] [`-buff` buffer_size]

変換ファイル名はフルパスで指定してください。
ルールファイルはCSV形式のファイルです。
`-r` を指定すると、ファイルの書き換えは行わず、検索のみを実行します。
`-buff`は一回の読み書きに要する大きさ(単位はKByte)を指定します。通常は指定しませんが、ファイルサイズが大きい場合などには大きな値を指定すると有効です。指定しない場合は10 KByteです。

例は以下の通りです。
text_ctl rule.csv c:\csv\*.cpp
text_ctl rule.csv c:\csv\*.cpp `-r`
text_ctl rule.csv c:\csv\*.cpp `-r` `-l` log.txt

## 3. 使用例

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

この時、以下のようにルールファイルを作成します。

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
上記の例には、IDLE と SET_A の2つの状態があります。
IDLE 状態では、テキストの1行に module があり、endmodule が存在しない場合に `#printf` と `#go` を実行します。
`#printf` はその行を表示します。`#go` はステートを SET_A に移します。
SET_A 状態では、endmodule が存在した場合に IDLE 状態へ戻ります。

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

SET_A 状態で always がある場合、// sync_reset "reset"
を行として追加します。
case の場合、その行の末尾に // paralellcase
を追加します。`#@@#` は読み込んだ対象の文字列に置き換えられます。
# register define ############################
を見つけた時はその行を削除します。
~reset_n を見つけた場合、~reset_n を ~rst_n に置換します。

## 4. コマンドの詳細

### 1.ステートマシンの状態名定義

ステートマシンの状態名を定義します。
最初に定義された状態から実行されます。

**形式**

`#st`,状態名

**使用例**

`#st`,IDLE

### 2.`#if`,`#noif`,`#else`,`#endif`文

`#if` は、指定した文字列が存在するかどうかを比較します。
`#noif` は、指定した文字列が存在しないことを比較します。
`#else` は、if 文に対する逆の条件になります。
`#endif` は、`#if` / `#noif` に対する終端です。
オプションに `aA_same` を指定すると、アルファベットの大文字と小文字を同一として検索します。

**形式**

`#if`,比較文字列,[`aA_same`]
`#noif`,比較文字列,[`aA_same`]
`#else`
`#endif`

**使用例**

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

**使用例**

//,`#if`,module

### 4.状態移動

`#go` は状態遷移の命令です。
`#act` は状態を遷移させず、指定した状態をアクティブにします。これを指定すると、状態が並列に動作します。
`#st`op は、指定した状態がアクティブな場合に、その状態を停止させます。`#act` または `#go` の指定がある場合は、`#act`、`#go` が優先されます。

**形式**

`#go`,指定状態
`#act`,指定状態
`#st`op,指定状態

**使用例**

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

`#ins`,挿入文字列
`#ins`_after,挿入文字列

**使用例**

`#ins`,aaaaaaa
`#ins`_after,aaaaaaa

### 6.行削除

`#del` 命令は、指定した行を削除します。

**形式**

`#del`

**使用例**

`#del`

### 6.行加工

`#chg` 命令は、行を加工します。`#@@#` は、読み込んだテキストを置き換える文字列です。

**形式**

`#chg`,加工指定

**使用例**

`#chg`,`#@@#` // aaa

例えば、読み込んだテキストが case(xxx) の場合、case(xxx) // aaa のように変換されます。

### 7.文字列置換

`#replace` 命令は、指定した文字列を置換します。

**形式**

`#replace`,置換前文字列,置換後文字列,[`aA_same`]
オプションに `aA_same` を指定すると、アルファベットの大文字と小文字を同一として置換します。

**使用例**

`#replace`,reset_n,rst_n
`#replace`,reset_n,rst_n,`aA_same`

### 8.デバッグ

`#debug` は、CSVファイルを読み込んだ状況を表示します。

**形式**

`#debug`

**使用例**

`#debug`

### 9.ステートマシンのアクティブ初期設定

`#st`_init は、ステートマシンをアクティブにするための初期設定です。この設定がない場合は、最初に定義したステートマシンがアクティブになります。

**形式**

`#st`_init,状態1,状態2～,状態n

**使用例**

`#st`_init,idle,idle_2

### 10.ログ収集

`#log` は、指定した箇所を基準として、前の n 行から後の m 行までの内容をログとして収集します。出力形式は `#line_chg` に従います。

**形式**

`#log`,前の行数,後の行数

**使用例**

`#log`,3,4

### 11.指定行の書き換え

`#line_chg` は、指定した行を書き換えます。

**形式**

`#line_chg`,行数,内容

**使用例**

`#line_chg`,100,aaaaadd

※内容にカンマがある時は内容をダブルコーテーションで括って下さい。また、内容にダブルコーテーションがある時は２回ダブルコーテーションを記述してください。

### 12.命令のトレース

`#itrace` は、命令をトレースします。

**形式**

`#itrace`

**使用例**

`#itrace`

### 13.バッファのトレース

`#trace` は、バッファをトレースします。

**形式**

`#trace`

**使用例**

`#trace`

### 14.改行削除

`#retdel` は、改行を削除し、次の行とつなげます。

**形式**

`#retdel`

**使用例**

`#retdel`

### 15.行にファイル挿入

`#ins`_file / `#ins`_file_after 命令は、指定したテキストファイルの内容を行として挿入します。
`#ins`_file は、検索文字列を含む行の前に挿入します。
`#ins`_file_after は、検索文字列を含む行の後に挿入します。

**形式**

`#ins`_file,テキストファイル名
`#ins`_file_after,テキストファイル名

**使用例**

`#ins`_file,ccc.txt
`#ins`_file_after,ccc.txt

## 5. 履歴

Ver 0.90  仮リリース
Ver 0.91  `-r` オプション追加
Ver 0.92  バグフィックス、すべてのステートが終わった時、サーチ＆書き換えを終わらせるようにした。
　　　　　初期ステート名を複数指定できるようにした。ログをとる機能を追加しました。
Ver 0.93  バグフィックス
Ver 0.94  バグフィックス、デバッグ機能追加
Ver 0.95  `#retdel`を追加
Ver 0.97  `#ins`_afterを追加
Ver 0.98  高速化しました。不要なリターンコードを付加していたバグをフィックス。
Ver 1.00  バックグラウンドジョブで走らせるようにしました。
Ver 1.01  コマンドがNULLの時、エラーで停止してしまうバグをフィックス
Ver 1.02  4Gバイト超のファイルも扱えるようにしました。`-buff`オプション追加
Ver 1.03  CSVファイルのCELL内に改行があっても正しく読めるようにした。
Ver 1.04  オプションの`aA_same`追加
Ver 1.04a オプションの`aA_same`のバグフィックス
Ver 1.05  `#ins`_file,`#ins`_file_afterを追加
