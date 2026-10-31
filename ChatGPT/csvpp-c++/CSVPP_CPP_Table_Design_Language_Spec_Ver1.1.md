# CSVPP-C++ 表形式設計言語 仕様書 Ver.1.1

**作成日:** 2026年10月31日  
**対象:** CSVPP Ver.1.77 / frontend Ver.1.18 / text_create Ver.1.04  
**対象ブック:** `Product_Design_CSVPP_Ver1.9(2).xlsx`（ユーザー修正版）

本書は、ユーザー提供の修正版Excel、実行ログ、および生成されたProduct/Customerの.cpp/.hを基に、2026年10月31日時点で確認できた仕様を整理したものである。

## 1. 目的と適用範囲

本仕様書は、Excelの表形式で記述したC++設計情報をCSVPPで読み込み、既存のC++生成マクロ cpp_C と text_create を利用して、クラスごとのヘッダー(.h)および実装(.cpp)を生成する仕組みを定義する。

Ver.1.1では、従来の単一出力ファイル方式から、複数クラスをそれぞれ独立したファイルへ出力する方式へ進展した。ProductクラスとCustomerクラスについて、Product.cpp / Product.h / Customer.cpp / Customer.h の4ファイルが生成されたことを、ユーザー提供の実行ログおよび生成物で確認した。

本仕様書の対象は、2026年10月31日に実行確認された Product_Design_CSVPP_Ver1.9(2).xlsx の構成と、その実行結果である。C++コンパイルおよび実行時動作は本確認に含まれない。

## 2. 全体構成

Excelブック内の設計表をCSVとして保存し、CSVPP Ver.1.77 / csvfront frontend Ver.1.18 で処理する。CSVPPのusr_Cマクロが各クラスの設計表を読み取り、cpp_Cの既存マクロへ変換する。クラス単位で中間入力ファイルを作成し、text_create Ver.1.04 が対応する .cpp と .h を出力する。

## 3. 処理フロー

1) cmd.csv、cpp_C.csv、usr_C.csvを読み込む。

2) cmdから #DESIGN_READ_CLASS を呼び出し、Class.csvを走査する。

3) Class.csvの各クラス行について、クラス名を含む専用中間ファイルを開く。実行例では ProductZ.csv、CustomerZ.csv。

4) #file_def にクラス名を設定し、#header_h、#header_cpp、#class を設定・呼び出す。

5) Member.csvをClassIDで絞り込み、#kind / #member によりメンバーを登録する。

6) Method.csvをClassIDで絞り込み、#kind / #method によりメソッドを登録する。

7) Argument.csvをMethodIDで照合し、#parmで引数を登録する。

8) Behavior.csvをMethodIDで照合する。getterはMemberIDを引いてreturn文を生成し、customはCustomCode.csvから該当コード行を取得して#codeで登録する。

9) クラスの設計情報を中間ファイルへ書き終えた後、ファイルを閉じる。

- 10) text_createをクラス専用中間ファイルに対して実行し、クラス名に対応する .cpp と .h を生成する。

- 11) Class.csvの次のクラスに進み、同じ処理を繰り返す。

## 4. ExcelシートとCSVデータ

- Class: ClassID、ClassName、ClassType、Description。クラス単位処理の起点となる。

- Member: MemberID、ClassID、MemberName、Type、Access、Default。クラスのメンバー変数を定義する。

- Method: MethodID、ClassID、MethodName、ReturnType、Access、IsConst。メソッドと戻り値型を定義する。コンストラクタはReturnTypeに「.」を指定する。

- Argument: MethodID、Position、ArgumentName、Type。メソッド引数を定義する。MethodIDで対象メソッドと結び付ける。

- Behavior: MethodID、Pattern、TargetMemberID、ValueArgument、CustomCodeRef。メソッド本体の生成方法を指定する。

- CustomCode: CustomCodeRef、LineNo、CppCode。customパターンで出力するC++コードを行単位で保持する。

各CSVの先頭行は列見出しとし、読み取りマクロで見出し行を除外する。引数とコードの並び順はCSVの行順に依存するため、PositionおよびLineNoに沿って行を配置する。

## 5. Behaviorの生成規則

- getter: Behavior.TargetMemberIDをMember.csvのMemberIDと照合し、対応するMemberNameを使って「return <MemberName>;」を生成する。

- custom: Behavior.CustomCodeRefをCustomCode.csvのCustomCodeRefと照合し、一致するCppCodeを行順に#codeへ渡す。

Ver.1.1の実証データでは、Productのコンストラクタ、setter、isInStock、reduceStock、restock、およびCustomerのコンストラクタ、setEmailがcustomで定義されている。getterはProductとCustomerの各アクセサで使用されている。

コード本体は対象メソッドの処理階層内で#codeを呼び出して登録する。複数行コードはCustomCode.csvに複数行で記述する。

