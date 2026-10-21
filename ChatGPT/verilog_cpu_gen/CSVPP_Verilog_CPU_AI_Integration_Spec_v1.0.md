# CSVPP Verilog検証用CPU生成・シミュレーション環境 AI連携仕様書

**Version 1.0 — 2026-10-21**  
**対象:** CSVPP / CSV-CPU Maker II / CSV-Compiler II / CSV-Verilog Maker II  
**検証段階:** CPU生成・コンパイル成功。Verilogシミュレーションによる機能確認は未実施。

## 1. 目的と適用範囲
自然言語で指定された検証要求を、CSVPP用Excelブックに落とし込み、検証用CPUのVerilog RTLと実行コード、およびシミュレーション環境を生成する。第一の基準例は、**16ビットアドレス・8ビットデータバスの全アドレス書き込み／読み戻し比較**とする。

本書は、提供された入力ブック、生成された `cpu_memtest.v`・`cpu_memtest.cod`・`cpu_memtest_lst.csv` およびシミュレーション環境用ブックを対象とする。生成済みのシミュレーション環境Verilog一式やシミュレーションログは未受領のため、環境生成成功・テスト完走を主張しない。

## 2. ファイル構成と役割

| ファイル | 役割 | 状態 |
|---|---|---|
| `CSVPP_Verilog_CPU_Generation.xlsx` | CSVPPのCPU生成言語・操作に関するマニュアル | 参照資料 |
| `cpu_maker_2.xlsx` | CPU生成の元となるサンプルExcel | 受領 |
| `cpu.v`, `cpu.cod` | 元サンプルの生成結果 | 受領 |
| `cpu_memtest_maker.xlsx` | AIが編集したメモリテスト用CPU生成Excel | CSVPPで実行済み |
| `cpu_memtest.v` | 生成されたCPU Verilogモジュール | 受領・静的確認 |
| `cpu_memtest.cod` | CPU命令コード | 受領・静的確認 |
| `cpu_memtest_lst.csv` | コンパイル命令リスト | 受領・静的確認 |
| `cpu_maker_2_sample_verilog(1).xlsx` | CPUシミュレーション環境生成用Excel | 受領・構成確認 |

## 3. 全体の生成フロー

```text
自然言語の検証要求
      |
      v
AIによる仕様整理（バス幅・アドレス範囲・パターン・判定）
      |
      +--> cpu_memtest_maker.xlsx
      |         |
      |       CSVPP / CSV-CPU Maker II・CSV-Compiler II
      |         +--> cpu_memtest.v
      |         +--> cpu_memtest.cod
      |         +--> cpu_memtest_lst.csv
      |
      +--> cpu_maker_2_sample_verilog(1).xlsx
                |
              CSVPP / CSV-Verilog Maker II
                +--> top/clk/rst/target/dump等のVerilog（生成予定）

Verilogシミュレータ + 全生成物 + cpu_memtest.cod
      |
      v
バスアクセス・データ比較・PASS/FAIL・波形の確認
```

## 4. CPU生成ブックの構成

`cpu_memtest_maker.xlsx` のシート:

| シート | 主な用途 | AI編集方針 |
|---|---|---|
| `ReadmeDoc` | 説明 | 原則保持 |
| `cmd` | 生成設定・モジュール名 | 必要な設定のみ変更 |
| `code` | テストプログラム・関数 | テスト要件に応じて編集 |
| `interface` | CPUと外部バスの接続処理 | プロトコルに合わせて慎重に変更 |
| `macro` | マクロ・定義 | 必要時に編集 |
| `cpu_C` | CPU生成クラス | 原則保持 |

**AI編集の原則:** 既存のCPU生成クラスや、検証済みのインターフェース実装を不用意に再生成しない。`code` の主処理を中心に変更し、必要な場合のみ `cmd`・`interface`・`macro` を変更する。Excelのセル位置・インデント・コマンドの引数配置を維持する。

## 5. CPUのVerilogインターフェース

実際の `cpu_memtest.v` にある `module cpu_memtest` のポート:

| ポート | 方向 | 幅 | 用途 |
|---|---|---:|---|
| `clk` | input | 1 | クロック |
| `clko` | input | 1 | クロック |
| `rst` | input | 1 | リセット |
| `irq` | input | 4 | 割り込み入力 |
| `dtin` | input | 8 | 読み出しデータ |
| `ack` | input | 1 | 応答信号 |
| `irq_clear` | output | 4 | 割り込みクリア |
| `cs` | output | 1 | チップ選択 |
| `we` | output | 1 | 書き込み制御 |
| `adr` | output | 16 | アドレス |
| `dtout` | output | 8 | 書き込みデータ |

`cs`・`we`・`ack` の有効レベル、各信号の更新・サンプリングタイミングは、`interface` の実装と生成された `target` の動作を照合して確定する。名称だけで決めつけない。

## 6. メモリテストの仕様

| 項目 | 値 |
|---|---|
| アドレス範囲 | `0x0000` ～ `0xFFFF` |
| アドレス数 | 65,536 |
| データ幅 | 8ビット |
| 書き込み値 | `address % 256`（アドレス下位8ビット） |
| フェーズ1 | 全アドレスに期待値を書き込む |
| フェーズ2 | 全アドレスから読み戻し、期待値と比較する |
| 不一致時 | アドレス・実測値・期待値を表示し `Result - NG` |
| 一致完了時 | `Result - Good` |

### 6.1 CSV-Compiler IIの主要記述

今回の生成入力とコンパイルリストで確認された主要構文:

```text
#st,main
#local,i,int
#local,dt,int
#local,expected,int
#for,i,65536
  #do,write,i,i % 256
#endfor
#for,i,65536
  #do,read,i,@dt
  #if,(i % 256) != dt
    #printf,data unmatch (addr = %x read = %x expect = %x),i,dt,i % 256
    #printf,Result - NG
    #user,$K_finish$
  #endif
#endfor
#printf,Result - Good
#user,$K_finish$
```

