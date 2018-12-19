object MvtAniFrm: TMvtAniFrm
  Left = 752
  Top = 347
  BorderStyle = bsSingle
  ClientHeight = 240
  ClientWidth = 140
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  OnActivate = FormActivate
  OnCreate = FormCreate
  OnKeyPress = FormKeyPress
  PixelsPerInch = 96
  TextHeight = 13
  object LabNom: TLabel
    Left = 0
    Top = 0
    Width = 3
    Height = 13
  end
  object LabDest: TLabel
    Left = 86
    Top = 152
    Width = 16
    Height = 15
    Caption = 'è'
    Font.Charset = SYMBOL_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Wingdings'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabOrig: TLabel
    Left = 88
    Top = 128
    Width = 16
    Height = 15
    Caption = 'ç'
    Font.Charset = SYMBOL_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Wingdings'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Grille: TStringGrid
    Left = 0
    Top = 24
    Width = 89
    Height = 180
    ColCount = 2
    DefaultColWidth = 40
    RowCount = 7
    FixedRows = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goAlwaysShowEditor]
    TabOrder = 0
    OnClick = GrilleClick
    OnSelectCell = GrilleSelectCell
    RowHeights = (
      24
      24
      24
      24
      24
      24
      24)
  end
  object BtBnOK: TBitBtn
    Left = 32
    Top = 208
    Width = 49
    Height = 25
    TabOrder = 1
    OnClick = BtBnOKClick
    Kind = bkOK
  end
  object MEdOrig: TMaskEdit
    Left = 104
    Top = 128
    Width = 25
    Height = 21
    EditMask = '99;1;_'
    MaxLength = 2
    TabOrder = 2
    Text = '  '
  end
  object MEdDest: TMaskEdit
    Left = 104
    Top = 152
    Width = 25
    Height = 21
    EditMask = '99;1;_'
    MaxLength = 2
    TabOrder = 3
    Text = '  '
  end
end
