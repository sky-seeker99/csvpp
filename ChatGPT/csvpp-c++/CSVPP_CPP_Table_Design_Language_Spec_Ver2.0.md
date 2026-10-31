# CSVPP C++ 表形式設計言語仕様書 Ver.2.0

**作成日：2026年10月31日**

## 1. はじめに

本仕様書は、CSVPPを利用してExcelの設計表から複数クラスのC++ソースコード（`.cpp` / `.h`）を生成する仕組みについて、Ver.2.0時点の構成、設計データ、生成処理、確認結果および今後の課題をまとめたものである。

本方式の目的は、C++のクラス構造やメソッドの振る舞いを表形式で記述し、CSVPPの既存のC++生成機能とテキストファイル生成・加工機能を利用してソースコードへ変換することである。

## 2. Ver.2.0の到達点

Ver.2.0では、次の3クラスを同一の設計データから生成できることを確認した。

| クラス | メンバー変数 | メソッド | 生成ファイル |
|---|---:|---:|---|
| Product | 4 | 12 | Product.cpp / Product.h |
| Customer | 3 | 5 | Customer.cpp / Customer.h |
| Order | 5 | 8 | Order.cpp / Order.h |
| **合計** | **12** | **25** | **6ファイル** |

実行ログでは、3クラスそれぞれについてクラス別の中間入力ファイルを作成し、`text_create` による `.cpp` / `.h` の出力処理を行い、最後に `convert complete` まで到達している。

## 3. 基本方針と構成

### 3.1 基本方針

- クラスの設計情報はExcelの表に記述する。
- Excelの設計表をCSVファイルとして出力し、CSVPPから読み込む。
- `usr_C` のマクロで設計データを読み取り、既存のC++生成用定義へ変換する。
- クラスごとに中間入力ファイルを作成する。
- 既存の `cpp_C` と `text_create` を利用して `.cpp` / `.h` を生成する。
- クラス数が増えても、クラスIDを基準にデータを抽出して順次処理する。

### 3.2 処理構成

```text
Excel設計ブック
  ├─ Class
  ├─ Member
  ├─ Method
  ├─ Argument
  ├─ Behavior
  └─ CustomCode
        │
        ▼ CSV出力
  Class.csv / Member.csv / Method.csv
  Argument.csv / Behavior.csv / CustomCode.csv
        │
        ▼
      CSVPP
  ├─ cmd.csv
  ├─ usr_C.csv  …… 設計データ読込・変換
  └─ cpp_C.csv  …… 既存C++生成定義
        │
        ▼ クラスごとの中間入力
  ProductZ.csv / CustomerZ.csv / OrderZ.csv
        │
        ▼ text_create
  Product.cpp / Product.h
  Customer.cpp / Customer.h
  Order.cpp / Order.h
```

## 4. Excel設計表の定義

### 4.1 Classシート

クラスの基本情報を定義する。

| 項目 | 内容 |
|---|---|
| ClassID | クラスを識別するID |
| ClassName | C++クラス名 |
| ClassType | クラス種別 |
| Description | 説明 |

Ver.2.0の定義クラスは `C001=Product`、`C002=Customer`、`C003=Order`。

### 4.2 Memberシート

クラスのメンバー変数を定義する。

| 項目 | 内容 |
|---|---|
| MemberID | メンバー変数を識別するID |
| ClassID | 所属クラスのID |
| MemberName | メンバー変数名 |
| Type | C++データ型 |
| Access | アクセス指定子 |
| Default | 初期値情報 |

Ver.2.0の生成確認対象では、各クラスのメンバー変数は `private` として生成された。`Default` の初期化への反映は、別途仕様・検証が必要である。

### 4.3 Methodシート

メソッドの宣言情報を定義する。

| 項目 | 内容 |
|---|---|
| MethodID | メソッドを識別するID |
| ClassID | 所属クラスのID |
| MethodName | メソッド名 |
| ReturnType | 戻り値の型 |
| Access | アクセス指定子 |
| IsConst | const指定に関する属性 |

`ReturnType` が `.` の場合はコンストラクタとして扱う。`IsConst` の反映は、現時点では未確認・未実装扱いとする。

