# CSVPP C++ 設計・コード生成仕様書 Ver.2.8

## 1. 概要

本仕様書は、CSVPPを使用してExcel上の設計情報からC++のヘッダーファイル（`.h`）およびソースファイル（`.cpp`）を生成する仕組みをまとめたものです。

Ver.2.8では、従来の6つの設計シート（Class、Member、Method、Argument、Behavior、CustomCode）を、`Design`
シート1枚に統合しました。各行のA列にCSVPPコマンドを配置し、コマンドに応じて設計データの種類を判定します。

本書の対象は、ユーザー環境で生成が確認された
`CSVPP_CPP_Design_Ver2.8_Unified_Design_Sheet_fix1.xlsx` です。

## 2. Ver.2.8の構成

### 2.1 Excelシート

  シート名      役割
  ------------- --------------------------------------------
  `cmd`         CSVPPの起動・読み込み・生成処理の制御
  `usr_C`       設計データの読み込み、配列登録、生成マクロ
  `cpp_C`       C++ `.cpp` / `.h` の出力テンプレート処理
  `reference`   生成テンプレート等が参照する定義
  `Design`      クラス設計情報を集約した統合設計シート
  `Guide`       Excelブックの説明・変更履歴

旧来の `Class`、`Member`、`Method`、`Argument`、`Behavior`、`CustomCode`
の各シートは、Ver.2.8では独立したシートとして使用せず、`Design`
シートに統合しています。

### 2.2 Designシートの共通列

  列   項目         説明
  ---- ------------ -------------------------------------
  A    コマンド     行の種類を指定する `#DESIGN_READ_*`
  B    Parameter1   コマンドごとの第1引数
  C    Parameter2   コマンドごとの第2引数
  D    Parameter3   コマンドごとの第3引数
  E    Parameter4   コマンドごとの第4引数
  F    Parameter5   コマンドごとの第5引数
  G    Parameter6   コマンドごとの第6引数

B列以降は共通の列位置を使用しますが、各コマンドで意味が異なります。引数の順番は、統合前の各設計シートの構成を維持します。

## 3. Designシートのレコード形式

### 3.1 Class

コマンド：`#DESIGN_READ_CLASS`

  列   内容
  ---- ------------
  B    クラス名
  C    種別・属性
  D    説明

登録例：

``` text
#DESIGN_READ_CLASS,Product,class,商品情報を管理するクラス
```

Ver.2.8では、Product、Customer、Orderの3クラスを定義しています。

### 3.2 Member

コマンド：`#DESIGN_READ_MEMBER`

  列   内容
  ---- --------------
  B    クラス名
  C    メンバー名
  D    型
  E    アクセス指定

登録例：

``` text
#DESIGN_READ_MEMBER,Product,id,int,private
```

メンバー情報はクラス名とともに配列へ登録されます。`generate_member`
マクロが対象クラスのメンバー情報を読み出し、アクセス指定とメンバー宣言を出力します。

### 3.3 Method

コマンド：`#DESIGN_READ_METHOD`

  列   内容
  ---- --------------
  B    クラス名
  C    メソッド名
  D    戻り値の型
  E    アクセス指定
  F    const属性

登録例：

``` text
#DESIGN_READ_METHOD,Product,getId,int,public,=FALSE()
```

コンストラクタもMethodレコードとして登録します。コンストラクタの戻り値欄は
`.` です。

### 3.4 Argument

コマンド：`#DESIGN_READ_ARGUMENT`

  列   内容
  ---- ------------
  B    クラス名
  C    メソッド名
  D    引数の順番
  E    引数名
  F    引数の型

登録例：

``` text
#DESIGN_READ_ARGUMENT,Product,Product,1,p_id,int
```

引数はクラス名・メソッド名に関連付けて管理し、引数の順番に従ってメソッド宣言・定義に反映します。

### 3.5 Behavior

コマンド：`#DESIGN_READ_BEHAVIOR`

  列   内容
  ---- ------------------
  B    クラス名
  C    メソッド名
  D    動作パターン
  E    対象メンバー名
  F    値引数等
  G    CustomCode参照ID

