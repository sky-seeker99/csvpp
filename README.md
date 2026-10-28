<!-- CSVPP - Generate C/C++, Verilog-HDL, scripts and text files from Excel data and specifications. -->

<!-- CSVPP (CSV-Preprocessor system) is a code generation system for Windows that automatically generates programs, scripts, batch files, and more based on data and specifications created in Excel. -->

# <img width="272" height="90" alt="csvpp_tag" src="https://github.com/user-attachments/assets/4e7b423a-ee63-4bff-a92e-96e39b48b21e" />

![License](https://img.shields.io/badge/license-Apache--2.0-blue.svg)
![Platform](https://img.shields.io/badge/platform-Windows-lightgrey.svg)
![Language](https://img.shields.io/badge/language-C%2B%2B-orange.svg)

## Excelからプログラムを生成する

**CSVPP（CSV-Preprocessor system）は、Excelで作成したデータや仕様をもとに、プログラム・スクリプト・バッチファイルなどを自動生成するWindows向けのコード生成システムです。どの様な言語を作るにしても単一のCSVPP言語を記述する事で事足ります。**

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
- 検証用CPUを生成する事で検証時間が非常に短縮できます。
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
- Microsoft Excel or Libre Office

---

# ダウンロード

最新版のプログラムをダウンロードして使用してください。

**最新版：2026.10.3**

- [csvpp_system_177a_20261003-1.zip](https://github.com/sky-seeker99/csvpp/releases/download/Ver-1.77a-20261003/csvpp_system_177a_20261003-1.zip)

> ZIPファイルを展開して使用してください。
> 
> CSVPPは Microsoft Excel または LibreOffice Calc で使用できます。

---

# まず試してみる

サンプルプログラムを使ってCSVPPを試すことができます。

- [filelist.xls](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/filelist.xls)

サンプルを使って、Excelで作成したデータからファイルを生成する基本的な流れを確認できます。

---

# インストールとまずは試してみる(動画)

<img width="640" height="438" alt="csvpp_install_and_exec" src="https://github.com/user-attachments/assets/ca64f838-b8bd-4e49-8b34-5ed9f7977114" />

---

# マニュアル

詳しい使い方については、リポジトリ内のマニュアルを参照してください。

- [CSVPP設定と使い方](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/CSVPP_Setup_and_Usage.xlsx) 
- [CSVPP言語マニュアル](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/CSVPP_LanguageManual.xlsx) 
- [CSVPP言語リファレンス](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/CSVPP_LanguageReferenceGuide.xlsx) 
- [テキストファイル生成と加工](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/CSVPP_TextFile_Generation_and_Processing.xlsx) 
- [バイナリファイル加工](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/CSVPP_BinaryFile_Processing.xlsx) 
- [Verilog-HDL生成](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/CSVPP_Verilog_Generation.xlsx)
- [Excel⇔CSV変換(Libre Office版](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/CSVPP_Converting_LibreCalc_CSV.xlsx) 
- [Excel⇔CSV変換(Microsoft Excel版)](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/CSVPP_Converting_Excel_CSV.xlsx)
- [Excel⇔CSV変換便利ツール(フィルタプログラム)](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/CSVPP_Utility_CSV_tool.xlsx) 

---

# CSVPPに含まれる主なツール

CSVPPには、コード生成だけでなく、CSVやテキストデータを扱うための複数のツールが含まれています。

- [csvmake.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvmake.exe)  -  Excel→CSV変換   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvmake_manual.md)
- [csvmake2.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvmake2.exe)  -  CSV→Excel変換   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvmake2_manual.md)
- [csvmake3.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvmake3.exe)  -  Excel→CSV変換(大量変換用)   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvmake3_manual.md)
- [csvmake4.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvmake4.exe)  -  CSV→Excel変換(大量変換用)   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvmake4_manual.md)
- [csvmake_ooo.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvmake_ooo.exe)  -  Excel→CSV変換 for LibreOffice  
- [csvmake2_ooo.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvmake2_ooo.exe)  -  CSV→Excel変換 for LibreOffice  
- [csvmake3_ooo.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvmake3_ooo.exe)  -  Excel→CSV変換 for LibreOffice(大量変換用)  
- [csvmake4_ooo.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvmake4_ooo.exe)  -  CSV→Excel変換 for LibreOffice(大量変換用)  
- [bin_catcut.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/bin_catcut.exe)  -  バイナリファイル連結・分割   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/bin_catcut_manual.md)
- [bin_ctl.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/bin_ctl.exe)  -  バイナリファイル加工   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/bin_ctl_manual.md)
- [bincsv.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/bincsv.exe)  -  バイナリ→CSV変換   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/bincsv_manual.md)
- [csvbin.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvbin.exe)  -  CSV→バイナリ変換   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvbin_manual.md)
- [text_create.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/text_create.exe)  -  テキストファイル生成   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/text_create_manual.md)
- [text_ctl.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/text_ctl.exe)  -  テキストファイル加工   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/text_ctl_manual.md)
- [txt_catcut.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/txt_catcut.exe)  -  テキストファイル連結・分割   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/txt_catcut_manual.md)
- [logcat.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/logcat.exe)  -  LOG連結   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/logcat_manual.md)
- [retchg.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/retchg.exe)  -  改行コード変換   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/retchg_manual.md)
- [csvxml.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvxml.exe)  -  CSV→XML変換   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvxml_manual.md)
- [csvhtml.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvhtml.exe)  -  CSV→HTML変換   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvhtml_manual.md)
- [htmlcsv.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/htmlcsv.exe)  -  HTML→CSV変換   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/htmlcsv_manual.md)
- [eucsjis.csv](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/eucsjis.csv)  -  SJIS-EUC変換用定義ファイル  
- [eucsjis.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/eucsjis.exe)  -  SJIS-EUC変換   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/eucsjis_manual.md)
- [eucsjis2.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/eucsjis2.exe)  -  SJIS-EUC変換   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/eucsjis2_manual.md)
- [nullchg.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/nullchg.exe)  -  NULL変換   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/nullchg_manual.md)
- [csvcellretchg.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvcellretchg.exe)  -  CSVファイルセル内改行コード変換   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvcellretchg_manual.md)
- [csvcellretchg2.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvcellretchg2.exe)  -  CSVファイルセル内改行コード変換   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvcellretchg2_manual.md)
- [csvmerge.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvmerge.exe)  -  CSVファイル横マージ   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvmerge_manual.md)
- [csvcut.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvcut.exe)  -  CSVファイル項目抽出   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvcut_manual.md)
- [csvdiff.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvdiff.exe)  -  CSV-DIFF   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvdiff_manual.md)
- [c_cmt_del.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/c_cmt_del.exe)  -  C/C++コメント削除   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/c_cmt_del_manual.md)
- [c_cmt_del2.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/c_cmt_del2.exe)  -  C/C++コメント削除   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/c_cmt_del2_manual.md)
- [jpegcsv.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/jpegcsv.exe)  -  JPEG,BMP→CSVファイル変換   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/jpegcsv_manual.md)
- [csvjpeg.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvjpeg.exe)  -  CSVファイル → JPEG,BMPファイル変換   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvjpeg_manual.md)
- [csvtab.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvtab.exe)  -  CSVファイル → TABファイル変換   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvtab_manual.md)
- [tabcsv.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/tabcsv.exe)  -  TABファイル → CSVファイル変換   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/tabcsv_manual.md)
- [csvstrcnv.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvstrcnv.exe)  -  CSV 数値→文字列変換   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvstrcnv_manual.md)
- [retconv.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/retconv.exe)  -  Excel 用 CSV 改行コード変換   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/retconv_manual.md)
- [retconv2.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/retconv2.exe)  -  Excel 用 CSV 改行コード変換   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/retconv2_manual.md)
- [retconv3.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/retconv3.exe)  -  FileMaker 用 CSV 改行コード変換  
- [retconv4.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/retconv4.exe)  -  FileMaker 用 CSV 改行コード変換  

