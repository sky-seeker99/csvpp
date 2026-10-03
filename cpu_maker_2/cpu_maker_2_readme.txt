=========================================================================
【  ソフト名  】CSV-CPU Maker II (Verilog版) 
【 ファイル名 】cpu_makerII.lzh
【  著作権者  】S.Kasuya
【  動作環境  】Windows95/NT4.0以上,
【  必要 APP  】Microsoft Excel 97以上
                CSVプリプロセッサ言語システム Ver1.03c以降
                CSV-Verilog MakerII 
                CSV-Compiler II Ver0.90以降
【  開発言語  】CSVプリプロセッサ言語
【 ソフト種別 】フリーウェア
【   連絡先   】http://8230.teacup.com/spbc11/mbox
【ウェブページ】http://csvpp.sourceforge.jp/pukiwiki/
【  転載条件  】作者に連絡すれば可
==========================================================================
【ソフトの紹介】
CSV-CPU Maker II (Verilog版)  はテストベンチ用ＣＰＵを自動生成するプログラムです。
また、ソースコードもコンパイルし、Ｖｅｒｉｌｏｇで自動実行できるパターンを生成します。

【使用方法】
CSVプリプロセッサ言語システムを使ってVerilogファイルを自動生成します。
具体的な方法は、Ｅｘｃｅｌを右クリックでセレクトして、メニューが出た所で、「送る」を選びます。
すると、子供のメニューがでますのて、そこで、「ｃｓｖ」を選択します。
選択したら、左クリックを押して実行です。
実行すると、ＤＯＳ画面が開き、Verilogファイルを作成します。

【ファイル】
cpu_maker_2.xls                :CSV-CPU Maker II (Verilog版)本体。このファイルを書き換えて使用します。
cpu_maker_2_readme.txt         :本ドキュメントファイル
cpu_maker_2_sample_code.xls    :サンプルコード。
cpu_maker_2_sample_verilog.xls :cpu_maker_2.xlsに対するサンプルVerilogファイル。変換するとVerilogファイルが出来ます。

【試しに使用してみる】
cpu_maker_2.xlsファイルをCSVプリプロセッサで変換すると以下のファイルが出来ます。
・cpu_for_testbench.v　　　　　:CPUのVerilogファイル
・cpu_for_testbench.cod        :CPUの命令コード
・cpu_for_testbench_lst.csv    :命令コードのリストファイル

cpu_maker_2_sample_verilog.xlsファイルをCSVプリプロセッサで変換すると以下のファイルが出来ます。
・top.v　　　:モジュール間接続トップファイル
・target.v   :ターゲットファイル
・rst.v      :リセット生成
・clk.v      :クロック生成

上記のVerilogを実行すると、CSV-CPU Maker IIで作ったCPUが動作します。
波形ファイル(cpu_test.dump)もダンプしますので、どの様な動作をするか確認して下さい。


【履歴】
Ver 1.00  初公開！
Ver 1.01  interface用タスク、ファンクションの追加 
Ver 1.02  variable_write_area_getの修正
Ver 1.03  スタックオーバーフローのチェックを追加、コードファイルとＶｅｒｉｌｏｇファイルの組み合わせチェック機能追加
(「cmd」シートにcpu_make_endのコールを追加、「interface」シートにprogram_load;している所を削除しているので注意）
Ver 1.04  割り込みルーチンから抜けるときのバグを修正
Ver 1.05  ビット幅を変更できる。



