# CSVPP AI連携仕様書 Ver.2.0

**対象方式：CSVPPマクロを利用したC++クラス一括生成**  
**作成日：2026年10月16日**  
**基準テンプレート：`Total_cppgen.xlsx`**

## 1. 目的

ChatGPTなどのAIが自然言語によるクラス設計の指示を受け取り、CSVPPで実行できるExcelファイル（`.xlsx`）を作成する。Ver.2.0では、クラスごとに詳細なコード生成命令を記述する代わりに、共通マクロ **`#store_member`** と **`#output_src`** を利用する。複数クラスを一つのブックで扱えることが特徴である。

この仕様は、添付された `Total_cppgen.xlsx` の実際のセル配置・マクロ定義に基づく。CSVPPの全機能を規定するものではない。

## 2. 全体の処理

```text
ユーザーの日本語による指示
          ↓
AI：クラス名・メンバ名・型を整理
          ↓
Total_cppgen.xlsxを複製し、cmdシートの入力領域を編集
          ↓
ユーザーのCSVPP環境で実行
          ↓
AddressBook.h / AddressBook.cpp などを生成
          ↓
生成結果を確認（必要に応じてC++コンパイル）
```

**運用上の原則：** AIは原則 `cmd` シートのクラス入力ブロックだけを編集し、`usr_C` と `cpp_C` の共通処理は維持する。

## 3. ブック構成

| シート | 役割 | AIによる編集 |
|---|---|---|
| `cmd` | マクロ読み込み、出力先設定、クラスごとのメンバ登録・生成指示 | **入力ブロックを編集** |
| `usr_C` | `#store_member` と `#output_src` を定義するユーザー用マクロ | 原則変更しない |
| `cpp_C` | `#class`、`#member`、`#method` などのC/C++生成処理 | 変更しない |
| `reference` | C/C++コード生成命令のリファレンス | 変更しない |

※この4シートは `Total_cppgen.xlsx` から確認した構成である。従来のクラス名別シート方式とは異なる。

## 4. cmdシートの初期設定

基準ブックの `cmd` シートでは、次のセルを使用する。

| セル | 内容 | 役割 |
|---|---|---|
| B4 | `%include` | `cpp_C` の読み込み |
| C4 | `=CONCATENATE(F4,".csv")` | `cpp_C.csv` を指定 |
| F4 | `cpp_C` | モジュール名 |
| B5 | `%include` | `usr_C` の読み込み |
| C5 | `=CONCATENATE(F5,".csv")` | `usr_C.csv` を指定 |
| F5 | `usr_C` | モジュール名 |
| B6 | `%classcall` | ユーザー用マクロの呼び出し |
| C6 / D6 | `usr_C` / `cpp` | 呼び出し対象 |
| B7 / C7 / D7 | `%set` / `output_dir` / `c:\csv` | 出力先ディレクトリ |

これらの設定はテンプレートの前提条件なので、クラスを追加するだけの場合は維持する。**`c:\csv` は基準ブックに記載された環境依存のパス**であり、別の環境では調整と検証が必要。

## 5. AIが記述する命令

### 5.1 メンバ登録：`#store_member`

| 列 | 値 | 例 |
|---|---|---|
| B | 命令名 | `#store_member` |
| C | C++型 | `std::string` |
| D | メンバ名 | `name` |

例：

```text
#store_member    int           id
#store_member    std::string   name
#store_member    double        price
#store_member    int           stock
```

### 5.2 クラス生成：`#output_src`

| 列 | 値 | 例 |
|---|---|---|
| B | 命令名 | `#output_src` |
| C | クラス名 | `Product` |

例：

```text
#output_src      Product
```

**1クラス分のメンバ登録を終えたら `#output_src` を1行記述する。** その後に次のクラスのメンバを続けられる。

## 6. 基準ブックに収録された入力例

以下は `cmd` シートの B～D 列に相当する内容である（表示上は空白で区切る）。

```text
%include        cpp_C.csv
%include        usr_C.csv
%classcall      usr_C        cpp
%set            output_dir   c:\csv

#store_member   std::string   name
#store_member   std::string   address
#store_member   std::string   phone
#store_member   std::string   email
#output_src     AddressBook

#store_member   int           id
#store_member   std::string   name
#store_member   int           age
#store_member   double        salary
#output_src     Employee

#store_member   int           id
#store_member   std::string   name
#store_member   double        price
#store_member   int           stock
#output_src     Product
```

**注意：** 実際のExcelでは上記を1セルの文章として貼り付けるのではなく、各命令と引数を所定の列に分ける。`%include` の引数は基準ブックでは数式セルになっているため、AIはその数式を維持する。

## 7. usr_Cマクロの動作（基準ブックから確認）

`usr_C` シートは `%class usr_C cpp_C` を定義し、`#store_member` と `#output_src` をエイリアス登録している。

- **`store_member`**：型と変数名を受け取り、配列変数 `m_type` と `m_name` に格納する。名前の先頭文字を大文字化した値を `m_name_upper` に保持し、`m_member_count` を加算する。
- **`output_src`**：クラス名を受け取り、`%shell text_create`、`#file_def`、`#header_h`、`#header_cpp`、`#class`、`#member`、`#method`、`#parm` などを利用して生成処理を行う。
- ヘッダー側には `#include <string>`、ソース側には `#include "クラス名.h"` を設定する。
- `usr_C` の後続部分にはコンストラクタ・getter・setterの生成処理、およびメンバ登録件数のリセット処理がある。

