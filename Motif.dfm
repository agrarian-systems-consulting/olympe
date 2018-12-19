object MotifFrm: TMotifFrm
  Left = 198
  Top = 114
  Width = 733
  Height = 620
  Caption = 'MotifFrm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnPaint = FormPaint
  PixelsPerInch = 96
  TextHeight = 13
  object SG: TStringGrid
    Left = 96
    Top = 24
    Width = 241
    Height = 521
    ColCount = 3
    FixedCols = 0
    RowCount = 100
    FixedRows = 0
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindow
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnDrawCell = SGDrawCell
  end
  object BtBleu: TBitBtn
    Left = 8
    Top = 344
    Width = 75
    Height = 25
    Caption = 'Bleu'
    TabOrder = 1
    OnClick = BtBleuClick
  end
  object Blanc: TBitBtn
    Left = 8
    Top = 384
    Width = 75
    Height = 25
    Caption = 'Blanc'
    TabOrder = 2
    OnClick = BlancClick
  end
  object Rouge: TBitBtn
    Left = 8
    Top = 424
    Width = 75
    Height = 25
    Caption = 'Rouge'
    TabOrder = 3
    OnClick = RougeClick
  end
  object DG: TDrawGrid
    Left = 360
    Top = 24
    Width = 225
    Height = 521
    ColCount = 3
    FixedCols = 0
    RowCount = 100
    FixedRows = 0
    TabOrder = 4
    OnDrawCell = DGDrawCell
  end
end
