# CSVPP

## Excelからプログラムを生成する

**CSVPP（CSV-Preprocessor system）は、Excelで作成したデータや仕様をもとに、プログラム・スクリプト・バッチファイルなどを自動生成するWindows向けのコード生成システムです。**

Excelにデータや処理内容を記述すると、CSVPPがその定義に従って目的の言語・形式のコードを生成します。

> **Excelで仕様・データを作る → CSVPPで処理する → ソースコードを生成する**

という使い方ができます。

---

## CSVPPでできること

- Excelで作成した仕様からソースコードを自動生成
- 大量の定型コードを自動生成
- Excelのデータを利用した各種テキストファイルの生成
- C/C++ソースコードの生成
- Verilog-HDLの生成
- CSVデータの加工・比較・結合・変換
- スクリプト・バッチファイルなどの自動生成
- 仕様作成 → データ作成 → コード生成を一連の流れで処理

---

## こんな人におすすめ

### 組み込み・C/C++開発

大量の定型的なソースコードやデータ定義を、Excelから自動生成できます。

### FPGA / Verilog-HDL開発

Excelで管理しているデータや仕様をもとに、Verilog-HDLのコードを生成できます。

### Excelで仕様やデータを管理している人

Excelで作成した仕様・データを、そのままコード生成の入力として利用できます。

### 定型作業を自動化したい人

コピー＆ペーストや手作業によるコード作成を減らし、データから必要なファイルを自動生成できます。

---

# CSVPPの特徴

## Excelベースのコード生成

一般的なテキストエディタによるコーディングだけではなく、Excelのセルを利用してデータや処理内容を構造化して記述できます。

- セル単位でデータを編集できます
- 表形式で仕様やデータを管理できます
- Excelの操作方法をそのまま活用できます
- データとコード生成処理を同じExcel環境で管理できます

---

## 仕様書からコードを自動生成

Excelで作成した仕様をCSVPPの入力として利用し、その内容から目的の言語やテキストファイルを生成できます。

例えば、

```text
Excelで仕様を作成
        ↓
      CSVPP
        ↓
C/C++ / Verilog-HDL / Script / Text ...
```

という流れで、仕様から実装までの作業を自動化できます。

---

## 仕様・データ・コード生成を一つにつなげる

通常は、

```text
仕様書
  ↓
人が内容を確認
  ↓
プログラムを作成
  ↓
仕様変更
  ↓
プログラムを修正
```

という作業が必要になります。

CSVPPでは、

```text
Excelで仕様・データを作成
          ↓
        CSVPP
          ↓
   ソースコードを生成
```

という流れを作ることができます。

定型的なコードを自動生成することで、手作業によるミスや修正作業を減らすことを目的としています。

---

# 主な用途

## C/C++ソースコード生成

Excelのデータや仕様からC/C++ソースコードを生成できます。

C/C++ソース生成用のクラスライブラリも提供しています。

## Verilog-HDL生成

Excelで管理しているデータや仕様からVerilog-HDLを生成できます。

## テキストファイル生成

プログラムソースだけでなく、さまざまな形式のテキストファイルをデータから生成できます。

## CSVデータ処理

CSVPPにはCSVデータを扱うための各種ツールが含まれています。

CSVの加工、比較、結合、変換など、開発時に発生するさまざまなデータ処理に利用できます。

---

# 動作環境

- Microsoft Windows 10 / 11
- Microsoft Excel

---

# ダウンロード

最新版のプログラムをダウンロードして使用してください。

**最新版：2026.9.7**
- [csvpp_system_177a.zip](https://github.com/user-attachments/files/31918018/csvpp_system_177a.zip)

> ZIPファイルを展開して使用してください。
>
> CSVPPの利用には Microsoft Excel が必要です。

---

# まず試してみる

サンプルプログラムを使ってCSVPPを試すことができます。

- [filelist.xls](https://github.com/user-attachments/files/31473311/filelist.xls)

サンプルを使って、Excelで作成したデータからファイルを生成する基本的な流れを確認できます。

---

# インストールとまずは試してみる(動画)

<img width="640" height="438" alt="csvpp_install_and_exec" src="https://github.com/user-attachments/assets/ca64f838-b8bd-4e49-8b34-5ed9f7977114" />


---

# マニュアル

詳しい使い方については、リポジトリ内のマニュアルを参照してください。

- [CSVPP設定と使い方](https://github.com/user-attachments/files/31350199/CSVPP_Setup_and_Usage.xlsx) ... 2026.8.24
- [CSVPP言語マニュアル](https://github.com/user-attachments/files/31342409/CSVPP_LanguageManual.xlsx) ... 2026.8.23
- [CSVPP言語リファレンス](https://github.com/user-attachments/files/31342410/CSVPP_LanguageReferenceGuide.xlsx) ... 2026.8.23
- [テキストファイル生成と加工](https://github.com/user-attachments/files/31473250/CSVPP_TextFile_Generation_and_Processing.xlsx) ... 2026.8.26
- [バイナリファイル加工](https://github.com/user-attachments/files/31918076/CSVPP_BinaryFile_Processing.xlsx) ... 2026.9.7
- [Verilog-HDL生成](https://github.com/user-attachments/files/31876291/CSVPP_Verilog_Generation.xlsx) ... 2026.9.6

---

# CSVPPに含まれる主なツール

CSVPPには、コード生成だけでなく、CSVやテキストデータを扱うための複数のツールが含まれています。

- `csvcut` - CSVデータの加工・抽出
- `csvdiff` - CSVデータの比較
- `csvmerge` - CSVデータの結合
- `csvxml` - CSV / XML関連の処理
- `csvmake` - コード生成・ビルド関連
- `csvveri` - Verilog-HDL関連
- `csvstrcnv` - 文字列変換
- `csvtab` - CSV関連処理
- `text_create` - テキストファイル生成
- `text_ctl` - テキスト処理
- `txt_catcut` - テキストデータ処理

---

# クラスライブラリ

[C/C++ソースコードを生成するためのクラスライブラリを提供しています。](https://github.com/user-attachments/files/31517968/cpp_maker_core.xlsx) ... 2026.8.27


---

# CSVPPを使うメリット

CSVPPを利用することで、次のような作業の自動化が期待できます。

- 定型的なソースコードの作成
- 大量のデータからのコード生成
- Excelで管理している仕様のコード化
- CSVデータの加工
- テキストファイルの一括生成
- 仕様変更に伴うコード修正
- コピー＆ペーストによる作業

特に、**「データはたくさんあるが、それを決まった形式のコードやファイルに変換したい」**という用途で力を発揮します。

---

# ライセンス

CSVPPのプログラムおよびドキュメントは、

**GNU General Public License version 2.0 (GPL-2.0)**

のライセンスに従います。

詳細は `LICENSE` を参照してください。

---

# Author

**sky-seeker99**

---

# 更新情報

最新の機能追加やマニュアルについては、GitHubのコミット履歴および本リポジトリを確認してください。