**重要：** `#store_member` と `#output_src` は、このブックの `usr_C` に定義されたマクロである。CSVPP本体に常に組み込まれた標準命令だとは断定しない。

## 8. AIによるExcel生成手順

1. `Total_cppgen.xlsx` をテンプレートとして複製する。
2. `cmd`、`usr_C`、`cpp_C`、`reference` の各シートを保持する。
3. `cmd` の先頭設定（4～7行目）と数式を保持する。
4. `cmd` のクラス入力領域（基準ブックでは9行目以降）を、要求されたクラス一覧に置き換える。
5. 各メンバについてB列に `#store_member`、C列に型、D列に名前を入力する。
6. クラス末尾の行でB列に `#output_src`、C列にクラス名を入力する。
7. 次のクラスがあれば空行を挟んで同様に続ける。
8. 以前のクラス入力が残らないように、使用しない旧入力行をクリアする。
9. `.xlsx` 形式で保存し、ユーザーに渡す。
10. ユーザーのCSVPPで実行し、生成された `.h` / `.cpp` を確認する。

**生成時のチェック：** クラス名とメンバ名が空欄でないこと、各クラスに `#output_src` があること、`usr_C` / `cpp_C` が保持されていること、既存の数式を壊していないことを確認する。

## 9. 入力例：AIへの依頼

> CSVPPで商品管理用の `Product` クラスを作成してください。メンバは `id:int`、`name:std::string`、`price:double`、`stock:int` です。`Total_cppgen.xlsx` のマクロ方式を使ってください。

この依頼に対してAIが追加するクラス入力部分：

| B列 | C列 | D列 |
|---|---|---|
| `#store_member` | `int` | `id` |
| `#store_member` | `std::string` | `name` |
| `#store_member` | `double` | `price` |
| `#store_member` | `int` | `stock` |
| `#output_src` | `Product` | （空欄） |

## 10. 出力と確認項目

基準マクロでは、各クラスについて以下の生成を意図している。

- `クラス名.h`：クラス定義、メンバ宣言、コンストラクタ・getter・setterの宣言
- `クラス名.cpp`：対応するメソッド実装とヘッダーファイルのinclude

実行後は、ファイル名、メンバ型と名前、関数の宣言・定義の対応、include行、クラス間のメンバ混入がないことを確認する。**CSVPPでの生成成功と、C++としてのコンパイル成功は別の検証項目**である。

## 11. Ver.1.0との違い

| 項目 | Ver.1.0（従来方式） | Ver.2.0（マクロ方式） |
|---|---|---|
| 入力の単位 | クラス別Excel／クラス別シート | 1つの`cmd`シートに複数クラス |
| 主な入力 | C++生成命令を個別に記述 | `#store_member` / `#output_src` |
| 生成処理 | 詳細命令を入力側で指定 | `usr_C` の共通マクロに集約 |
| クラス追加 | 個別シートや設定の更新 | 入力ブロックを追加 |
| AIの編集対象 | 複数箇所 | 原則 `cmd` の入力領域 |

Ver.1.0の方式を廃止するのではなく、**定型的なクラスの一括生成にはVer.2.0を優先する**。

## 12. 検証状況と制約

- `Employee`、`AddressBook`、`Product` は従来のExcel方式での生成成功がユーザーから報告されている。
- `Total_cppgen.xlsx` には3クラスのマクロ入力が存在する。**このマクロ版ブックの実行結果（生成物の一致）は、この仕様書作成時点で添付資料だけからは独立検証していない。** ユーザーからは同じファイルを生成できる旨の報告を受けている。
- 現行マクロで確認できる範囲は、メンバ変数・コンストラクタ・getter・setterを中心とした定型生成である。
- 継承、名前空間、テンプレート、複雑なメソッド本体、`const` 修飾、参照渡しなどの対応は未検証。
- マクロ内部に `c:\csv` を含む出力処理があるため、出力先変更は `cmd` の `output_dir` だけで十分とは限らない。環境変更時は検証する。

## 13. 今後の拡張候補

1. AIが任意個数のクラスを一括登録するテンプレート生成。
2. 生成結果の差分比較とコンパイル検証。
3. 出力ディレクトリの可搬性改善。
4. getter/setterの有無、アクセス修飾子、コンストラクタ引数などの指定を可能にするマクロ拡張。
5. AI向けのサンプル集と自動チェックツールの整備。

## 14. 関連資料

- `Total_cppgen.xlsx`：本仕様の基準テンプレート（`cmd` / `usr_C` / `cpp_C` / `reference`）。
- `CSVPP_AI_Integration_Spec_v1.0.md`：従来方式の仕様書。
- CSVPP GitHubリポジトリ：`sky-seeker99/csvpp`。

---

**本書の位置付け：** Ver.2.0は `Total_cppgen.xlsx` に基づくAI入力仕様の初版であり、CSVPPのマクロ方式を再現可能な形で利用するための運用仕様である。
