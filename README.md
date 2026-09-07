# CSVPP
 Excelで作ったデータや仕様から、プログラム・スクリプト・各種ファイルを自動生成するWindows向けコード生成システム。
 CSVPP（CSV-Preprocessor system）は、Excelを「コード生成のための入力・定義環境」として利用するインタプリタ型の言語生成システムです。
 Excelにデータや処理内容を記述すると、その定義に従ってC/C++などのプログラム、スクリプト、バッチファイル、Verilog-HDLなどを生成できます。

## こんなことができます
- Excelで作成した仕様からソースコードを自動生成
- 大量の定型コードを自動生成
- Excelのデータをプログラムや各種テキスト形式へ変換
- C/C++ソースコードを生成
- Verilog-HDLを生成
- CSVの加工・比較・結合・変換
- 仕様書・データ・生成コードを一連の流れで管理

### 「Excelで仕様を書く → CSVPPで処理する → ソースコードを生成する」
 という使い方ができます。

## なぜCSVPP？
### 通常、仕様書とプログラムは別々に管理されます。
<pre>
仕様書（Excel）
     ↓
人間が内容を確認
     ↓
プログラムを手作業で作成
     ↓
仕様変更
     ↓
プログラムを修正
</pre>

### CSVPPでは、この作業を自動化できます。
<pre>
Excelで仕様・データを作成
      ↓
    CSVPP
      ↓
ソースコードを生成
</pre>

 Excelを使って仕様とデータを管理し、その内容から必要なコードを生成することで、コピー＆ペーストや定型コードの手作業を減らすことができます。

### 特にこんな用途に
- 組み込み・C/C++開発
 大量の定型的なC/C++コードやデータ定義を、Excelから自動生成できます。

- FPGA / Verilog-HDL
 Excelで管理しているデータや仕様から、Verilog-HDLの記述を生成できます。

- データ処理
 CSVの加工、比較、結合、変換など、開発時によく発生するデータ処理にも利用できます。

- 仕様書からのコード生成
 Excelで作成した仕様を、そのままコード生成の入力として利用できます。

### 動作環境
- Windows 10 / 11
- Microsoft Excel

## ダウンロード
 最新版の csvpp_system_*.zip をダウンロードしてください。
 最新版をダウンロード
 ダウンロード後、ZIPファイルを展開して使用してください。
 ※ Microsoft Excelが必要です。

## まず試してみる
 サンプルプログラムを使って、CSVPPの動作を確認できます。

- filelist.xls — サンプル
- CSVPP設定と使い方
- CSVPP言語マニュアル
- CSVPP言語リファレンス
- テキストファイル生成と加工
- Verilog-HDL生成

 詳しい使い方は マニュアル を参照してください。

## 主なツール
 CSVPPには、コード生成だけでなく、CSV・テキストデータを扱うための複数のツールが含まれています。
 | ツール         | 概要             |
 | ----------- | -------------- |
 | `csvcut`    | CSVデータの抽出・加工   |
 | `csvdiff`   | CSVデータの比較      |
 | `csvmerge`  | CSVデータの結合      |
 | `csvxml`    | CSV / XML関連の変換 |
 | `csvveri`   | Verilog-HDL関連  |
 | `csvmake`   | コード生成・ビルド関連    |

## 特徴
- Excelベースの言語定義
 テキストエディタだけでなく、Excelのセルを利用してデータや処理内容を構造化して記述できます。
- 仕様・データ・コード生成を一つにつなげる
 Excelで仕様やデータを作成し、その内容をCSVPPで処理してコードを生成できます。
- 定型コードを自動生成
 繰り返し作成する必要のあるコードやテキストを自動生成することで、手作業を減らせます。
- 拡張可能
 CSVPPにはC/C++ソース生成などのためのクラスライブラリも含まれています。

## ライセンス
 プログラム及び、ドキュメントは GNU General Public License version 2.0 のライセンスに従います。

## Author
 sky-seeker99

## マニュアル
* [CSVPP設定と使い方](https://github.com/user-attachments/files/31350199/CSVPP_Setup_and_Usage.xlsx) ... 2026.8.24
* [CSVPP言語マニュアル](https://github.com/user-attachments/files/31342409/CSVPP_LanguageManual.xlsx) ... 2026.8.23
* [CSVPP言語リファレンス](https://github.com/user-attachments/files/31342410/CSVPP_LanguageReferenceGuide.xlsx) ... 2026.8.23
* [テキストファイル生成と加工](https://github.com/user-attachments/files/31473250/CSVPP_TextFile_Generation_and_Processing.xlsx) ... 2026.8.26
* [Verilog-HDL生成](https://github.com/user-attachments/files/31876291/CSVPP_Verilog_Generation.xlsx) ... 2026.9.6

## プログラム本体 [csvpp_system_177a.zip]
* [2026.9.6](https://github.com/user-attachments/files/31876312/csvpp_system_177a.zip)
* [2026.8.26](https://github.com/user-attachments/files/31473193/csvpp_system_177a.zip)
* [2026.8.23](https://github.com/user-attachments/files/31342405/csvpp_system_177a.zip) 
 
## サンプルプログラム
* [filelist.xls](https://github.com/user-attachments/files/31473311/filelist.xls)

## クラスライブラリ
* [C/C++ソース生成クラス](https://github.com/user-attachments/files/31517968/cpp_maker_core.xlsx) ... 2026.8.27



