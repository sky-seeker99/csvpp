# CSVPP-C++ 表形式設計言語仕様書 Ver.0.1

**文書種別:** 初期提案仕様（ドラフト）  
**作成日:** 2026年10月25日  
**対象:** CSVPPによるC++クラス生成とAI連携  
**状態:** 設計案。既存CSVPPでの実装可否・実際の命令書式は未検証

---

## 1. 目的

CSVPPの既存の `#class`、`#member`、`#method`、`#code` とマクロ・テキスト生成機能を活用し、Excelの表でクラス、データ、操作、引数、定型処理を記述できる**軽量な表形式設計言語**を定義する。

Ver.0.1では、C++の全構文を表現することを目標としない。**表で記述しやすい設計情報を構造化し、複雑な処理は既存の `#code` に委ねる**ことを基本方針とする。

### 1.1 目標

1. 人間とAIが同じ表形式で設計を編集できる。
2. 設計表から `.h` と `.cpp` を再現性をもって生成できる。
3. 既存のCSVPPテンプレートやマクロを極力再利用する。
4. 生成前に設計表の不整合を検出できる。
5. 既存のProduct・Customer・Orderの生成結果を回帰確認できる。

### 1.2 対象外（Ver.0.1）

- 関数オーバーロードの自動生成（既存の制限を維持）
- 継承、仮想関数、テンプレート、名前空間の完全対応
- 複雑な制御フローの表だけによる表現
- クラス間の所有権・ライフタイムの自動推論
- C++ソースから設計表への逆変換
- テストコードやUML図の正式な自動生成

## 2. アーキテクチャ

```text
自然言語・人手入力
        ↓
Excel設計表（Class / Member / Method / Argument / Behavior）
        ↓
設計表の検証・正規化（提案する前処理）
        ↓
CSVPP用中間データ・cmdシート
        ↓
既存CSVPPマクロ／#class #member #method #code
        ↓
*.h / *.cpp
```

**重要:** `Class` 等は本仕様で提案するシート名であり、CSVPPの新規命令ではない。`#class` 等の実際の書式・適用範囲は既存の `cpp_C` シート、言語マニュアルと照合して確定する。

## 3. 設計ブック構成

| シート | 役割 | Ver.0.1 |
|---|---|---|
| `Class` | クラス定義 | 必須 |
| `Member` | メンバ定義 | 必須 |
| `Method` | メソッド定義 | 必須 |
| `Argument` | 引数定義 | 必須（引数がない場合はデータ行なし） |
| `Behavior` | 定型処理の定義 | 必須（処理未指定は `custom` 扱い可） |
| `cmd` | 既存CSVPPへの橋渡し | 実装時に必要 |

将来候補: `Constraint`、`Relation`、`Test`、`Document`。Ver.0.1では独立した正式シートとしない。

### 3.1 共通表記規則

- 1行目を列見出し、2行目以降をデータ行とする（提案）。
- 空白行は無視する。識別子の前後空白は除去する。
- `ClassID`、`MemberID`、`MethodID` はブック内で一意とする。
- `ClassID` / `MethodID` によって他シートを参照する。
- C++識別子は原則 `[A-Za-z_][A-Za-z0-9_]*` とし、C++予約語は禁止する。
- 型名と式はC++テキストとして扱う。安全性や妥当性は別途検証する。
- 真偽値は `true` / `false` とする。
- 列名の大文字小文字を区別する。未定義列はVer.0.1では警告とする。
- セル中の改行・引用符・カンマの扱いは、既存CSVPPの読み込み方式に合わせて実装前に確定する。

## 4. シート仕様

### 4.1 `Class`

| 列名 | 必須 | 意味 | 例 |
|---|---|---|---|
| `ClassID` | ○ | クラス識別子 | `C001` |
| `ClassName` | ○ | C++クラス名 | `Product` |
| `Kind` | ○ | `class` / `struct` | `class` |
| `Description` | — | 責務・説明 | `商品情報を管理` |

同じ `ClassName` を複数定義してはならない。Ver.0.1では継承なしの単一クラス定義を基本とする。

### 4.2 `Member`

| 列名 | 必須 | 意味 | 例 |
|---|---|---|---|
| `MemberID` | ○ | メンバ識別子 | `V001` |
| `ClassID` | ○ | 所属クラス | `C001` |
| `MemberName` | ○ | C++変数名 | `stock` |
| `Type` | ○ | C++型 | `int` |
| `Access` | ○ | `private` / `public` / `protected` | `private` |
| `Default` | — | 初期化式 | `0` |
| `Description` | — | 意味 | `在庫数` |

同一クラス内で `MemberName` の重複は禁止する。`Default` は**C++式**であり、数値・文字列等の妥当性は生成後のコンパイルでも確認する。

### 4.3 `Method`

