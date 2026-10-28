# CSVPP-C++ 表形式設計言語 仕様書 Ver.1.0

**作成日:** 2026年10月28日  
**対象:** `Product_Design_CSVPP_Ver1.0.xlsx` / CSVPP Ver.1.77  
**状態:** Productクラスのコード生成は実機ログ・生成物で確認済み。C++コンパイル／実行、一般化した設計変更テストは未実施。

## 1. 目的と適用範囲

Excelの表形式設計情報からCSVファイルを作成し、CSVPPのマクロ機能と既存のC++生成クラス `cpp_C` を利用して、C++のヘッダー（`.h`）と実装（`.cpp`）を生成する。Pythonなどの外部変換スクリプトを本経路に介在させず、CSVPP本体および既存 `cpp_C` を変更しない構成とする。

**Ver.1.0で確認した対象:** 単一の `Product` クラス、privateメンバ4個、publicメソッド9個（コンストラクタ1、getter4、setter4）、コンストラクタおよび各メソッドの本体生成。

## 2. 処理構成

```text
Excelブック Product_Design_CSVPP_Ver1.0.xlsx
 ├─ cmd          : 生成処理の入口
 ├─ usr_C        : 設計CSVの読み取り・照合・既存マクロへの変換
 ├─ cpp_C        : 既存のC++生成マクロ群（変更なし）
 ├─ Class        ──> Class.csv
 ├─ Member       ──> Member.csv
 ├─ Method       ──> Method.csv
 ├─ Argument     ──> Argument.csv
 ├─ Behavior     ──> Behavior.csv
 └─ CustomCode   ──> CustomCode.csv
               ↓
     CSVPP Ver.1.77（csvfront.exe）
               ↓
     DesignProductZ.csv（text_create用の中間入力）
               ↓
     text_create Ver.1.04
               ↓
     c:\csv\DesignProduct.h
     c:\csv\DesignProduct.cpp
```

既存の `Product` シートは参考用に残るが、Ver.1.0の `cmd` は設計CSVを読み込み、`Product.csv` に依存しない。

## 3. Excelシート・CSVデータ仕様

各表の1行目は見出し。CSVは同名で `c:\csv\` に保存する。以下の列順はVer.1.0ブックの実データに準拠する。

### 3.1 Class → Class.csv

| 列 | 名称 | 説明 | Product例 |
|---|---|---|---|
| A | ClassID | クラス識別子 | C001 |
| B | ClassName | C++クラス名 | Product |
| C | ClassType | クラス種別 | class |
| D | Description | 説明 | 任意 |

### 3.2 Member → Member.csv

| 列 | 名称 | 説明 | 例 |
|---|---|---|---|
| A | MemberID | メンバ識別子 | V004 |
| B | ClassID | 所属クラスID | C001 |
| C | MemberName | メンバ名 | stock |
| D | Type | C++型 | int |
| E | Access | アクセス指定 | private |
| F | Default | 初期値 | 空欄 |

Ver.1.0の対象メンバは `id:int`、`name:std::string`、`price:double`、`stock:int` の4個。

### 3.3 Method → Method.csv

| 列 | 名称 | 説明 | 例 |
|---|---|---|---|
| A | MethodID | メソッド識別子 | M005 |
| B | ClassID | 所属クラスID | C001 |
| C | MethodName | メソッド名 | getStock |
| D | ReturnType | 戻り値型。コンストラクタは `.` | int |
| E | Access | アクセス指定 | public |
| F | IsConst | const指定用列（Ver.1.0未対応） | 0 |

実証済みMethodID: `M001=Product`、`M002=getId`、`M003=getName`、`M004=getPrice`、`M005=getStock`、`M006=setId`、`M007=setName`、`M008=setPrice`、`M009=setStock`。

### 3.4 Argument → Argument.csv

| 列 | 名称 | 説明 | 例 |
|---|---|---|---|
| A | MethodID | 所属メソッドID | M009 |
| B | Position | 引数順序の情報 | 1 |
| C | ArgumentName | 引数名 | value |
| D | Type | C++型 | int |

実装ではMethod.csvの各メソッドに対してArgument.csvを再走査し、対応するMethodIDの引数を `#parm` に渡す。**引数出力順はCSV行順に依存**するため、Position列と行順を一致させること。

### 3.5 Behavior → Behavior.csv

| 列 | 名称 | 説明 | 例 |
|---|---|---|---|
| A | MethodID | 処理対象のメソッド | M005 |
| B | Pattern | 処理種別（実証値: getter / custom） | getter |
| C | TargetMemberID | 対象メンバID | V004 |
| D | ValueArgument | 値を渡す引数名 | value |
| E | CustomCodeRef | CustomCodeの参照キー | CODE_M009 |