上記は**構文の説明用抜粋**であり、Excelのセル配置まで再現したものではない。実際の生成には元ブックのセル構造、`read`/`write` サブルーチン、マクロ、インターフェース定義が必要。

### 6.2 アドレス端点とループ

`#for,i,65536` はコンパイルされている。ただし、シミュレーションで `0xFFFF` までアクセスしたか、最終アドレスから次の値への境界処理が正しいかは波形またはログで検証する。

### 6.3 テストの限界

`address % 256` は、アドレス上位8ビットが異なっても同じデータになる。このパターンだけではアドレス線の短絡・ミラーリング等の一部故障を見逃す可能性がある。基本試験完了後、反転データ、固定パターン、ウォーキング1/0、アドレス依存の複数パターンを追加検討する。

## 7. 生成コード・リストとの対応

- `cpu_memtest.v` は `module cpu_memtest` を定義する。
- 命令領域は `reg [191:0] prg_area [114:0];` と宣言され、**1命令192ビット**の構造を持つ。
- `cpu_memtest.cod` は `@00000000` のようなアドレス指定と、32ビット×6フィールドの16進データで構成される。
- `cpu_memtest.v` には `$readmemh("cpu_memtest.cod",prg_area);` があり、シミュレーション時に命令コードファイルを読み込む。
- `cpu_memtest_lst.csv` のヘッダーには `register area=14`、`program area=109`、`start address=0`、`global area=1`、`irq function number=0` と記載されている。これらの**リスト上の使用量**とVerilog配列の**宣言上限**は混同しない。
- リストには `main`（86命令）と `read`（11命令）などの関数情報、`#for`、`#do`、`#printf`、`#user` への展開が記録されている。
- `Result - Good`、`Result - NG` および不一致メッセージは生成Verilogの表示処理にも存在する。

## 8. シミュレーション環境生成ブック

`cpu_maker_2_sample_verilog(1).xlsx` は以下の7シートからなる。

| シート | 役割 |
|---|---|
| `cmd` | Verilog生成の指示 |
| `top` | トップ階層・モジュール間接続 |
| `dump` | 波形出力設定 |
| `rst` | リセット生成 |
| `clk` | クロック生成 |
| `target` | CPUのアクセス対象モデル |
| `csvveri_C` | CSV-Verilog生成クラス |

**重要:** `target` が65536×8ビットRAMを実装しているか、読み出しデータが `dtin` に返されるか、`ack` が適切なタイミングで返るかは、生成されたVerilogで確認する。未確認のままRAMとして動作すると扱わない。

## 9. シミュレーション時の確認項目

1. `cpu_memtest.v` と `cpu_memtest.cod` を同一実行環境で参照できること（`$readmemh` の相対パスに注意）。
2. `top` で `clk`・`clko`・`rst` とバス信号が正しく結線されていること。
3. `target` に65536×8ビット相当の保存領域があること。
4. `cs`、`we`、`ack` の極性とハンドシェイクが一致すること。
5. 書き込みが65536回、読み出しが65536回、想定アドレスで実施されること。
6. `0x0000`、`0x00FF`、`0x0100`、`0xFFFF` でデータが正しいこと。
7. 全件一致で `Result - Good` が出ること。
8. 意図的な1ビット化けを注入したとき `Result - NG` と不一致情報が出ること。
9. ハングアップ・無応答を検出できるタイムアウトをテストベンチに設けること。
10. 波形ダンプと実行ログを保存し、結果を再現できること。

## 10. AI自動生成の入出力契約（提案）

**入力:** アドレス幅、データ幅、アクセス対象の接続仕様、テスト範囲、データパターン、比較方針、エラー時動作、クロック・リセット条件。

**出力:** CPU生成用Excel、必要なら環境生成用Excel、生成後のVerilogと命令コード、命令リスト、実行手順、検証チェックリスト。

**禁止事項:** 未確認のCSVPP命令・シート構造を推測で確定仕様とすること、コンパイル成功をシミュレーション成功と表現すること、`cpu_C` / `csvveri_C` を根拠なく改変すること。

**推奨検証ゲート:** (A) Excel構造検査 → (B) CSVPP変換エラー0件 → (C) 生成Verilogの構文検査 → (D) テストベンチ接続検査 → (E) シミュレーションPASS/FAIL注入試験 → (F) 再現性確認。

## 11. 現在の達成状況と残課題

| 工程 | 状況 |
|---|---|
| 自然言語からメモリテスト用Excel作成 | 完了 |
| CSVPPによるCPU Verilog・命令コード生成 | **ユーザーよりエラーなしと報告、成果物受領** |
| コンパイルリスト受領・静的確認 | 完了 |
| シミュレーション環境用Excelの受領 | 完了 |
| 環境用Verilogの生成結果確認 | 未実施 |
| 65536アドレスのシミュレーション完走 | 未実施 |
| 正常系PASS・故障注入FAILの確認 | 未実施 |

## 12. 次に必要な成果物

CSVPPで `cpu_maker_2_sample_verilog(1).xlsx` から生成した `top.v`、`target.v`、`clk.v`、`rst.v`、`dump.v` 等の**実際に生成されたファイル一式**と、可能ならシミュレーションログ・波形情報。ファイル名は生成結果に従い、固定と決めつけない。

これらを照合し、接続の整合性とテスト完走を確認した段階で、本仕様書を「シミュレーション検証済み」版に更新する。

---

**位置付け:** 本書は、提供サンプルに基づくAI連携の統合仕様と検証計画であり、未実施のシミュレーション結果を含まない。
