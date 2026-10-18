# CSVPP AI連携仕様書 Ver.3.0

**対象：ExcelテンプレートとCSVPPマクロによる複数C++クラス・独自メソッド生成**  
**作成日：2026年10月18日**  
**基準ブック：`Product_Customer_Order_csvpp(2).xlsx`**  
**位置付け：AIによるExcel生成の運用仕様。CSVPP本体の全言語仕様ではない。**

## 1. 目的と適用範囲

ユーザーが日本語でクラス、メンバ、メソッドを指示すると、AIがCSVPPで処理可能な `.xlsx` を作る。ユーザーの環境でCSVPPを実行し、クラスごとの `.h` と `.cpp` を出力する。CSVPP本体の変更は前提としない。

Ver.2.0からの拡張点は、`#output_src` の追加引数を使ってクラス専用マクロを呼び出し、独自メソッドを生成する点である。**実行成功の確認とC++のコンパイル成功は別の検証事項**とする。

## 2. 入出力と処理フロー

```text
日本語によるクラス設計
  → AIがクラス名・メンバ・メソッド・処理式を構造化
  → 動作実績のあるExcelブックを複製
  → cmd（クラス入力）とusr_C（独自マクロ）を編集
  → CSVPPで実行（ユーザー環境）
  → 各クラスの .h / .cpp を照合・必要に応じてコンパイル
```

1ブックに複数クラスを記述できる。`Product`、`Customer`、`Order` の3クラスから6ファイルを修正なしで生成できたことはユーザー報告により確認済み。

## 3. ブック構成と編集権限

| シート | 役割 | AI編集方針 |
|---|---|---|
| `cmd` | マクロ読込・出力先・クラス入力・独自マクロ指定 | **入力領域のみ編集** |
| `usr_C` | `#store_member`、`#output_src` とクラス専用マクロ | **独自マクロ定義を追加・更新**。既存共通処理は保持 |
| `cpp_C` | C++コード生成マクロ群 | 原則変更しない |
| `reference` | 命令説明 | 変更しない |

### 3.1 cmdの初期設定（維持）

| 位置 | 内容 | 備考 |
|---|---|---|
| `B4` / `C4` / `F4` | `%include` / `=CONCATENATE(F4,".csv")` / `cpp_C` | マクロ読み込み |
| `B5` / `C5` / `F5` | `%include` / `=CONCATENATE(F5,".csv")` / `usr_C` | マクロ読み込み |
| `B6:D6` | `%classcall` / `usr_C` / `cpp` | クラス呼び出し |
| `B7:D7` | `%set` / `output_dir` / `c:\csv` | 基準ブックの環境依存パス |

数式やシート名、既存マクロのセル配置を維持する。出力先は実行環境に合わせて確認する。

## 4. クラスの記述（cmdシート）

クラス入力はB～D列に分割して記入する。**次の表はセルごとの値**を示す。

| B列 | C列 | D列 | 意味 |
|---|---|---|---|
| `#store_member` | `int` | `id` | 型・メンバ名を登録 |
| `#store_member` | `std::string` | `name` | 同上 |
| `#store_member` | `double` | `price` | 同上 |
| `#store_member` | `int` | `stock` | 同上 |
| `#output_src` | `Product` | `Product_macro` | クラス生成と独自マクロ呼出し |

`#output_src` のC列はクラス名、D列は**省略可能な**独自マクロ名。独自メソッドを持たないクラスではD列を空欄にする。1クラス分のメンバを登録してから `#output_src` を置き、次のクラスの定義を続ける。`usr_C` の共通処理は出力後に登録メンバ数をリセットする。

**注：** `#store_member` と `#output_src` は基準ブックの `usr_C` で定義されるユーザーマクロであり、CSVPP本体の普遍的な組込み命令と断定しない。

## 5. 独自メソッドの記述（usr_Cシート）

### 5.1 接続規則

`usr_C` の `output_src` は `cls_name`、`macro_name` を受け取り、getter/setter生成後・ファイル出力前に、指定されたマクロを呼び出す。基準例の関連箇所は `usr_C` 45～46行および90～95行。既存処理を変更せず、クラス専用の `%st` ブロックを追加する。

### 5.2 動作実績のあるProduct_macro

`usr_C` の例（列位置を示す概念表）：

| B列 | C列 | D列 | 役割 |
|---|---|---|---|
| `%st` | `Product_macro` | | マクロ開始 |
| `#method` | `bool` | `isInStock` | メソッド宣言 |
| `#return` | `stock > 0` | | 戻り値 |
| `#method` | `double` | `getTotalPrice` | メソッド宣言 |
| `#parm` | `int` | `quantity` | 引数 |
| `#return` | `price * quantity` | | 戻り値 |

これにより、`bool isInStock()` と `double getTotalPrice(int quantity)` の宣言・実装が生成された。

### 5.3 複数文・条件分岐：reduceStock

最新版の実績例（`usr_C` 111～118行付近）：

| 行 | B列 | C列 | D列 |
|---:|---|---|---|
| 111 | `#method` | `bool` | `reduceStock` |
| 112 | `#parm` | `int` | `quantity` |
| 114 | `#if` | `quantity <= 0 \|\| quantity > stock` | |
| 115 | （空欄） | `#return` | `false` |
| 116 | `#endif` | | |
| 117 | `#set-` | `stock` | `quantity` |
| 118 | `#return` | `true` | |

