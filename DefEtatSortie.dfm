inherited DefEtatSortieFrm: TDefEtatSortieFrm
  Left = 193
  Top = 158
  Width = 808
  Caption = 'Etat de Sortie'
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panell: TPanel
    Width = 800
    inherited BoutFermer: TBitBtn
      Left = 648
      Anchors = [akRight, akBottom]
    end
    inherited BtBnQuitter: TBitBtn
      Left = 728
      Anchors = [akRight, akBottom]
    end
    inherited ChBRepTout: TCheckBox
      Left = 472
      Visible = False
    end
    inherited BtRepBas: TBitBtn
      Left = 408
      Visible = False
    end
    inherited BtRecopBas: TBitBtn
      Left = 440
      Visible = False
    end
    inherited BtBnNote: TBitBtn
      Enabled = True
    end
    inherited BtBnVersExcel: TBitBtn
      TabOrder = 15
    end
    object BtBnResultat: TBitBtn
      Left = 256
      Top = 8
      Width = 115
      Height = 30
      Caption = 'R'#233'sultat'
      TabOrder = 13
      OnClick = BtBnResultatClick
    end
  end
  inherited Grille0: TStringGrid
    Width = 593
    Align = alLeft
    OnDrawCell = Grille0DrawCell
  end
  inherited PanHaut: TPanel
    Width = 800
    object RGModifiable: TRadioGroup
      Left = 672
      Top = 0
      Width = 105
      Height = 33
      Anchors = [akTop, akRight]
      Caption = 'Modifiable'
      Color = clRed
      Columns = 2
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemIndex = 0
      Items.Strings = (
        'Non'
        'Oui')
      ParentColor = False
      ParentFont = False
      TabOrder = 2
      OnClick = RGModifiableClick
    end
    object BtBnAide: TBitBtn
      Left = 624
      Top = 8
      Width = 25
      Height = 25
      Caption = '?'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      OnClick = BtBnAideClick
    end
  end
  object PanG: TPanel [3]
    Left = 600
    Top = 41
    Width = 200
    Height = 384
    Align = alRight
    TabOrder = 3
    DesignSize = (
      200
      384)
    object BtBnDico: TBitBtn
      Left = 29
      Top = 32
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Dico'
      TabOrder = 0
      OnClick = BtBnDicoClick
    end
    object LBService: TListBox
      Left = 0
      Top = 311
      Width = 187
      Height = 73
      Anchors = [akRight, akBottom]
      Color = clInfoBk
      ItemHeight = 13
      Items.Strings = (
        'Ins'#233'rer'
        'Supprimer Ligne'
        'Ligne Vide'
        'Trait'
        'Titre')
      TabOrder = 1
      OnClick = LBServiceClick
    end
  end
  inherited ActionList1: TActionList
    Left = 720
    Top = 60
  end
  object ColorDialog: TColorDialog
    Ctl3D = True
    Left = 752
    Top = 56
  end
end