---

# サンプルファイル

## テキストファイルを生成するサンプルファイル

- [text_file_gen_sample1.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvpp_sample/text_file_gen_sample1.xlsx) 
- [text_file_gen_sample2.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvpp_sample/text_file_gen_sample2.xlsx) 

## ソースコードのヘッダを差し替えるサンプルファイル

- [replace_license_header.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvpp_sample/replace_license_header.xlsx)

## 大量のテキストファイルを生成するサンプルファイル

- [json_file_gen_sample.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvpp_sample/json_file_gen_sample.xlsx) 

## C++コードを生成するサンプルファイル

- [cpp_maker.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvpp_sample/cpp_maker.xlsx) 

## Verilogを生成するサンプルファイル

- [csvveri_sample_top.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvveri_2_sample/csvveri_sample_top.xlsx) 
- [csvveri_sample.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvveri_2_sample/csvveri_sample.xlsx) 

---

# CSVPP言語で記述されたツール

- [grep_textcut.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvpp_app/grep_textcut.xlsx)  -  拡張Grep&テキスト分割プログラム  
- [filelist2xls.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvpp_app/filelist2xls.xlsx)  -  ディレクトリ＆ファイルリスト作成プログラム   

---

# クラスライブラリ

- [C/C++ソースコード生成クラスライブラリ](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvpp_app/cpp_maker_core.xlsx)

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

