object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'ConsoleOutputGet'
  ClientHeight = 562
  ClientWidth = 535
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 535
    Height = 39
    Align = alTop
    TabOrder = 0
    object Button1: TButton
      Left = 8
      Top = 6
      Width = 51
      Height = 27
      Caption = 'Clear'
      TabOrder = 0
      OnClick = Button1Click
    end
    object Font: TButton
      Left = 70
      Top = 6
      Width = 55
      Height = 27
      Caption = 'Font'
      TabOrder = 1
      OnClick = FontClick
    end
    object Backcolor: TButton
      Left = 138
      Top = 6
      Width = 55
      Height = 27
      Caption = 'Backcolor'
      TabOrder = 2
      OnClick = BackcolorClick
    end
    object Button2: TButton
      Left = 206
      Top = 6
      Width = 65
      Height = 27
      Caption = 'FileSave'
      TabOrder = 3
      OnClick = Button2Click
    end
    object clrFlg: TCheckBox
      Left = 306
      Top = 10
      Width = 93
      Height = 17
      Caption = #27598#22238#12463#12522#12450
      TabOrder = 4
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 39
    Width = 535
    Height = 523
    Align = alClient
    TabOrder = 1
    object memo: TMemo
      Left = 1
      Top = 1
      Width = 533
      Height = 521
      Align = alClient
      Font.Charset = SHIFTJIS_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #65325#65331' '#12468#12471#12483#12463
      Font.Style = [fsBold]
      ParentFont = False
      ScrollBars = ssBoth
      TabOrder = 0
    end
  end
  object font_diag: TFontDialog
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    Left = 294
    Top = 62
  end
  object color_diag: TColorDialog
    Left = 384
    Top = 54
  end
  object save_di: TSaveDialog
    DefaultExt = 'txt'
    FileName = 'console_log'
    Filter = #12486#12461#12473#12488#12501#12449#12452#12523'|*.txt'
    Title = #12525#12464#12501#12449#12452#12523#20445#23384
    Left = 238
    Top = 108
  end
end
