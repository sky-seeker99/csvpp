# CSV-Preprocessor system
## 概要		
 CSVPP は、表計算ソフトで作成したデータを基に、	
 各種プログラミング言語・スクリプト・バッチファイルへ自動変換するための	
 インタプリタ型言語生成システム です。	
 ユーザーは Excel ファイル上で処理内容を記述し、	
 CSVPP がその定義に従って目的の言語コードを生成します。	

## 特徴
### Excel ベースの言語定義
 従来のテキストエディタによるコーディングではなく、表計算ソフトを用いてコーディングします。
 * セル単位で構造化されたデータ編集が可能
 * 視覚的・直感的な言語設計ができる
 * 設計と実装の整合性が高い

### 表計算ソフトとの高い親和性	
 変換元となるデータも Excel で作成できるため、仕様作成 → データ作成 → コード生成 までを同一環境で完結できます。

### 仕様書からの自動コード生成	
 仕様書を Excel で作成した場合、その内容をそのまま 言語コードやスクリプトへ自動変換できます。
 * 仕様と実装の乖離を防止
 * コード生成の自動化による作業効率化
 * 大規模プロジェクトでの品質向上に寄与

## 動作環境		
* Microsoft Windows 10 / 11	
* Microsoft Excel	

## ライセンス
 プログラム及び、ドキュメントは GNU General Public License version 2.0 のライセンスに従います。

## マニュアル
* [CSVPP設定と使い方](https://github.com/user-attachments/files/31350199/CSVPP_Setup_and_Usage.xlsx) ... 2026.8.24
* [CSVPP言語マニュアル](https://github.com/user-attachments/files/31342409/CSVPP_LanguageManual.xlsx) ... 2026.8.23
* [CSVPP言語リファレンス](https://github.com/user-attachments/files/31342410/CSVPP_LanguageReferenceGuide.xlsx) ... 2026.8.23
* [テキストファイル生成と加工](https://github.com/user-attachments/files/31473250/CSVPP_TextFile_Generation_and_Processing.xlsx) ... 2026.8.26

## プログラム本体 [csvpp_system_177a.zip]
* [2026.8.26](https://github.com/user-attachments/files/31473193/csvpp_system_177a.zip)
* [2026.8.23](https://github.com/user-attachments/files/31342405/csvpp_system_177a.zip) 
 
## サンプルプログラム
* [filelist.xls](https://github.com/user-attachments/files/31473311/filelist.xls)




