object DefActionFrm: TDefActionFrm
  Left = 217
  Top = 217
  Width = 696
  Height = 480
  Align = alCustom
  Caption = 'DefActionFrm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  PixelsPerInch = 96
  TextHeight = 13
  object PanHaut: TPanel
    Left = 0
    Top = 0
    Width = 688
    Height = 41
    Align = alTop
    TabOrder = 0
    object LabelModifie: TLabel
      Left = 568
      Top = 5
      Width = 69
      Height = 20
      Caption = 'Modifi'#233' !'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      Visible = False
    end
    object LabRegle: TLabel
      Left = 16
      Top = 8
      Width = 86
      Height = 20
      Caption = 'Regle N'#176' 1'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object BtDico: TBitBtn
      Left = 336
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Dico'
      TabOrder = 0
      OnClick = BtDicoClick
    end
    object BtMotCle: TBitBtn
      Left = 416
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Mots Cle'
      TabOrder = 1
      OnClick = BtMotCleClick
    end
  end
  object PanBas: TPanel
    Left = 0
    Top = 405
    Width = 688
    Height = 41
    Align = alBottom
    TabOrder = 1
    object BtSortir: TBitBtn
      Left = 488
      Top = 8
      Width = 75
      Height = 25
      TabOrder = 0
      Kind = bkClose
    end
    object BtBnQuitter: TBitBtn
      Left = 600
      Top = 8
      Width = 50
      Height = 25
      Caption = 'Quitter'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      OnClick = BtBnQuitterClick
    end
  end
  object GBCondition: TGroupBox
    Left = 0
    Top = 41
    Width = 689
    Height = 96
    Align = alCustom
    Anchors = [akLeft, akTop, akRight]
    Caption = 'Condition'
    TabOrder = 2
    object REdit: TRichEdit
      Left = 2
      Top = 15
      Width = 685
      Height = 79
      Align = alTop
      Color = clAqua
      Lines.Strings = (
        'REdit')
      TabOrder = 0
    end
  end
  object GBAction: TGroupBox
    Left = 0
    Top = 144
    Width = 688
    Height = 261
    Align = alBottom
    Anchors = [akLeft, akTop, akRight, akBottom]
    Caption = 'Actions'
    TabOrder = 3
    object SG: TStringGrid
      Left = 2
      Top = 15
      Width = 684
      Height = 244
      Align = alClient
      Anchors = [akLeft, akRight, akBottom]
      ColCount = 2
      FixedColor = 13693007
      FixedCols = 0
      RowCount = 9
      GridLineWidth = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goEditing]
      TabOrder = 0
      OnClick = SGClick
      OnDrawCell = SGDrawCell
      ColWidths = (
        64
        64)
    end
  end
end