## 6. クラス別ファイル出力方式

複数クラス出力の要点は、クラスごとにtext_create用の中間入力を分けることである。Ver.1.9(2)のusr_Cでは、Class.csvの各クラス処理の中で、クラス名を含むファイル名を指定してshell入力ファイルを開き、当該クラスの定義を出力した後に閉じ、text_createを実行する構成が確認できる。

実行ログでは ProductZ.csv を処理した後に c:\\csv\\Product.cpp と c:\\csv\\Product.h が開かれ、続いて CustomerZ.csv の処理後に c:\\csv\\Customer.cpp と c:\\csv\\Customer.h が開かれている。

cpp_Cの既存出力機構を利用し、クラスごとの中間入力をtext_createへ渡すことで、クラス別ファイルを生成する。Ver.1.9(2)の成功版では、ユーザーがExcelを修正してこの流れを成立させた。したがって、以前のVer.1.8/初期Ver.1.9の試行時の記述と、最終成功版の実際のExcel内容を混同しないこと。

## 7. Ver.1.9(2)で確認した生成対象

Productクラス: privateメンバー id:int、name:std::string、price:double、stock:int。publicメソッドはコンストラクタ、getId、getName、getPrice、getStock、setId、setName、setPrice、setStock、isInStock、reduceStock、restockの12個。

Customerクラス: privateメンバー id:int、name:std::string、email:std::string。publicメソッドはコンストラクタ、getId、getName、getEmail、setEmailの5個。

Product.cppにはProductのコンストラクタと11メソッドの実装が出力された。Product.hには4メンバーと12メソッド宣言が出力された。

Customer.cppにはCustomerのコンストラクタと4メソッドの実装が出力された。Customer.hには3メンバーと5メソッド宣言が出力された。

## 8. 実行環境と実行例

確認環境: CSV-file preprocessor Ver.1.77、CSVPP frontend Ver.1.18、text_create Ver.1.04。

実行コマンド例: csvfront.exe c:\\csv\\cmd.csv -ic:\\csv -x<Excelブックのパス> -p -o。

設計CSVは実行環境の c:\\csv に配置する。cmd.csv、cpp_C.csv、usr_C.csvも同じ実行環境のCSVPP設定に従って用意する。

## 9. 実行結果の確認項目

ログにProductZ.csvとCustomerZ.csvそれぞれのshell入力ファイルopen / close、およびtext_create起動が記録されること。

Product.cpp / Product.h / Customer.cpp / Customer.h の4ファイルが存在し、サイズが0バイトでないこと。

各ファイルに対応するクラス名が使われ、他クラスのメンバーやメソッドが混入していないこと。

ヘッダーにメンバー宣言・メソッド宣言、実装ファイルにメソッド本体が出力されていること。

今回の確認では4ファイルの内容まで確認済み。C++コンパイル、リンク、実行テストは別途実施する。

## 10. 制約・未確認事項

関数オーバーロード（同名メソッドで引数構成が異なるもの）の生成には未対応である。既知の制約として扱う。

IsConst列のconstメソッド生成は、本版の確認対象に含まれない。

Member.Default列の初期値反映、クラス継承、テンプレート、namespace、static、const参照、ポインタ・配列、クラス間依存の自動#include、例外仕様などは本版で検証していない。

CustomCodeは任意のC++コード行を出力できるが、CSV内のカンマ・引用符・改行などのエスケープ規則は別途検証が必要。

コンパイル成功や実行時の正しさは、今回の生成ログ・生成ファイル確認だけでは保証しない。

## 11. 次の開発課題

3クラス以上で同じクラス別出力処理が成立するか確認する。

生成した複数クラスをまとめてコンパイルし、ヘッダー相互参照とincludeの扱いを確認する。

クラス間の関連・依存関係を表で定義し、必要な#includeを生成する方式を検討する。

const、初期値、static、継承、namespaceなどの設計属性を段階的に追加する。

オーバーロードを扱うため、MethodIDとメソッド名の関係、宣言・定義の識別方法を拡張する。

設計表の入力規則、ID整合性、参照切れ、重複定義を検出する検証マクロを追加する。

## 付録A. 生成ファイル一覧

c:\\csv\\Product.cpp

c:\\csv\\Product.h

c:\\csv\\Customer.cpp

c:\\csv\\Customer.h

## 付録B. バージョン履歴

Ver.0.x～Ver.1.0: Excel表から単一クラスのC++コードを生成する機能を段階的に構築。Class / Member / Method / Argument / Behavior / CustomCodeの読み取りと#codeによる本体生成を確立。

Ver.1.1（本書）: 複数クラスの設計表をClassIDで分離し、クラスごとの中間入力ファイルを経由して各クラスの.cpp/.hを個別生成。ProductとCustomerの4ファイルを実機確認。