### 4.4 Argumentシート

メソッドの引数を定義する。

| 項目 | 内容 |
|---|---|
| MethodID | 対象メソッドのID |
| Position | 引数の順番 |
| ArgumentName | 引数名 |
| Type | 引数の型 |

複数引数は `Position` によって順序を管理する。生成ログでは、コンストラクタの複数引数が順番に読み込まれ、生成ヘッダでは1つのコンストラクタ宣言にまとめられている。

### 4.5 Behaviorシート

メソッドの振る舞いを指定する。

| 項目 | 内容 |
|---|---|
| MethodID | 対象メソッドのID |
| Pattern | 処理パターン |
| TargetMemberID | 対象メンバー変数のID |
| ValueArgument | 値として使用する引数 |
| CustomCodeRef | 独自コードの参照ID |

確認済みの代表的な使い方：

- `getter`：対象メンバー変数を返す処理を生成する。
- `custom`：`CustomCodeRef` で指定されたコードを読み込み、メソッド本体に出力する。

### 4.6 CustomCodeシート

メソッド内部の独自C++コードを定義する。

| 項目 | 内容 |
|---|---|
| CustomCodeRef | コードブロックの識別ID |
| LineNo | コード行の順序 |
| CppCode | C++コード1行 |

複数行のコードは、同じ `CustomCodeRef` を使用し、`LineNo` 順に並べる。条件分岐や複数ステートメントを含む処理を記述できる。

## 5. クラス別の生成処理

### 5.1 クラス単位の処理

`Class` シートからクラス情報を順に取得し、各クラスについて次の処理を行う。

1. クラス名を取得する。
2. クラス名に対応する中間入力ファイル（例：`ProductZ.csv`）を開く。
3. ファイル定義、ヘッダ情報、クラス定義を出力する。
4. `Member` シートから同じ `ClassID` のメンバーを抽出する。
5. `Method` シートから同じ `ClassID` のメソッドを抽出する。
6. `Argument` シートから各メソッドの引数を取得する。
7. `Behavior` と `CustomCode` からメソッド本体を構成する。
8. 中間入力ファイルを閉じる。
9. `text_create` を実行し、`.cpp` / `.h` を生成する。
10. 次のクラスへ進む。

この方式により、クラスごとに独立したソースファイルを生成する。

### 5.2 中間入力ファイル

Ver.2.0のログで確認されたファイル名は次のとおり。

- `ProductZ.csv`
- `CustomerZ.csv`
- `OrderZ.csv`

中間入力ファイルはクラスごとに作成され、`text_create` に渡される。

## 6. Ver.2.0の生成対象

### 6.1 Product

メンバー変数：

- `int id`
- `std::string name`
- `double price`
- `int stock`

主なメソッド：

- コンストラクタ
- `getId()` / `getName()` / `getPrice()` / `getStock()`
- `setId()` / `setName()` / `setPrice()` / `setStock()`
- `isInStock()`
- `reduceStock(int quantity)`
- `restock(int quantity)`

`reduceStock` は数量が0以下の場合、または在庫数が不足する場合に `false` を返し、それ以外では在庫を減らして `true` を返す。`restock` は数量が0以下の場合に `false` を返し、それ以外では在庫を増やして `true` を返す。

### 6.2 Customer

メンバー変数：

- `int id`
- `std::string name`
- `std::string email`

主なメソッド：

- コンストラクタ
- `getId()` / `getName()` / `getEmail()`
- `setEmail(std::string value)`

### 6.3 Order

メンバー変数：

- `int orderId`
- `int customerId`
- `int productId`
- `int quantity`
- `double unitPrice`

主なメソッド：

- コンストラクタ
- `getOrderId()` / `getCustomerId()` / `getProductId()`
- `getQuantity()` / `getUnitPrice()`
- `getTotalPrice()`
- `setQuantity(int value)`

`getTotalPrice()` は `quantity * unitPrice` を返す。

## 7. CSVPP側の役割

