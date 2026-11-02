# CSVPP C++表形式設計・コード生成仕様書 Ver.2.7

## 1. 概要

本仕様書は、`CSVPP_CPP_Design_Ver2.7.xlsx`
を使用して、表形式の設計情報から C++
のクラス定義ファイル（`.h`）および実装ファイル（`.cpp`）を生成する仕組みをまとめたものである。

Ver.2.7 は Ver.2.6
の設計構造を引き継ぎ、診断用メソッドおよび診断用コードを取り除いた整理版である。今回の検証対象は
`Product`、`Customer`、`Order` の3クラスである。

## 2. Ver.2.7の位置付け

-   ベース：Ver.2.6
-   キー構成：`ClassName + MethodName` による複合キー方式
-   診断用メソッド：除去
-   診断用 CustomCode：除去
-   生成対象：C++ の `.cpp` と `.h`
-   検証クラス：Product / Customer / Order

本版では、生成ロジックそのものを変更するのではなく、Ver.2.6の構造を維持して診断用データを整理している。

## 3. 処理の全体像

処理は概ね次の流れで行う。

1.  Excel設計ブックを CSVPP の入力として指定する。
2.  CSVPP がクラス・メンバー情報を読み込む。
3.  Method、Argument、Behavior、CustomCode
    の各設計情報を配列に読み込む。
4.  クラスごとにメンバーおよびメソッドを抽出・生成する。
5.  クラス単位の中間データ（例：`ProductZ.csv`、`CustomerZ.csv`、`OrderZ.csv`）を作成する。
6.  `text_create` が中間データを処理し、`.cpp` と `.h` を出力する。

実行ログでは、CSVPP CSV-file preprocessor Ver 1.77、frontend Program Ver
1.18、text file creater Ver 1.04 が記録されている。

## 4. 設計データの構成

Ver.2.7の設計は、クラス情報と、メソッドを構成する複数の表を組み合わせて表現する。

### 4.1 Class

クラス単位の基本情報を管理する。

### 4.2 Member

クラスが保持するデータメンバーを管理する。検証対象では、各メンバーの型、名前、アクセス指定子などを定義する。

### 4.3 Method

メソッドの基本情報を管理する。今回の設計で確認できる主な項目は次のとおり。

-   `ClassName`：所属クラス名
-   `MethodName`：メソッド名
-   `ReturnType`：戻り値の型
-   `Access`：アクセス指定子
-   `IsConst`：const指定に関する属性

メソッドの識別・関連付けには、`ClassName` と `MethodName`
の組み合わせを使用する。

### 4.4 Argument

メソッドの引数を管理する。メソッドとの対応付けには `ClassName` と
`MethodName` を使用し、引数の順序を `Position` で表す。

### 4.5 Behavior

メソッドの動作内容を管理する。メソッドとの対応付けは `ClassName` と
`MethodName`
による。動作パターン、対象メンバー、引数名、CustomCode参照などを使って処理を表現する。

### 4.6 CustomCode

メソッド内に出力するユーザー定義コードを管理する。複数行のコードは、コード参照キーと行番号を用いて順序を保持する構成である。

## 5. キーと関連付け

Ver.2.7では、メソッドIDだけに依存せず、次の複合キーで関連情報を結び付ける。

`ClassName + MethodName`

このキーを基準として、MethodとArgument、Behaviorの情報を対応付ける。BehaviorからCustomCodeを参照する場合は、CustomCode参照キーを使用する。

### 設計上の注意

-   クラス名とメソッド名の組み合わせは一意になるように設計する。
-   同一クラス内で同じメソッド名を複数登録するオーバーロードは、本版の生成仕様では対応対象外とする。
-   引数の順番は `Position` によって管理する。
-   CustomCodeの複数行は行番号順に並ぶように登録する。

## 6. C++コード生成

### 6.1 ヘッダーファイル（.h）

クラス宣言、データメンバー、コンストラクタおよび各メソッドの宣言を出力する。

### 6.2 実装ファイル（.cpp）

コンストラクタおよび各メソッドの定義を出力する。Behaviorの定義に従い、getter、setter、その他の処理を生成する。CustomCodeを参照する場合は、そのコードをメソッド本体に出力する。

### 6.3 中間ファイルとテンプレート処理

CSVPP側でクラスごとの中間CSVを作成し、`text_create`
がテンプレート内の出力項目を処理して `.cpp` と `.h`
を生成する。実行ログでは、`header_cpp`、`method_parm_*`、`method_begin`、`method_body_*`、`method_end`、`method_define_*`
などの出力処理が確認できる。

## 7. Ver.2.7の検証対象

### 7.1 Product

メンバー：

