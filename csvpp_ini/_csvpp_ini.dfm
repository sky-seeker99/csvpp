object Form1: TForm1
  Left = 430
  Top = 275
  Width = 940
  Height = 713
  Caption = 'CSVPP初期設定プログラム Ver 1.11'
  Color = clBtnFace
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'ＭＳ Ｐゴシック'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 12
  object Splitter1: TSplitter
    Left = 0
    Top = 153
    Width = 924
    Height = 9
    Cursor = crVSplit
    Align = alTop
  end
  object Splitter2: TSplitter
    Left = 0
    Top = 621
    Width = 924
    Height = 8
    Cursor = crVSplit
    Align = alBottom
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 924
    Height = 153
    Align = alTop
    TabOrder = 0
    object batFile: TMemo
      Left = 1
      Top = 1
      Width = 922
      Height = 151
      Align = alClient
      Font.Charset = SHIFTJIS_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'ＭＳ ゴシック'
      Font.Style = []
      ParentFont = False
      ScrollBars = ssBoth
      TabOrder = 0
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 629
    Width = 924
    Height = 45
    Align = alBottom
    TabOrder = 1
    object Button1: TButton
      Left = 16
      Top = 8
      Width = 113
      Height = 33
      Caption = '更新'
      TabOrder = 0
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 136
      Top = 8
      Width = 113
      Height = 33
      Caption = '更新して終了'
      TabOrder = 1
      OnClick = Button2Click
    end
    object Button3: TButton
      Left = 256
      Top = 8
      Width = 113
      Height = 33
      Caption = '更新せずに終了'
      TabOrder = 2
      OnClick = Button3Click
    end
  end
  object panel: TPanel
    Left = 0
    Top = 162
    Width = 924
    Height = 459
    Align = alClient
    TabOrder = 2
    object Label1: TLabel
      Left = 8
      Top = 8
      Width = 63
      Height = 12
      Caption = '作業ドライブ'
    end
    object Label2: TLabel
      Left = 136
      Top = 8
      Width = 81
      Height = 12
      Caption = '作業ディレクトリ'
    end
    object Label3: TLabel
      Left = 400
      Top = 8
      Width = 218
      Height = 12
      Caption = '※ディレクトリ階層は一階層にしてください。'
    end
    object Label4: TLabel
      Left = 8
      Top = 112
      Width = 74
      Height = 12
      Caption = 'ログファイル名'
    end
    object Label5: TLabel
      Left = 8
      Top = 168
      Width = 84
      Height = 12
      Caption = 'csvmakeフィルタ'
    end
    object Label6: TLabel
      Left = 432
      Top = 168
      Width = 120
      Height = 12
      Caption = 'csvmakeフィルタ拡張子'
    end
    object Label7: TLabel
      Left = 8
      Top = 192
      Width = 255
      Height = 12
      Caption = '擬似環境変数(CSVPPのみで使用できる環境変数)'
    end
    object Label8: TLabel
      Left = 8
      Top = 312
      Width = 120
      Height = 12
      Caption = 'インクルードサーチパス'
    end
    object WorkDrv: TComboBox
      Left = 80
      Top = 8
      Width = 49
      Height = 20
      ItemHeight = 12
      TabOrder = 0
      Text = 'c'
      OnChange = WorkDrvChange
      Items.Strings = (
        'a'
        'b'
        'c'
        'd'
        'e'
        'f'
        'g'
        'h'
        'i'
        'j'
        'k'
        'l'
        'm'
        'n'
        'o'
        'p'
        'q'
        'r'
        's'
        't'
        'u'
        'v'
        'w'
        'x'
        'y'
        'z')
    end
    object WorkDir: TEdit
      Left = 224
      Top = 8
      Width = 161
      Height = 20
      TabOrder = 1
      Text = 'csv'
      OnChange = WorkDirChange
    end
    object stpp: TCheckBox
      Left = 8
      Top = 32
      Width = 209
      Height = 25
      Caption = 'バッチ終了後一時停止あり?'
      Checked = True
      State = cbChecked
      TabOrder = 2
      OnClick = stppClick
    end
    object csvmake_o_p: TCheckBox
      Left = 240
      Top = 32
      Width = 177
      Height = 25
      Caption = 'OpenOffice.org版を使用する'
      TabOrder = 3
      OnClick = csvmake_o_pClick
    end
    object csvfront: TCheckBox
      Left = 8
      Top = 56
      Width = 225
      Height = 25
      Caption = 'CSVPPフロントエンドプログラムあり?'
      Checked = True
      State = cbChecked
      TabOrder = 4
      OnClick = csvfrontClick
    end
    object proc: TCheckBox
      Left = 240
      Top = 56
      Width = 217
      Height = 25
      Caption = 'プロセスが残ってしまうExcelを削除'
      Checked = True
      State = cbChecked
      TabOrder = 5
      OnClick = procClick
    end
    object tmp: TCheckBox
      Left = 464
      Top = 56
      Width = 209
      Height = 25
      Caption = 'CSV展開時、一旦テンポラリに退避'
      TabOrder = 6
      OnClick = tmpClick
    end
    object log: TCheckBox
      Left = 8
      Top = 80
      Width = 137
      Height = 25
      Caption = 'ログを作成する?'
      TabOrder = 7
      OnClick = logClick
    end
    object pipe: TCheckBox
      Left = 240
      Top = 80
      Width = 217
      Height = 25
      Caption = 'パイプ処理でログを作成する?'
      TabOrder = 8
      OnClick = pipeClick
    end
    object logWin: TCheckBox
      Left = 464
      Top = 80
      Width = 433
      Height = 25
      Caption = 'コンソールを使用する?'
      Checked = True
      State = cbChecked
      TabOrder = 9
      OnClick = logWinClick
    end
    object logFile: TEdit
      Left = 88
      Top = 112
      Width = 393
      Height = 20
      TabOrder = 10
      Text = 'c:\log.txt'
      OnChange = logFileChange
    end
    object sp_push_flg: TCheckBox
      Left = 8
      Top = 136
      Width = 233
      Height = 25
      Caption = '両端の半角スペースを削除しない'
      Checked = True
      State = cbChecked
      TabOrder = 11
      OnClick = sp_push_flgClick
    end
    object filter_prg: TEdit
      Left = 104
      Top = 168
      Width = 305
      Height = 20
      TabOrder = 12
      OnChange = filter_prgChange
    end
    object filter_ext: TEdit
      Left = 560
      Top = 168
      Width = 57
      Height = 20
      TabOrder = 13
      OnChange = filter_extChange
    end
    object env_list: TMemo
      Left = 8
      Top = 208
      Width = 913
      Height = 97
      Font.Charset = SHIFTJIS_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'ＭＳ ゴシック'
      Font.Style = []
      ParentFont = False
      ScrollBars = ssBoth
      TabOrder = 14
      OnChange = env_listChange
    end
    object inc_list: TMemo
      Left = 8
      Top = 328
      Width = 913
      Height = 105
      Font.Charset = SHIFTJIS_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'ＭＳ ゴシック'
      Font.Style = []
      ParentFont = False
      ScrollBars = ssBoth
      TabOrder = 15
      OnChange = inc_listChange
    end
  end
  object tim: TTimer
    Enabled = False
    Interval = 10
    OnTimer = timTimer
    Left = 856
    Top = 186
  end
end
