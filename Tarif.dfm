inherited TarifFrm: TTarifFrm
  Width = 502
  Height = 357
  Caption = 'TarifFrm'
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panell: TPanel
    Top = 282
    Width = 494
    inherited BoutFermer: TBitBtn
      Left = 264
    end
    inherited BtBnQuitter: TBitBtn
      Left = 344
    end
    inherited BtClasser: TButton
      Left = 96
      Visible = False
    end
    inherited PClasst: TPanel
      Left = 171
    end
    inherited ChBRepTout: TCheckBox
      Left = 176
      Visible = False
    end
  end
  inherited Grille0: TStringGrid
    Top = 200
    Width = 449
    Height = 81
    ColCount = 6
    FixedCols = 2
    RowCount = 3
    ColWidths = (
      64
      32
      64
      64
      64
      64)
  end
  inherited PanHaut: TPanel
    Width = 494
    BevelOuter = bvNone
    inherited LabelModifie: TLabel
      Left = 376
    end
    object LabNom: TLabel
      Left = 8
      Top = 8
      Width = 67
      Height = 20
      Caption = 'LabNom'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabCondition: TLabel
      Left = 192
      Top = 24
      Width = 44
      Height = 13
      Caption = 'Condition'
    end
    object BtBnDico: TBitBtn
      Left = 288
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Dictionnaire'
      TabOrder = 0
      OnClick = BtBnDicoClick
    end
  end
  object RECondition: TRichEdit [3]
    Left = 0
    Top = 41
    Width = 494
    Height = 89
    Align = alTop
    Color = clAqua
    TabOrder = 3
  end
  object PanPourRG: TPanel [4]
    Left = 0
    Top = 130
    Width = 494
    Height = 63
    Align = alTop
    TabOrder = 4
    object RGLimite: TRadioGroup
      Left = 16
      Top = 8
      Width = 73
      Height = 50
      Caption = 'Limite'
      Columns = 2
      ItemIndex = 0
      Items.Strings = (
        '<'
        '<=')
      TabOrder = 0
      OnClick = RGLimiteClick
    end
    object RGMultiple: TRadioGroup
      Left = 96
      Top = 8
      Width = 129
      Height = 50
      Caption = 'Multiple ou Unique'
      Columns = 2
      ItemIndex = 0
      Items.Strings = (
        'Palier'
        'Exclusif')
      TabOrder = 1
    end
  end
end