| 構成要素 | 役割 |
|---|---|
| `cmd.csv` | CSVPPの実行指示 |
| `usr_C.csv` | 設計表CSVの読み込み、クラス・メンバー・メソッド等の変換処理 |
| `cpp_C.csv` | 既存のC++コード生成定義 |
| `text_create` | 中間入力から `.cpp` / `.h` を生成 |
| `Class.csv` 等 | Excel設計表から出力した設計データ |

本方式は既存のC++生成機能を利用する。Ver.2.0では、3クラス対応のためにクラスごとの中間入力ファイルを分ける構成が有効であることを確認した。

## 8. 実行方法

1. Excel設計ブックの `Class`、`Member`、`Method`、`Argument`、`Behavior`、`CustomCode` の各シートをCSV形式で出力する。
2. CSVPPが参照する作業フォルダ（ログ例では `c:\csv\`）に各CSVを配置する。
3. `cmd.csv`、`usr_C.csv`、`cpp_C.csv` と設計CSVが正しい場所にあることを確認する。
4. CSVPPを実行する。

実行ログに記録されたコマンド例：

```text
csvfront.exe c:\csv\cmd.csv -ic:\csv -x<設計ブックのパス> -p -o
```

実際の実行環境に合わせて、実行ファイルと設計ブックのパスを指定する。

## 9. Ver.2.0の確認結果

### 9.1 ログで確認できた事項

- `Class.csv` からProduct、Customer、Orderの3クラスが順に処理された。
- 各クラスのメンバー変数が読み込まれた。
- 各クラスのメソッドと引数が読み込まれた。
- Behavior / CustomCodeに基づくメソッド本体のコードが出力された。
- クラス別の中間入力ファイルが作成された。
- `text_create` により6つの `.cpp` / `.h` ファイルが出力された。
- 最終ログに `convert complete` が記録された。

### 9.2 生成ファイル

| クラス | ソース | ヘッダ |
|---|---|---|
| Product | Product.cpp | Product.h |
| Customer | Customer.cpp | Customer.h |
| Order | Order.cpp | Order.h |

### 9.3 検証範囲について

本仕様書の確認根拠は、提供されたCSVPP実行ログと生成された6ファイルである。ログ上のコード生成完了と、C++コンパイル・リンク・実行の検証は別の確認項目として扱う。コンパイル・リンク・実行の最終確認結果を記録する場合は、使用したコンパイラ、コマンド、実行結果を検証記録に追記する。

## 10. 現時点の制約・未確認事項

- 異なる引数構成を持つ同名メソッドのオーバーロード生成には対応していない。
- `IsConst` のC++宣言への反映は未確認。
- `Member.Default` によるメンバー変数の初期化は未確認。
- `ClassType` の利用範囲・対応するクラス種別は今後整理が必要。
- アクセス指定子は生成例では `private` メンバーと `public` メソッドを確認したが、全指定パターンの検証は今後の課題。
- クラス間の関連（例：OrderがProductやCustomerをオブジェクトとして保持する設計）は、Ver.2.0の生成対象ではIDによる参照にとどまる。
- 入力CSVの列名、列順、文字コード、空欄の扱いなどは、実際のCSVPP読み込み条件に従う必要がある。

## 11. 今後の拡張候補

1. `IsConst` の対応と検証。
2. `Member.Default` の初期化コード生成。
3. クラス間関連（メンバーとして他クラスを保持する設計）の表現。
4. `include`、継承、静的メンバー等の設計情報の追加。
5. 入力データの整合性チェック（未定義ClassID、MethodID、MemberID、重複IDなど）。
6. 生成結果のコンパイルテストを自動化する仕組み。
7. テスト用 `main.cpp` やテストコードの生成。
8. オーバーロード対応の検討。

## 12. まとめ

Ver.2.0では、Excelの表形式設計データをCSVPPで読み込み、Product・Customer・Orderの3クラスについて、クラスごとのC++ソースファイルとヘッダファイルを生成する流れを確認した。

この構成は、既存の `cpp_C` と `text_create` を活用しながら、設計情報を表に集約するものである。今後、クラス間関連や設計属性への対応、入力検証、コンパイルテストの自動化を進めることで、表形式で記述できる小さなC++設計言語として発展させることができる。
