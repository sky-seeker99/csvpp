# CSVPP AI連携仕様書 Ver.1.0

**対象：ChatGPTなどのAIが、CSVPPでC++クラスを生成するためのExcelブック（`.xlsx`）を作成する方式A**  
**制定日：2026-10-16**  
**検証状況：Product.xlsxについて、利用者のWindows環境で無修正のコード生成に成功。C++コンパイル・実行試験は未実施。**

## 1. 目的と適用範囲

自然言語によるクラス設計の指示から、AIがCSVPP用Excelブックを作成する。利用者がCSVPPを実行すると、C++のヘッダー（`.h`）と実装（`.cpp`）を生成できるようにする。

```text
自然言語でクラスを指定
         ↓
AIが既存のCSVPPブックを編集して .xlsx を作成
         ↓
利用者がWindows上でCSVPPを実行
         ↓
クラス名.h ＋ クラス名.cpp
```

本仕様書は、確認済みの **Employee / AddressBook / Product** の単一クラス生成例を対象とする。CSVPPの全構文を網羅する言語仕様書ではない。

## 2. 基準となるブック

**推奨基準：生成に成功した `Product.xlsx`**。新規ブックをゼロから作成せず、既存の動作確認済みブックを複製して必要箇所を変更する。

| シート | 役割・取り扱い |
|---|---|
| `cmd` | CSVPPのトップスクリプト。処理対象名と出力関連の設定を保持する。 |
| `Product` | C++クラスを定義する入力シート。新クラス名へ改名する。 |
| `usr_C` | 既存のユーザー定義処理。原則変更しない。 |
| `cpp_C` | 既存のC/C++生成処理。原則変更しない。 |
| `reference` | 命令の参照情報。原則変更しない。 |

### 2.1 `cmd` シートで確認した配置

以下は `Product.xlsx` に実際に含まれる配置である。

| セル | 内容 | 生成時の扱い |
|---|---|---|
| B4 / F4 | `%include` / `cpp_C` | 既存設定を維持 |
| B5 / F5 | `%include` / `usr_C` | 既存設定を維持 |
| B6 / C6 / D6 | `%classcall` / `usr_C` / `cpp` | 既存設定を維持 |
| B7 / C7 / D7 | `%set` / `output_dir` / `c:\csv` | 出力先は環境に依存。必要時のみ変更 |
| B9 | `%shell` | 既存設定を維持 |
| C9 | `text_create` | 既存設定を維持 |
| F9 | `Product` | **新クラス名に変更** |
| B10 | `#file_def` | 既存設定を維持 |
| B11 | `%include` | 既存設定を維持 |
| B12 | `%output` | 既存設定を維持 |

**注意：** `cmd` シートには数式やCSVPP独自の処理が含まれる。セルの見た目だけをコピーするのではなく、**元の数式・セル配置・他シートを保存すること**。F9の変更はAddressBookの実験で必要だった修正として確認されているが、F9が内部的にどのように解釈されるかはCSVPP本体の仕様確認が必要。

## 3. クラス定義シートの記述規則

以下は `Product.xlsx` で使用し、コード生成を確認した命令とセル配置である。**B列に命令、C列以降に引数**を記入する。

| 命令 | 配置例 | 用途（確認した範囲） |
|---|---|---|
| `#header_h` | B3=`#header_h`, C3=`#include <string>` | `.h` の冒頭に記述を追加 |
| `#header_cpp` | B4=`#header_cpp`, C4=`#include "Product.h"` | `.cpp` の冒頭に記述を追加 |
| `#class` | B5=`#class`, C5=`Product` | クラス名 |
| `#private` | B6=`#private` | private領域の開始 |
| `#member` | B7=`#member`, C7=`int`, D7=`id` | 型とメンバ名 |
| `#public` | B11=`#public` | public領域の開始 |
| `#method` | B12=`#method`, C12=`.`, D12=`Product` | コンストラクタの定義例 |
| `#parm` | B13=`#parm`, C13=`int`, D13=`p_id` | 直前のメソッドの引数 |
| `#code` | B17=`#code`, C17=`id = p_id;` | 直前のメソッドの処理行 |
| `#method` | B21=`#method`, C21=`int`, D21=`getId` | 戻り値型とメソッド名 |

- `#member`、`#parm`、`#code` は必要数だけ行を追加する。
- `#method` の後に続く `#parm` と `#code` は、そのメソッドに属する配置として使用した。
- コンストラクタの型欄に置く `.` は、確認済みブックの記述を踏襲する。一般的なCSVPP構文としての意味は、別途マニュアルで確認する。
- `std::string` 型を使う場合は、確認済みの例と同様に `#header_h` で `<string>` を取り込む。

### 3.1 `Product` シートの主要データ例