**Apache License Version 2.0**

のライセンスに従います。

詳細は `LICENSE` を参照してください。

---

# Author

**sky-seeker99**

---

# 更新情報

最新の機能追加やマニュアルについては、GitHubのコミット履歴および本リポジトリを確認してください。

---

# CSVPP-AI連携 (C++コード生成)
- [CSVPP AI連携仕様書 Ver.1.0](https://github.com/sky-seeker99/csvpp/blob/main/ChatGPT/cpp_gen/CSVPP_AI_Integration_Spec_v1.0.md)
- [CSVPP AI連携仕様書 Ver.2.0](https://github.com/sky-seeker99/csvpp/blob/main/ChatGPT/cpp_gen/CSVPP_AI_Integration_Spec_v2.0.md) 
- [CSVPP C/C++コード生成命令リファレンス](https://github.com/sky-seeker99/csvpp/blob/main/ChatGPT/cpp_gen/CSVPP_CPP_Command_Reference_AI.md) 
- [CSVPP AI連携：独自メソッド追加のExcel生成ルール](https://github.com/sky-seeker99/csvpp/blob/main/ChatGPT/cpp_gen/CSVPP_AI_Custom_Method_Rules_v3_draft.md) 
- [CSVPP AI連携仕様書 Ver.3.0](https://github.com/sky-seeker99/csvpp/blob/main/ChatGPT/cpp_gen/CSVPP_AI_Integration_Spec_v3.0.md) 
- [CSVPP AI連携仕様書 Ver.3.1](https://github.com/sky-seeker99/csvpp/blob/main/ChatGPT/cpp_gen/CSVPP_AI_Integration_Spec_v3.1.md) 

- 使用したExcelファイル
  - [Employee.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/cpp_gen/Employee.xlsx)
  - [AddressBook.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/cpp_gen/AddressBook.xlsx)
  - [Product.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/cpp_gen/Product.xlsx)
  - [Product_Customer_Order_csvpp.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/cpp_gen/Product_Customer_Order_csvpp.xlsx)
  - [BankAccount_csvpp.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/cpp_gen/BankAccount_csvpp.xlsx)

- 生成したC++コードファイル
  - [Employee.cpp](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/cpp_gen/Employee.cpp)
  - [Employee.h](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/cpp_gen/Employee.h)
  - [AddressBook.cpp](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/cpp_gen/AddressBook.cpp)
  - [AddressBook.h](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/cpp_gen/AddressBook.h)
  - [Product.cpp](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/cpp_gen/Product.cpp)
  - [Product.h](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/cpp_gen/Product.h)
  - [BankAccount.cpp](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/cpp_gen/BankAccount.cpp)
  - [BankAccount.h](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/cpp_gen/BankAccount.h)

---

# CSVPP-AI連携 (Verilog-RTL/Testbenchi生成)
- [CSVPP Verilog RTL生成 AI連携仕様書 Ver.1.0](https://github.com/sky-seeker99/csvpp/blob/main/ChatGPT/verilog_gen/CSVPP_Verilog_RTL_AI_Integration_Spec_Ver1.0.md)
- [CSVPP Verilog RTL・テストベンチ・TOP統合 AI連携仕様書 Ver.2.0](https://github.com/sky-seeker99/csvpp/blob/main/ChatGPT/verilog_gen/CSVPP_Verilog_RTL_Testbench_TOP_AI_Integration_Spec_Ver2.0.md)

- 使用したExcelファイル
  - [csvveri_rtl.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_gen/csvveri_rtl.xlsx)
  - [csvveri_test.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_gen/csvveri_test.xlsx)
  - [csvveri_top.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_gen/csvveri_top.xlsx)

- 生成したVerilogコードファイル
  - [model.v](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_gen/model.v)
  - [top.v](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_gen/top.v)
  - [test.v](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_gen/test.v)
  - [cover.v](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_gen/cover.v)
  - [clk.v](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_gen/clk.v)

# CSVPP-AI連携 (Verilog-検証用CPU生成)
- [CSVPP Verilog検証用CPU生成・シミュレーション環境 AI連携仕様書](https://github.com/sky-seeker99/csvpp/blob/main/ChatGPT/verilog_cpu_gen/CSVPP_Verilog_CPU_AI_Integration_Spec_v1.1.md)

- 使用したExcelファイル(AI修正版)
  - [cpu_memtest_maker_fixed.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_cpu_gen/cpu_memtest_maker_fixed.xlsx)
  - [cpu_maker_2_sample_verilog_fixed.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_cpu_gen/cpu_maker_2_sample_verilog_fixed.xlsx)
 
- 生成したVerilogコードファイル
  - [cpu_memtest.v](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_cpu_gen/cpu_memtest.v)
  - [cpu_memtest.cod](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_cpu_gen/cpu_memtest.cod)
  - [cpu_memtest_lst.csv](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_cpu_gen/cpu_memtest_lst.csv)
  - [top.v](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_cpu_gen/top.v)
  - [target.v](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_cpu_gen/target.v)
  - [rst.v](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_cpu_gen/rst.v)
  - [clk.v](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_cpu_gen/clk.v)

- バッチファイル
  - [sim_go.sh](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_cpu_gen/sim_go.sh)
  - [verilog.lst.txt](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_cpu_gen/verilog.lst.txt)

# CSVPP-C++表形式設計言語仕様
- [CSVPP-C++ 表形式設計言語仕様書 Ver.0.1](https://github.com/sky-seeker99/csvpp/blob/main/ChatGPT/csvpp-c++/CSVPP-Cpp_Table_Design_Language_Spec_Ver0.1.md)
- [CSVPP-C++ 表形式設計言語仕様書 Ver.1.0](https://github.com/sky-seeker99/csvpp/blob/main/ChatGPT/csvpp-c++/CSVPP_CPP_Table_Design_Language_Spec_Ver1.0.md)

- AIが生成したCSVPP言語のExcelファイル
  - [Product_Design_CSVPP.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP.xlsx)
  - [Product_Design_Ver0.1.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_Ver0.1.xlsx)
  - [Product_Design_CSVPP_Ver0.2.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP_Ver0.2.xlsx)
  - [Product_Design_CSVPP_Ver0.3.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP_Ver0.3.xlsx)
  - [Product_Design_CSVPP_Ver0.4.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP_Ver0.4.xlsx)
  - [Product_Design_CSVPP_Ver0.5.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP_Ver0.5.xlsx)
  - [Product_Design_CSVPP_Ver0.6.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP_Ver0.6.xlsx)
  - [Product_Design_CSVPP_Ver0.7.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP_Ver0.7.xlsx)
  - [Product_Design_CSVPP_Ver0.8.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP_Ver0.8.xlsx)
  - [Product_Design_CSVPP_Ver0.9.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP_Ver0.9.xlsx)
  - [Product_Design_CSVPP_Ver1.0.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP_Ver1.0.xlsx)

- 生成したC++コードファイル
  - [DesignProduct.h](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/DesignProduct.h)
  - [DesignProduct.cpp](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/DesignProduct.cpp)