-   `int id`
-   `std::string name`
-   `double price`
-   `int stock`

メソッド（12件）：

-   `Product(...)`
-   `getId()`
-   `getName()`
-   `getPrice()`
-   `getStock()`
-   `setId(int value)`
-   `setName(std::string value)`
-   `setPrice(double value)`
-   `setStock(int value)`
-   `isInStock()`
-   `reduceStock(int quantity)`
-   `restock(int quantity)`

確認できた主な動作：

-   getterは対応するメンバー値を返す。
-   setterは引数値を対応するメンバーに設定する。
-   `isInStock()` は在庫数が正の場合に `true` を返す。
-   `reduceStock()` は数量が0以下、または在庫不足の場合に `false`
    を返し、それ以外は在庫を減らして `true` を返す。
-   `restock()` は数量が0以下の場合に `false`
    を返し、それ以外は在庫を増やして `true` を返す。

### 7.2 Customer

メンバー：

-   `int id`
-   `std::string name`
-   `std::string email`

メソッド（5件）：

-   `Customer(...)`
-   `getId()`
-   `getName()`
-   `getEmail()`
-   `setEmail(std::string value)`

### 7.3 Order

メンバー：

-   `int orderId`
-   `int customerId`
-   `int productId`
-   `int quantity`
-   `double unitPrice`

メソッド（8件）：

-   `Order(...)`
-   `getOrderId()`
-   `getCustomerId()`
-   `getProductId()`
-   `getQuantity()`
-   `getUnitPrice()`
-   `getTotalPrice()`
-   `setQuantity(int value)`

`getTotalPrice()` は `quantity * unitPrice` を返す。

## 8. 検証結果

2026年11月2日に実施されたVer.2.7の実行結果では、次の内容が確認された。

  項目                結果
  ------------------- ---------------------------------------------
  Excel入力           Ver2.7を指定して実行
  Method配列          Product 12件、Customer 5件、Order 8件を確認
  合計メソッド数      25件
  `.cpp`生成          Product.cpp / Customer.cpp / Order.cpp
  `.h`生成            Product.h / Customer.h / Order.h
  Order最終メソッド   `setQuantity()` まで生成
  C++コンパイル       C++17でコンパイル成功
  コンパイル警告      0件
  コンパイルエラー    0件

コンパイル検証に使用したコマンド：

``` bash
g++ -std=c++17 -Wall -Wextra -pedantic -c Product.cpp Customer.cpp Order.cpp
```

この検証はコンパイル（オブジェクトファイル生成）までであり、リンクおよび実行時テストを実施したものではない。

## 9. 既知の制約・適用範囲

-   同一クラス内で同じメソッド名を持つ関数オーバーロードは、本版の設計・生成対象外である。
-   本版で確認したクラスは Product、Customer、Order の3クラスである。
-   コンパイル検証は上記3クラスの生成ソースを対象とする。
-   継承、テンプレート、例外仕様、演算子オーバーロードなどについては、本版の検証資料から対応可否を判断できないため、本仕様書では保証対象として扱わない。

## 10. Ver.2.6からの変更点

-   Ver.2.6の複合キー構成を継承。
-   診断用メソッドを削除。
-   診断用CustomCodeを削除。
-   Product / Customer / Order の通常設計データに整理。
-   3クラス、合計25メソッドで生成確認を実施。

## 11. 今後の拡張候補

以下は今後の検討候補であり、Ver.2.7で実装済みであることを示すものではない。

-   より多くのクラス・メソッドを使った生成検証
-   引数や戻り値の型の追加検証
-   constメソッド指定の生成確認
-   private / protected / public の組み合わせ検証
-   複数行CustomCodeを使った複雑なメソッドの追加検証
-   生成コードのリンク・実行テスト
-   オーバーロード対応の検討

## 12. まとめ

CSVPP C++表形式設計
Ver.2.7は、Excel上のクラス、メンバー、メソッド、引数、動作、ユーザー定義コードを組み合わせ、C++のヘッダーおよび実装ファイルを生成する検証済み構成である。

今回のProduct、Customer、Orderの3クラス、合計25メソッドについて、生成処理が正常に完了し、生成されたソースはC++17で警告・エラーなしにコンパイルできた。

Ver.2.7は、今後のC++コード生成機能を拡張するための基準版として位置付ける。

## 付録A. Ver2.7 Excelブックのシート一覧

  シート名       行数（ヘッダー含む）
  ------------ ----------------------
  cmd                              15
  usr_C                           300
  cpp_C                           711
  reference                        75
  Class                             4
  Member                           20
  Method                           26
  Argument                         21
  Behavior                         26
  CustomCode                       34
  Guide                            16
