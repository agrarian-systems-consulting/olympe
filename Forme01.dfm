inherited Forme01Frm: TForme01Frm
  Left = 190
  Top = 241
  Width = 811
  Height = 347
  Caption = 'Sortie'
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panell: TPanel
    Top = 279
    Width = 803
    inherited BtBnQuitter: TBitBtn
      Visible = False
    end
    inherited BtClasser: TButton
      Visible = False
    end
    inherited BtBnStocker: TBitBtn
      Visible = False
    end
    inherited ChBRepTout: TCheckBox
      Visible = False
    end
    object RGPrecision: TRadioGroup
      Left = 408
      Top = 0
      Width = 73
      Height = 39
      Caption = 'Precision'
      Columns = 2
      ItemIndex = 0
      Items.Strings = (
        '0  '
        '2')
      TabOrder = 8
      OnClick = RGPrecisionClick
    end
    object BtBnMoin12: TBitBtn
      Left = 104
      Top = 8
      Width = 33
      Height = 25
      Caption = '- 12'
      TabOrder = 9
      OnClick = BtBnMoin12Click
    end
    object BtBnPlus12: TBitBtn
      Left = 136
      Top = 8
      Width = 33
      Height = 25
      Caption = '+12'
      TabOrder = 10
      OnClick = BtBnPlus12Click
    end
  end
  inherited Grille0: TStringGrid
    Top = 41
    Width = 799
    Height = 238
    Align = alLeft
    Anchors = [akLeft, akTop, akRight, akBottom]
    RowCount = 2
    FixedRows = 0
    OnDrawCell = Grille0DrawCell
    RowHeights = (
      25
      24)
  end
  inherited PanHaut: TPanel
    Width = 803
    Visible = False
    inherited LabelModifie: TLabel
      Left = 624
      Top = 13
      Visible = False
    end
  end
end
