inherited LesDefSimFrm: TLesDefSimFrm
  Left = 3
  Top = 3
  Caption = 'Les Simulations d'#233'finies'
  OnHelp = FormHelp
  PixelsPerInch = 96
  TextHeight = 13
  object LabPrix: TLabel [0]
    Left = 16
    Top = 0
    Width = 38
    Height = 20
    Caption = 'PRIX'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object LabQuantite: TLabel [1]
    Left = 240
    Top = 0
    Width = 80
    Height = 20
    Caption = 'QUANTITE'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  inherited Panell: TPanel
    inherited BtClasser: TButton
      Visible = False
    end
    inherited ChBRepTout: TCheckBox
      Visible = False
    end
    object BtBnReprendre: TBitBtn
      Left = 112
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Reprendre'
      TabOrder = 8
      OnClick = BtBnReprendreClick
    end
  end
  inherited Grille0: TStringGrid
    Left = 8
    Top = 48
    Height = 385
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goTabs, goAlwaysShowEditor, goThumbTracking]
    ColWidths = (
      64
      64
      64
      64
      64)
  end
end