| 列名 | 必須 | 意味 | 例 |
|---|---|---|---|
| `MethodID` | ○ | メソッド識別子 | `M001` |
| `ClassID` | ○ | 所属クラス | `C001` |
| `MethodName` | ○ | C++関数名 | `getStock` |
| `ReturnType` | ○ | 戻り値型 | `int` |
| `Access` | ○ | 公開範囲 | `public` |
| `IsConst` | ○ | `true` / `false` | `true` |
| `Description` | — | 処理説明 | `在庫数を取得` |

同一クラス内の同名 `MethodName` は**引数が異なってもエラー**とする。コンストラクタ・デストラクタ、演算子オーバーロードはVer.0.1の表形式メソッドの対象外とし、必要に応じて既存テンプレートで扱う。

### 4.4 `Argument`

| 列名 | 必須 | 意味 | 例 |
|---|---|---|---|
| `MethodID` | ○ | 所属メソッド | `M002` |
| `Position` | ○ | 1始まりの順序 | `1` |
| `ArgumentName` | ○ | 引数名 | `quantity` |
| `Type` | ○ | C++型 | `int` |
| `Description` | — | 引数説明 | `減らす数量` |

同一メソッド内で `Position` と `ArgumentName` はそれぞれ重複禁止。順序は `Position` の昇順とする。デフォルト引数・可変長引数は対象外。

### 4.5 `Behavior`

| 列名 | 必須 | 意味 | 例 |
|---|---|---|---|
| `MethodID` | ○ | 対象メソッド | `M001` |
| `Pattern` | ○ | 処理種別 | `getter` |
| `TargetMemberID` | パターン依存 | 対象メンバ | `V004` |
| `ValueArgument` | パターン依存 | 引数名 | `quantity` |
| `Condition` | — | 条件式（Ver.0.1では原則不使用） | 空欄 |
| `CustomCodeRef` | — | `#code` に渡す既存処理参照 | 空欄 |

Ver.0.1の**正式対応パターン**は次の2種類に限定する。

| Pattern | 条件 | 生成の意味 |
|---|---|---|
| `getter` | 引数なし、戻り値型がメンバ型と一致 | `return member;` |
| `custom` | 既存テンプレートに実装を委ねる | 既存 `#code` の処理を使用 |

`setter`、`add`、`subtract`、`compare`、`validate` は**拡張候補**とする。Ver.0.1では未対応パターンを黙って生成せず、エラーにする。`custom` の具体的な参照方法は既存 `#code` の実装に合わせて確定する。

## 5. CSVPP既存命令との対応

| 設計表 | 既存命令の役割 | 変換方針 |
|---|---|---|
| `Class` | `#class` | クラス単位の生成対象を設定 |
| `Member` | `#member` | メンバ宣言を展開 |
| `Method` + `Argument` | `#method` | メソッド宣言・定義を展開 |
| `Behavior` | `#code` | 処理本文を展開または既存コードに委譲 |

これは**論理対応**であり、CSVPPの実命令の構文例を主張するものではない。実装では `cpp_C` の既存コマンドと生成結果を参照して、列からマクロ引数への変換規則を決定する。

## 6. 設計例：Product

### 6.1 Class

| ClassID | ClassName | Kind | Description |
|---|---|---|---|
| C001 | Product | class | 商品情報を管理 |

### 6.2 Member

| MemberID | ClassID | MemberName | Type | Access | Default |
|---|---|---|---|---|---|
| V001 | C001 | id | int | private | 0 |
| V002 | C001 | name | std::string | private | `""` |
| V003 | C001 | price | double | private | 0.0 |
| V004 | C001 | stock | int | private | 0 |

### 6.3 Method

| MethodID | ClassID | MethodName | ReturnType | Access | IsConst |
|---|---|---|---|---|---|
| M001 | C001 | getStock | int | public | true |
| M002 | C001 | reduceStock | bool | public | false |

### 6.4 Argument

| MethodID | Position | ArgumentName | Type |
|---|---|---|---|
| M002 | 1 | quantity | int |

### 6.5 Behavior

| MethodID | Pattern | TargetMemberID | ValueArgument | CustomCodeRef |
|---|---|---|---|---|
| M001 | getter | V004 | | |
| M002 | custom | V004 | quantity | `Product_reduceStock` |

`Product_reduceStock` は既存 `#code` 側に実装を用意するという**仮の参照名**であり、実際の参照書式は未確定。

### 6.6 期待生成結果（概念例）

`Product.h`:

```cpp
#pragma once
#include <string>

class Product {
private:
    int id = 0;
    std::string name = "";
    double price = 0.0;
    int stock = 0;
public:
    int getStock() const;
    bool reduceStock(int quantity);
};
```

`Product.cpp`:

```cpp
#include "Product.h"

int Product::getStock() const {
    return stock;
}

bool Product::reduceStock(int quantity) {
    if (quantity < 0 || quantity > stock) return false;
    stock -= quantity;
    return true;
}
```