```text
B3  #header_h    C3  #include <string>
B4  #header_cpp  C4  #include "Product.h"
B5  #class       C5  Product
B6  #private
B7  #member      C7  int          D7  id
B8  #member      C8  std::string  D8  name
B9  #member      C9  double       D9  price
B10 #member      C10 int          D10 stock
B11 #public
B12 #method      C12 .            D12 Product
B13 #parm        C13 int          D13 p_id
B14 #parm        C14 std::string  D14 p_name
B15 #parm        C15 double       D15 p_price
B16 #parm        C16 int          D16 p_stock
B17 #code        C17 id = p_id;
B18 #code        C18 name = p_name;
B19 #code        C19 price = p_price;
B20 #code        C20 stock = p_stock;
```

続いて、`getId` / `getName` / `getPrice` / `getStock`、`setId` / `setName` / `setPrice` / `setStock` を `#method`・`#parm`・`#code` の組み合わせで記述する。

## 4. AIが新しいクラス用ブックを作る手順

1. 利用者からクラス名、メンバ名、型、コンストラクタ、getter/setterの要否を受け取る。
2. 検証済みの `Product.xlsx` を複製する。
3. `Product` シートを新しいクラス名へ変更する。
4. `cmd!F9` を新しいクラス名へ変更する。**ほかのcmdセルは、必要性を確認できない限り変更しない。**
5. クラス定義シートの `#class` の引数を新しいクラス名にする。
6. `#header_cpp` を `#include "新クラス名.h"` にする。必要な標準ヘッダーは `#header_h` に指定する。
7. `#member`、コンストラクタ、getter、setterの各行を設計に合わせて作り直す。既存の行が残って意図しないコードを生成しないようにする。
8. `usr_C`、`cpp_C`、`reference`、数式、必要なブック構造を保持する。
9. `新クラス名.xlsx` として保存する。
10. Excelのシート名、`cmd!F9`、`#class`、include先、コンストラクタ名の整合性をチェックする。
11. 利用者がCSVPPを実行し、`.h` / `.cpp` の生成結果を確認する。

**制約：** Excelシート名には長さや使用禁止文字の制限がある。クラス名をシート名にそのまま利用できない場合の対応は、現時点では未検証。まずは英数字とアンダースコアによる短いクラス名を推奨する。

## 5. 出力の確認項目

- `.h` と `.cpp` が生成される。
- `.h` に必要な `#include`、クラス定義、メンバ宣言、メソッド宣言がある。
- `.cpp` の先頭に `#include "クラス名.h"` がある。
- コンストラクタがメンバに引数を代入する。
- getterは対応するメンバを返し、setterは対応するメンバを更新する。
- クラス名、メンバ名、型が指示と一致する。
- 追加の品質確認として、C++コンパイラでコンパイルし、必要なら実行テストを行う。

**生成成功とコンパイル成功は別である。** 今回の実験で確認できたのはCSVPPによるファイル生成と生成内容の目視確認まで。

## 6. 実験記録

| 実験 | 結果 | 分かったこと |
|---|---|---|
| `Employee.xlsx` | `.h` / `.cpp` の生成に成功 | `sample` シートを `Employee` に改名。後にシート4行目に `#header_cpp` を追加し、`.cpp` へのinclude出力を確認。 |
| `AddressBook.xlsx` | `.h` / `.cpp` の生成に成功 | `cmd` シートF9の修正が必要だった。 |
| `Product.xlsx` | **Excelの修正なしで生成に成功** | クラス名、対象シート名、cmd設定、includeを整合させたAI生成ブックで動作した。 |

`Product.h` には `id:int`、`name:std::string`、`price:double`、`stock:int`、コンストラクタ、getter/setterが生成された。`Product.cpp` には `#include "Product.h"` と各メソッドの実装が生成された。

## 7. 現時点で未検証の事項

- 任意の複雑なC++構文（継承、テンプレート、名前空間、例外、オーバーロードなど）。
- 複数クラス・複数ファイルの一括生成。
- クラス名とシート名を異なる名前にした場合の動作。
- `cmd` シート各命令・数式の内部仕様と環境差。
- Excel以外の表計算ソフトで作成したブックの完全な互換性。
- 生成コードのコンパイル・リンク・実行確認。

## 8. 今後の拡張方針

1. **Ver.1.1：** クラスの指定情報を定型化し、メンバ数が異なる複数の新規クラスで無修正生成を再現する。
2. **Ver.1.2：** コンパイル検証とエラーのフィードバックを追加する。
3. **将来版：** CSVPPマニュアルに基づき、C++以外の生成テンプレートにも対象を広げる。

## 9. 関連資料

- CSVPP GitHubリポジトリ：`https://github.com/sky-seeker99/csvpp`
- 検証済みExcel：`Employee.xlsx`、`AddressBook.xlsx`、`Product.xlsx`
- 出力例：`Employee.h/.cpp`、`AddressBook.h/.cpp`、`Product.h/.cpp`

---

本書は、実際に提供されたExcelブックと生成結果、および利用者から報告された動作確認を基にまとめた **AI連携の実証仕様（Ver.1.0）** です。未確認のCSVPP内部仕様を確定事項として扱わず、今後の検証に応じて改訂します。
