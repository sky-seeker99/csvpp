# CSVPP AI連携：独自メソッド追加のExcel生成ルール（Ver.3.0 草案）

## 1. 対象と根拠

対象は、動作確認済みの `Product_Customer_Order_csvpp(1).xlsx` のマクロ方式。`cmd`、`usr_C`、`cpp_C`、`reference` の4シートを維持する。今回のExcelから生成された `Product.h` と `Product.cpp` に `isInStock`、`getTotalPrice` が含まれることを確認済み。以下のセル位置はこの版のExcelに基づく。

## 2. 処理の流れ

1. `cmd!B4:C6` で `cpp_C.csv`、`usr_C.csv` を読み込み、`usr_C` クラスを呼び出す。
2. `cmd` シートに `#store_member` を並べてメンバを登録する。
3. `#output_src` の **第1引数（C列）** にクラス名、**第2引数（D列、省略可）** に独自メソッドのマクロ名を指定する。
4. `usr_C` シートの `output_src` マクロが、コンストラクタとgetter/setterを組み立てた後、指定された独自マクロを呼び出す。
5. `#method`、`#parm`、`#return` などを `cpp_C` が処理し、`.h` と `.cpp` を生成する。

## 3. cmdシートの書式

今回のProduct定義は以下のセル配置。

| セル | 値 | 意味 |
|---|---|---|
| B9 / C9 / D9 | `#store_member` / `int` / `id` | メンバ登録 |
| B10 / C10 / D10 | `#store_member` / `std::string` / `name` | メンバ登録 |
| B11 / C11 / D11 | `#store_member` / `double` / `price` | メンバ登録 |
| B12 / C12 / D12 | `#store_member` / `int` / `stock` | メンバ登録 |
| B13 / C13 / D13 | `#output_src` / `Product` / `Product_macro` | クラス生成と追加マクロ指定 |

**注意：** D13の `Product_macro` が独自メソッド生成を有効にする。`Customer` と `Order` の `#output_src` はD列を空欄にしている。

## 4. usr_Cシートの独自マクロ定義

実例は `usr_C!B102:D109`。

| 行 | B列 | C列 | D列 |
|---|---|---|---|
| 102 | `%st` | `Product_macro` | |
| 104 | `#method` | `bool` | `isInStock` |
| 105 | `#return` | `stock > 0` | |
| 107 | `#method` | `double` | `getTotalPrice` |
| 108 | `#parm` | `int` | `quantity` |
| 109 | `#return` | `price * quantity` | |

これによって、次の宣言と実装が出力された。

```cpp
// Product.h の宣言
bool isInStock();
double getTotalPrice(int quantity);

// Product.cpp の実装
bool Product::isInStock(){
  return(stock > 0);
}
double Product::getTotalPrice(int quantity){
  return(price * quantity);
}
```

## 5. 既存の共通マクロとの接続

`usr_C!B45:D46` で `output_src` を定義し、`%argdef` の `cls_name`、`macro_name` を受け取る。`usr_C!B90:D92` の処理は以下。

```text
%noif    macro_name
  %do   $macro_name$
%endif
```

この位置はgetter/setter生成後、`%output`（94行目）の前にある。したがって、独自メソッドは同じクラスの生成内容に組み込まれる。`%output` の後にメンバ登録数が0へ戻される（95行目）。

## 6. AIがExcelを編集するときの規則

1. **正常動作したブックをコピーして使う。** `cpp_C` と `reference` は変更しない。
2. `cmd` に必要な `#store_member` 行を追加し、各クラス末尾に `#output_src` を置く。
3. 独自メソッドがあるクラスだけ `#output_src` のD列に一意のマクロ名を入れる。
4. `usr_C` の既存の共通定義を保持し、追加マクロを既存の `Product_macro` と同じ形式で定義する。クラス名・マクロ名・型・引数・式は整合させる。
5. `#method` で戻り値型とメソッド名、`#parm` で引数、`#return` で返す式を指定する。複数メソッドは同じマクロ内に順番に記述できる。
6. メソッドが参照するメンバ（例：`stock`、`price`）が `#store_member` で登録されていることを確認する。
7. 他のクラスに影響しないよう、マクロ名の重複、出力先、メンバ登録数のリセットを確認する。
8. 数式、セル配置、シート名、既存マクロを保持して保存する。

## 7. 生成後の検証

- `.h` に追加メソッドの宣言がある。
- `.cpp` に同名・同型・同引数の実装がある。
- `.cpp` 先頭で対象ヘッダーをincludeしている。
- 既存のコンストラクタ、getter、setterが失われていない。
- 他クラスの生成内容が変わっていない。
- C++コンパイラによるビルド確認は別途行う。

## 8. 未検証の範囲

今回のファイルで実証されたのは、**引数なしboolメソッド**と**int引数を1つ持つdoubleメソッド**、および `#return` による単一式の生成。複数引数、`void` メソッド、条件分岐、ループ、複数文、オーバーロード、`const` 修飾などは、この実例だけでは動作保証できない。対応には `cpp_C` の命令仕様確認と追加実験が必要。

## 9. 次の検証候補

`Product` に `reduceStock(int quantity)` を追加し、在庫数の検証と減算を伴う複数文メソッドを生成できるか試す。まず `cpp_C` と `reference` の対応命令を確認し、実際のCSVPP実行結果で仕様を確定する。