`reduceStock` の本文は**customコードとして別途定義するもの**であり、上のBehavior表だけから自動導出されるわけではない。また、`<string>` のinclude解決はVer.0.1で実装方法を確定すべき事項である。

## 7. 検証ルール

### 7.1 エラー（生成停止）

| コード | 内容 |
|---|---|
| E001 | 必須列・必須値の欠落 |
| E002 | ID重複 |
| E003 | 参照先のClassID / MethodID / MemberIDが存在しない |
| E004 | 同一クラス内でメンバ名が重複 |
| E005 | 同一クラス内でメソッド名が重複（オーバーロード不可） |
| E006 | 引数順序・引数名の重複 |
| E007 | 未対応Behaviorパターン |
| E008 | getterの引数数・戻り値型が不整合 |
| E009 | 識別子の形式不正または予約語使用 |
| E010 | custom実装の参照が解決できない |

### 7.2 警告

| コード | 内容 |
|---|---|
| W001 | 未知の列がある |
| W002 | 説明文が空欄 |
| W003 | 初期値式の型検証が未実施 |
| W004 | C++標準ライブラリのinclude解決が未確認 |

C++コンパイラによる型検査・構文検査はCSVPP設計表の検証を補完するものとし、置き換えない。

## 8. 生成順序と再生成

1. Class・Member・Method・Argument・Behaviorの表を読み込む。
2. ID・参照・重複・パターンを検証する。
3. `ClassID`、`Position` 等で並び順を確定する。
4. 既存CSVPPが読める中間表またはcmdデータへ変換する。
5. CSVPPで `.h` / `.cpp` を生成する。
6. コンパイルし、既存サンプルと動作を比較する。

**再生成方針:** 自動生成ファイルの手修正は原則禁止する。独自処理は設計表から参照する `#code` の元データ側で管理する。生成ファイルと手書きファイルの分離方法は実装時に決定する。

## 9. AI連携の入出力契約

AIはC++本文を直接生成する代わりに、まず設計表の各行を作成する。出力時には次を満たす。

- 必須シート・必須列を省略しない。
- IDと参照関係を一意かつ整合的にする。
- 不明な設計判断を勝手に補わず、確認事項として列挙する。
- `custom` の本文は、表から推測できない場合に「要実装」と明示する。
- 既存CSVPPが未対応の構文（同名オーバーロード等）を生成しない。
- 生成前に検証ルールを適用し、エラー一覧を示す。

## 10. 受け入れ試験

| 試験ID | 内容 | 合格条件 |
|---|---|---|
| T001 | Productの基本生成 | `.h` / `.cpp` が生成されコンパイル成功 |
| T002 | getter生成 | `getStock()` が指定メンバを返す |
| T003 | custom処理 | `reduceStock()` が既存コード参照から生成される |
| T004 | メソッド名重複 | E005で生成停止 |
| T005 | 存在しないメンバ参照 | E003で生成停止 |
| T006 | 未対応パターン | E007で生成停止 |
| T007 | 再生成 | 同一入力から同一コードが生成される |
| T008 | 既存資産との比較 | Product・Customer・Orderの従来機能を損なわない |

T008は、既存の3クラスの生成Excelとソースコードを用意した段階で詳細な期待値を確定する。

## 11. 実装段階

**フェーズA：互換性調査**  
`cpp_C`、CSVPP言語マニュアル、テキスト生成マニュアル、既存Product生成ブックを照合し、既存4命令の実引数と制約を記録する。

**フェーズB：最小設計表**  
Class / Member / Method / Argument / Behaviorの5表と、`getter` / `custom` の2パターンでProductを生成する。

**フェーズC：検証機能**  
ID重複、参照切れ、同名メソッド等を検出する。

**フェーズD：拡張**  
`setter`、`add`、`subtract`、`compare`、制約、クラス間関係、テスト生成を順次検討する。

## 12. 未決定事項

1. 既存 `#class`、`#member`、`#method`、`#code` の正確な命令書式。
2. 設計表を既存 `cpp_C` に変換する方式（CSVPPマクロのみか、前処理が必要か）。
3. `CustomCodeRef` の実際の参照方式とコード保管場所。
4. `#include` の生成規則。
5. コンストラクタ・デストラクタを既存テンプレートでどう扱うか。
6. CSVPPのExcel読み込み時の空欄・改行・引用符の仕様。
7. 出力ファイル名・ディレクトリの決定規則。
8. 検証機能をCSVPP内で実現するか、AI・外部スクリプトで補完するか。

## 13. Ver.0.1の完了判定

本仕様を「実装確認済み」に進める条件は、**実際のCSVPPでProductを設計表から生成し、コンパイル・動作試験・再生成試験に合格すること**とする。それまでは本書の表・列・コード例を提案仕様として扱う。

---

### 改訂履歴

| 版 | 日付 | 内容 |
|---|---|---|
| Ver.0.1 | 2026-10-25 | 初版。5シート、基本規則、既存4命令との対応方針、Product例、検証・試験を定義 |
