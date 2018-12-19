object MvtAniFrm: TMvtAniFrm
  Left = 621
  Top = 137
  BorderStyle = bsSingle
  Caption = 'Mouvement'
  ClientHeight = 427
  ClientWidth = 280
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
  PixelsPerInch = 96
  TextHeight = 13
  object LabNom: TLabel
    Left = 0
    Top = 0
    Width = 5
    Height = 16
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabDestin: TLabel
    Left = 94
    Top = 288
    Width = 36
    Height = 13
    Caption = 'Va vers'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object LabOrig: TLabel
    Left = 96
    Top = 208
    Width = 41
    Height = 13
    Caption = 'Vient De'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object LabEntree: TLabel
    Left = 128
    Top = 160
    Width = 116
    Height = 13
    Caption = 'Entr'#233'e dans la Cat'#233'gorie'
  end
  object LabSortie: TLabel
    Left = 128
    Top = 240
    Width = 101
    Height = 13
    Caption = 'Sortie de la Cat'#233'gorie'
  end
  object LabEffEntree: TLabel
    Left = 96
    Top = 184
    Width = 33
    Height = 13
    Caption = 'Effectif'
  end
  object LabEffSortie: TLabel
    Left = 96
    Top = 264
    Width = 33
    Height = 13
    Caption = 'Effectif'
  end
  object LabEffVente: TLabel
    Left = 96
    Top = 24
    Width = 33
    Height = 13
    Caption = 'Effectif'
  end
  object LabPrixVente: TLabel
    Left = 104
    Top = 48
    Width = 17
    Height = 13
    Caption = 'Prix'
  end
  object LabVente: TLabel
    Left = 128
    Top = 0
    Width = 28
    Height = 13
    Caption = 'Vente'
  end
  object LabAchat: TLabel
    Left = 128
    Top = 80
    Width = 28
    Height = 13
    Caption = 'Achat'
  end
  object LabEffAchat: TLabel
    Left = 96
    Top = 104
    Width = 33
    Height = 13
    Caption = 'Effectif'
  end
  object LabPrixAchat: TLabel
    Left = 104
    Top = 128
    Width = 17
    Height = 13
    Caption = 'Prix'
  end
  object LabVenteModif: TLabel
    Left = 256
    Top = 0
    Width = 9
    Height = 13
    Caption = 'M'
    Color = clRed
    ParentColor = False
    Visible = False
  end
  object LabAchatModif: TLabel
    Left = 256
    Top = 80
    Width = 9
    Height = 13
    Caption = 'M'
    Color = clRed
    ParentColor = False
    Visible = False
  end
  object LabEntreeModif: TLabel
    Left = 256
    Top = 160
    Width = 9
    Height = 13
    Caption = 'M'
    Color = clRed
    ParentColor = False
    Visible = False
  end
  object LabSortieModif: TLabel
    Left = 256
    Top = 240
    Width = 9
    Height = 13
    Caption = 'M'
    Color = clRed
    ParentColor = False
    Visible = False
  end
  object LabMvtModif: TLabel
    Left = 0
    Top = 24
    Width = 9
    Height = 13
    Caption = 'M'
    Color = clRed
    ParentColor = False
    Visible = False
  end
  object GrMvt: TStringGrid
    Left = 0
    Top = 40
    Width = 89
    Height = 204
    ColCount = 2
    DefaultColWidth = 40
    FixedColor = 13693007
    RowCount = 8
    FixedRows = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goAlwaysShowEditor]
    TabOrder = 0
    OnClick = GrMvtClick
    OnKeyPress = GrMvtKeyPress
    OnSelectCell = GrMvtSelectCell
    RowHeights = (
      24
      25
      24
      24
      24
      24
      24
      24)
  end
  object BtBnOK: TBitBtn
    Left = 8
    Top = 256
    Width = 57
    Height = 25
    TabOrder = 1
    OnClick = BtBnOKClick
    Kind = bkOK
  end
  object SGSortie: TStringGrid
    Left = 136
    Top = 256
    Width = 129
    Height = 57
    ColCount = 3
    DefaultColWidth = 40
    FixedCols = 0
    RowCount = 2
    FixedRows = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goAlwaysShowEditor]
    ScrollBars = ssNone
    TabOrder = 2
    OnEnter = SGSortieEnter
    OnExit = SGExit
    OnKeyDown = SGKeyDown
    OnKeyPress = SGKeyPress
  end
  object SGEntree: TStringGrid
    Left = 136
    Top = 176
    Width = 129
    Height = 57
    ColCount = 3
    DefaultColWidth = 40
    FixedCols = 0
    RowCount = 2
    FixedRows = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goAlwaysShowEditor]
    ScrollBars = ssNone
    TabOrder = 3
    OnEnter = SGEntreeEnter
    OnExit = SGExit
    OnKeyDown = SGKeyDown
    OnKeyPress = SGKeyPress
  end
  object SGVente: TStringGrid
    Left = 136
    Top = 16
    Width = 129
    Height = 57
    ColCount = 3
    DefaultColWidth = 40
    FixedCols = 0
    RowCount = 2
    FixedRows = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goAlwaysShowEditor]
    ScrollBars = ssNone
    TabOrder = 4
    OnExit = SGExit
    OnKeyDown = SGKeyDown
    OnKeyPress = SGKeyPress
  end
  object SGAchat: TStringGrid
    Left = 136
    Top = 96
    Width = 129
    Height = 57
    ColCount = 3
    DefaultColWidth = 40
    FixedCols = 0
    RowCount = 2
    FixedRows = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goAlwaysShowEditor]
    ScrollBars = ssNone
    TabOrder = 5
    OnExit = SGExit
    OnKeyDown = SGKeyDown
    OnKeyPress = SGKeyPress
  end
  object LBAnimaux: TListBox
    Left = 136
    Top = 320
    Width = 129
    Height = 97
    Color = clInfoBk
    ItemHeight = 13
    TabOrder = 6
    OnClick = LBAnimauxClick
  end
end