登録例：

``` text
#DESIGN_READ_BEHAVIOR,Product,getId,getter,id
```

CustomCodeを使用する場合の例：

``` text
#DESIGN_READ_BEHAVIOR,Product,Product,custom,,,,CODE_M001
```

実際の登録では、各項目の位置をExcel上で確認し、既存レコードと同じ引数順を維持してください。

### 3.6 CustomCode

コマンド：`#DESIGN_READ_CUSTOM`

  列   内容
  ---- ------------------
  B    CustomCode参照ID
  C    C++コード1行

登録例：

``` text
#DESIGN_READ_CUSTOM,CODE_M001,id = p_id;
```

複数行のコードは、同じ参照IDを使用して複数レコードに分けて登録します。Behavior側の参照IDとCustomCode側のIDを対応させます。

## 4. Ver.2.8の登録件数

現在の統合ブックに登録されている件数は次のとおりです。

  データ種別   コマンド                       件数
  ------------ ------------------------- ---------
  Class        `#DESIGN_READ_CLASS`              3
  Member       `#DESIGN_READ_MEMBER`            12
  Method       `#DESIGN_READ_METHOD`            25
  Argument     `#DESIGN_READ_ARGUMENT`          20
  Behavior     `#DESIGN_READ_BEHAVIOR`          25
  CustomCode   `#DESIGN_READ_CUSTOM`            33
  **合計**                                 **118**

対象クラスはProduct、Customer、Orderです。

## 5. CSVPPの処理構成

基本的な処理の流れは次のとおりです。

``` text
Excelブック
   |
   v
Designシート
   |
   v
Design.csv
   |
   v
cmd
   |
   +--> cpp_C
   |
   +--> usr_C
           |
           +--> #DESIGN_READ_CLASS
           +--> #DESIGN_READ_MEMBER
           +--> #DESIGN_READ_METHOD
           +--> #DESIGN_READ_ARGUMENT
           +--> #DESIGN_READ_BEHAVIOR
           +--> #DESIGN_READ_CUSTOM
           |
           v
       設計情報を配列に登録
           |
           v
       クラス別中間CSV
       ProductZ.csv
       CustomerZ.csv
       OrderZ.csv
           |
           v
       text_create
           |
           +--> Product.cpp / Product.h
           +--> Customer.cpp / Customer.h
           +--> Order.cpp / Order.h
```

### 5.1 cmdシート

Ver.2.8では、設計データの読み込みを統合CSV 1ファイルにまとめています。

``` text
%include c:\csv\Design.csv
```

従来の6つの設計CSVを個別に読み込む構成から、`Design.csv`
だけを読み込む構成に変更しました。

### 5.2 usr_Cシート

`usr_C`
は、Design.csv内のコマンドを処理し、クラス設計情報を配列に登録します。また、登録された情報を読み出してクラス別の中間データを生成します。

### 5.3 generate_memberマクロ

`generate_member` は、メンバー変数の宣言を生成するマクロです。

処理の概要：

1.  対象クラス名を引数として受け取る。
2.  対象クラスのメンバー数を取得する。
3.  メンバー名、型、アクセス指定などを配列から読み出す。
4.  `#kind` により `private`、`public` 等のアクセス区分を設定する。
5.  `#member` によりメンバー宣言を出力する。

Ver.2.8の初回統合時に、このマクロ本体の引き継ぎ漏れがあり、生成されたヘッダーファイルからメンバー宣言が欠落しました。修正版
`fix1` では、Ver.2.7で動作確認済みの `generate_member`
マクロを復元しています。

## 6. 生成対象クラス

### 6.1 Product

メンバー：

-   `int id`
-   `std::string name`
-   `double price`
-   `int stock`

主なメソッド：

-   コンストラクタ `Product`
-   `getId`、`getName`、`getPrice`、`getStock`
-   `setId`、`setName`、`setPrice`、`setStock`
-   `isInStock`
-   `reduceStock`
-   `restock`