`getter` はTargetMemberIDをMember.csvのMemberIDと照合し、`return <MemberName>;` を生成する。`custom` はCustomCodeRefに一致するCustomCode.csvの行をコードとして出力する。

**注意:** Ver.1.0のsetterは `setter` パターンではなく、**`custom` パターン**で実装されている。

### 3.6 CustomCode → CustomCode.csv

| 列 | 名称 | 説明 | 例 |
|---|---|---|---|
| A | CustomCodeRef | Behaviorとの結合キー | CODE_M001 |
| B | LineNo | 行番号情報 | 1 |
| C | CppCode | 出力するC++コード1行 | id = p_id; |

`CODE_M001` はコンストラクタの代入4行、`CODE_M006`～`CODE_M009` はsetter各1行を保持する。**行の生成順はCSV行順に依存するため、LineNo順に配置**する。C++コードにCSV区切りのカンマや引用符が含まれる場合のエスケープ動作は未検証。

## 4. cmdシートの処理

Ver.1.0の主要命令（ExcelのB列以降の値をCSVPP命令として示す）:

```text
%include,cpp_C.csv
%include,usr_C.csv
%classcall,usr_C,cpp
%set,output_dir,c:\csv
%shell,text_create,#c:\csv\DesignProductZ.csv
#file_def,DesignProduct
#header_h,#include <string>
#header_cpp,#include "DesignProduct.h"
#DESIGN_READ_CLASS,c:\csv\Class.csv
#DESIGN_READ_MEMBER,c:\csv\Member.csv
#DESIGN_READ_METHOD,c:\csv\Method.csv
%output
```

`%shell` は中間ファイルの生成・後段ツール連携に関与する。実行ログでは `text_create c:\csv\DesignProductZ.csv` が起動し、`.h` / `.cpp` を生成した。

## 5. usr_Cによる変換仕様

### 5.1 マクロ登録

`usr_C` に `#DESIGN_READ_CLASS`、`#DESIGN_READ_MEMBER`、`#DESIGN_READ_METHOD`、`#DESIGN_READ_BEHAVIOR` を `%alias` で登録する。Ver.0.5で `#DESIGN_READ_METHOD` が呼ばれなかった問題は、Ver.0.6で `%alias` 登録を修正して解決した。

### 5.2 CSV読み込みと見出し除外

`%textfor` でCSVを走査し、`%csv_set` で列値を変数に分解する。ClassID、MemberIDなどの見出し値を判定して先頭行を処理対象から除外する。

### 5.3 クラスとメンバ

Class.csv → `#class,<ClassName>`。Member.csv → 対応クラスのアクセス指定を切り替え、`#member,<Type>,<MemberName>`。既存 `cpp_C` がヘッダーのクラス定義を組み立てる。

### 5.4 メソッドと引数

Method.csvの行を走査し、`#method,<ReturnType>,<MethodName>` を呼び出す。続いてArgument.csvから同じMethodIDの行を検索して `#parm,<Type>,<ArgumentName>` を呼び出す。コンストラクタは戻り値の代わりに `.` を用いる。

### 5.5 本体生成

各MethodIDに対してBehavior.csvを照合する。

- `getter`: TargetMemberIDからMemberNameを取得し、`#code` で `return <MemberName>;` を出力。
- `custom`: CustomCodeRefに一致するCustomCode.csvの各CppCode行を `#code` で出力。

**重要な実装上の知見:** `#code` は対象メソッドの処理階層内で呼び出す必要がある。Ver.0.8では診断ログが出ても本体は空だったが、Ver.0.9でMethod処理内のネスト位置に修正したところ、`getStock()` の `return stock;` が出力された。Ver.1.0はこの配置を継承している。

## 6. 生成結果（実機確認済み）

生成ヘッダーの要部:

```cpp
#include <string>
#ifndef _DesignProduct_h_
#define _DesignProduct_h_
class Product{
  private:
    int id;
    std::string name;
    double price;
    int stock;
  public:
    Product(int p_id,std::string p_name,double p_price,int p_stock);
    int getId();
    std::string getName();
    double getPrice();
    int getStock();
    void setId(int value);
    void setName(std::string value);
    void setPrice(double value);
    void setStock(int value);
};
#endif  // _DesignProduct_h_
```

生成実装（実際の処理内容）:

```cpp
#include "DesignProduct.h"
Product::Product(int p_id,std::string p_name,double p_price,int p_stock){
  id = p_id;
  name = p_name;
  price = p_price;
  stock = p_stock;
}
int Product::getId(){
  return id;
}
std::string Product::getName(){
  return name;
}
double Product::getPrice(){
  return price;
}
int Product::getStock(){
  return stock;
}
void Product::setId(int value){
  id = value;
}
void Product::setName(std::string value){
  name = value;
}
void Product::setPrice(double value){
  price = value;
}
void Product::setStock(int value){
  stock = value;
}
```

ユーザー実行ログで `DESIGN_CLASS` / `DESIGN_MEMBER` / `DESIGN_METHOD` / `DESIGN_ARGUMENT` / `DESIGN_BEHAVIOR` / `DESIGN_CODE` を確認。`text_create Ver.1.04` が各 `method_body_Product_public_*` を出力し、添付の `.cpp` / `.h` で内容を確認した。

## 7. 実行手順

1. Excelの `Class`、`Member`、`Method`、`Argument`、`Behavior`、`CustomCode` シートをそれぞれ同名のCSVとして `c:\csv\` に保存する（見出し行を含む）。
2. CSVPPの通常手順で `cmd.csv`、`cpp_C.csv`、`usr_C.csv` を準備する。
3. `Product_Design_CSVPP_Ver1.0.xlsx` を `-x` に指定して実行する。
4. `[DESIGN_CODE]` ログでコンストラクタ4行、getter4行、setter4行が出ていることを確認する。
5. `c:\csv\DesignProduct.cpp` と `c:\csv\DesignProduct.h` の内容を確認する。

実機で使用されたコマンド例（実行環境依存のパスを省略表記）:

```bat
csvfront.exe c:\csv\cmd.csv -ic:\csv -xProduct_Design_CSVPP_Ver1.0.xlsx -p -o
```

## 8. バージョン別の到達点

| 版 | 検証対象 | 結果 |
|---|---|---|
| 0.1～0.2 | 設計表とCSV読込の初期構想 | 試作 |
| 0.3 | Class/Member CSV読込 | 実機ログで確認 |
| 0.4 | `#class` / `#member` 生成 | ヘッダー生成成功 |
| 0.5 | Method/Argument導入 | マクロ登録不備を検出 |
| 0.6 | `#method` / `#parm` 生成 | 9メソッド宣言生成成功 |
| 0.7 | Behavior/CustomCode処理 | Behavior呼び出し確認、本体は空 |
| 0.8 | getStockへの固定 `#code` | 診断ログ成功、本体は空 |
| 0.9 | `#code` のネスト配置修正 | getStock本体生成成功 |
| **1.0** | **Behavior / CustomCodeから本体生成** | **コンストラクタ・getter4・setter4生成成功** |

## 9. 制約・未検証事項

- 実機で確認したのは単一クラス `Product` の所定の設計データ。複数クラス、任意のClassIDに対する汎用性は未検証。
- 関数オーバーロード（異なる引数を含む）は既存CSVPP C++生成系の既知の制約であり、本仕様でも対応を保証しない。
- `IsConst`、`Default` のコードへの反映は未対応。
- getterは確認済み。独立した `setter` Patternは未実装（setterは `custom` で生成）。
- `CustomCode` の複数行はコンストラクタの4行で確認済み。ただし条件分岐、波括弧、複雑な式、カンマ・引用符を含むCSVセルは未検証。
- `Position` / `LineNo` の自動ソートは確認していない。CSVの行順を設計順に揃えること。
- CSV読込失敗、参照先ID欠落、重複ID、型不一致等に対する診断・検証仕様は未整備。
- 生成C++のコンパイル、リンク、実行、ユニットテストは未実施。
- BehaviorやCustomCodeを編集したときの変更追従テストは未実施。実証は現行Product設計データについてのもの。

## 10. 次期Ver.1.1の推奨検証項目

1. `CustomCode` による `isInStock()` の独自メソッド追加。
2. `reduceStock(int quantity)` のような条件分岐を含む複数行コードの生成。
3. 設計表の値を変更し、生成C++へ反映されることを確認する差分テスト。
4. 生成されたC++のコンパイルと簡単な実行テスト。
5. 入力データ検証、参照整合性、CSVエスケープ規則の整理。

---

### 参照資料

- `Product_Design_CSVPP_Ver1.0.xlsx`（`cmd`、`usr_C`、`cpp_C`、6つの設計表、`Ver1.0_手順`）
- ユーザー提供のCSVPP Ver.1.77実行ログ（2026年10月28日）
- 同実行で生成された `DesignProduct(6).cpp` / `DesignProduct(6).h`

本書は、上記資料で確認できた仕様と実証結果をまとめたものであり、未検証の一般化機能を実装済みとは扱わない。