**セル位置が重要：** if内部の `#return` はB列ではなくC列に配置し、式 `false` はD列に配置する。表中の `\|\|` はMarkdown表のエスケープであり、実際のExcelセルには `||` を入力する。

確認された生成結果：

```cpp
bool Product::reduceStock(int quantity){
  if (quantity <= 0 || quantity > stock){
    return(false);
  }
  stock -= quantity;
  return(true);
}
```

`Product.h` にも `bool reduceStock(int quantity);` が出力された。

## 6. cpp_C命令の分類と使用方針

以下は `cpp_C` の**定義が確認された**命令群。全命令の実行確認を意味しない。詳しい定義位置・実装は別紙 `CSVPP_CPP_Command_Reference_AI.md` を参照する。

| 分類 | 例 |
|---|---|
| 出力・ファイル | `#file_def`, `#header_h`, `#header_cpp`, `#header_ext` |
| クラス・宣言 | `#class`, `#public`, `#private`, `#protected`, `#member`, `#method`, `#parm` |
| 文出力・整形 | `#code`, `#code0`, `#code_sp` |
| 条件分岐 | `#if`, `#elseif`, `#else`, `#endif` |
| 繰り返し | `#for`, `#endfor`, `#while`, `#endwhile`, `#do_while` |
| 選択 | `#switch`, `#case`, `#default`, `#endcase`, `#endswitch` |
| 変数・演算 | `#local`, `#global`, `#set`, `#set-`, `#return` |

**区別：** `#if` はC++の条件分岐を生成するマクロ、`%if` はCSVPPのマクロ処理を制御する命令。`%st`、`%do`、`%argdef` 等もCSVPP側の制御に用いられる。両者を混同しない。

## 7. AIがExcelを生成する際の必須手順

1. **基準は最新版の動作確認済みブック** `Product_Customer_Order_csvpp(2).xlsx` とする。新規に空ブックからマクロを再構築しない。
2. 自然言語の指示を、クラス名、メンバ型・名、メソッドの戻り値型・名・引数・処理に分解する。不明な仕様は推測で固定せず確認する。
3. `cmd` の既存クラス入力部分を、指定された全クラスの `#store_member` と `#output_src` に置き換える。不要な旧入力を残さない。
4. 独自メソッドがあるクラスには一意のマクロ名（例 `Product_macro`）をD列に設定する。
5. `usr_C` の共通定義を維持し、クラス専用マクロを既存の `%st` の書式・列位置に従って追加する。重複名と古いメソッド定義を除去する。
6. メソッドが参照するメンバが同じクラスの `#store_member` に存在するか照合する。引数・型・演算式も検査する。
7. `cmd` 初期設定、数式、シート名、`cpp_C`、`reference` を維持して `.xlsx` 保存する。
8. 保存したExcelを再読込して、セル位置・式・マクロ参照・クラスごとの入力終了位置を確認する。
9. ユーザー環境のCSVPPで生成し、`.h` と `.cpp` を検査する。C++コンパイルと実行テストは別途実施する。

## 8. 検証チェックリスト

- [ ] `cmd` の `%include` と `%classcall` が維持されている。
- [ ] `cmd` の出力先ディレクトリが実行環境に合う。
- [ ] すべてのクラスに `#output_src` があり、D列のマクロ名が `usr_C` の定義と一致する。
- [ ] クラス間でメンバが混在しない。
- [ ] `.h` にクラス・メンバ・コンストラクタ・getter/setter・独自メソッド宣言がある。
- [ ] `.cpp` に対象ヘッダーのinclude、対応するメソッド実装がある。
- [ ] 条件分岐、括弧、演算子、return文が意図したC++として出力される。
- [ ] ほかのクラスの生成内容が変化していない。
- [ ] 必要に応じてコンパイラで構文・リンク・動作を確認する。

## 9. 動作実績と未検証事項

| 機能 | 根拠 | 状況 |
|---|---|---|
| 単一クラスとgetter/setter | Employee、AddressBook、Productの生成結果 | 生成確認済み |
| 3クラス一括生成 | Product・Customer・Orderの6ファイル生成（ユーザー報告） | 生成確認済み |
| 引数なし独自メソッド | `isInStock()` | 生成結果確認済み |
| 引数付き独自メソッド | `getTotalPrice(int)` | 生成結果確認済み |
| 複数文・if・減算代入 | `reduceStock(int)` | 生成結果確認済み |
| ループ、switch、複数引数、オーバーロード、const、例外処理等 | `cpp_C` に一部命令定義は存在 | **この実験群では未検証** |
| 全生成ファイルのC++コンパイル・実行 | コンパイラログなし | **未検証** |

## 10. バージョン履歴と関連資料

- **Ver.1.0**：クラス別シートによるC++生成。
- **Ver.2.0**：`#store_member` と `#output_src` による複数クラス一括生成。
- **Ver.3.0**：クラス専用マクロと独自メソッド、条件分岐・複数文生成の実績を統合。

関連ファイル：`CSVPP_AI_Integration_Spec_v1.0.md`、`CSVPP_AI_Integration_Spec_v2.0.md`、`CSVPP_AI_Custom_Method_Rules_v3_draft.md`、`CSVPP_CPP_Command_Reference_AI.md`、`Product_Customer_Order_csvpp(2).xlsx`、`Product(2).h`、`Product(2).cpp`。

---

**公開時の注意：** この文書は特定のテンプレートと確認済み出力に基づくAI向け生成仕様であり、CSVPPの全命令・全実行環境の互換性や生成C++のコンパイル成功を保証しない。