### 6.2 Customer

メンバー：

-   `int id`
-   `std::string name`
-   `std::string email`

主なメソッド：

-   コンストラクタ `Customer`
-   `getId`、`getName`、`getEmail`
-   `setEmail`

### 6.3 Order

メンバー：

-   `int orderId`
-   `int customerId`
-   `int productId`
-   `int quantity`
-   `double unitPrice`

主なメソッド：

-   コンストラクタ `Order`
-   `getOrderId`
-   `getCustomerId`
-   `getProductId`
-   `getQuantity`
-   `getUnitPrice`
-   `getTotalPrice`
-   `setQuantity`

## 7. Ver.2.8の変更点

### Ver.2.7からの主な変更

1.  Class、Member、Method、Argument、Behavior、CustomCodeの6シートを廃止し、Designシートに統合。
2.  DesignシートA列に各データ種別を示すCSVPPコマンドを配置。
3.  cmdシートの設計データ読み込みをDesign.csv 1ファイルに集約。
4.  既存の `#DESIGN_READ_*` コマンドと引数位置を維持する方針で統合。
5.  初回統合時に欠落した `generate_member` マクロをfix1で復元。

### 修正版ファイル

``` text
CSVPP_CPP_Design_Ver2.8_Unified_Design_Sheet_fix1.xlsx
```

このファイルをVer.2.8の修正版として扱います。

## 8. 動作確認結果

ユーザー環境でVer.2.8初回版を実行した際、生成された3つのヘッダーファイルでメンバー宣言が欠落する問題が確認されました。

原因は、統合時に `generate_member`
マクロ本体が引き継がれていなかったことです。

Ver.2.7で動作確認済みのマクロをVer.2.8へ復元し、fix1を作成しました。その後、ユーザー環境で再生成を行い、次の結果が確認されました。

-   Productの `.cpp` / `.h` が出力された。
-   Customerの `.cpp` / `.h` が出力された。
-   Orderの `.cpp` / `.h` が出力された。
-   ヘッダーファイルにメンバー定義が出力された。
-   ユーザーから「ばっちり、cppとhが出力されました」との確認を得た。

本仕様書では、上記をユーザー環境での生成確認結果として記録します。別環境での再現性や、あらゆる設計データに対する網羅的な検証を意味するものではありません。

## 9. 現時点の制約・未確認事項

-   関数のオーバーロードは未対応です。異なる引数を持つ同名メソッドの生成には対応していません。
-   `IsConst`
    相当の属性列はありますが、constメソッドの出力については本検証結果だけでは対応を確定できません。
-   継承、テンプレート、演算子オーバーロード、例外仕様などは、本版での対応を確認していません。
-   `Default`
    列によるメンバー初期値の自動生成は、本版の検証対象に含めていません。
-   クラス間の関連付けや自動 `#include` は、本版の対象外です。
-   コンパイル、リンク、実行時動作の全項目について、今回のfix1で独立した検証を行ったとは記載しません。

## 10. 今後の拡張候補

-   `generate_method`、`generate_argument`、`generate_behavior`、`generate_customcode`
    の共通化・整理
-   Designシートの入力チェックと未定義参照チェック
-   メンバー初期値の生成
-   constメソッド対応の確認
-   コンストラクタ初期化リストの生成
-   クラス間依存関係やinclude指定の管理
-   設計データからのドキュメント自動生成

## 11. まとめ

Ver.2.8では、C++クラス生成に必要な6種類の設計情報をDesignシート1枚に集約しました。A列のCSVPPコマンドによってレコード種別を判定するため、設計データを一元管理できる構成になっています。

初回統合時には `generate_member`
マクロの引き継ぎ漏れがありましたが、Ver.2.7で動作確認済みのマクロを復元したfix1で修正され、Product、Customer、Orderの
`.cpp` と `.h` がユーザー環境で生成できることを確認しました。

今後は、メンバー生成と同じ考え方で各生成マクロを整理し、Designシートを中心とした表形式C++設計・コード生成環境として発展させることができます。
