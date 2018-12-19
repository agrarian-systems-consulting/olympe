inherited AppelFctFrm: TAppelFctFrm
  Width = 801
  Caption = 'AppelFctFrm'
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panell: TPanel
    Width = 793
  end
  inherited Grille0: TStringGrid
    Left = 336
    Top = 250
    Width = 337
    Height = 151
  end
  inherited PanHaut: TPanel
    Width = 793
    object Label1: TLabel
      Left = 16
      Top = 16
      Width = 209
      Height = 24
      Caption = 'NON FONCTIONNEL !!!!'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
  end
  object PanB2: TPanel [3]
    Left = 0
    Top = 459
    Width = 793
    Height = 41
    Align = alBottom
    TabOrder = 3
    object BtBnALancer: TBitBtn
      Left = 0
      Top = 8
      Width = 201
      Height = 25
      Caption = 'Programme '#224' Lancer'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      OnClick = BtBnALancerClick
    end
  end
  object PanH1: TPanel [4]
    Left = 0
    Top = 41
    Width = 793
    Height = 144
    Align = alTop
    TabOrder = 4
    object LabExecutable: TLabel
      Left = 168
      Top = 64
      Width = 91
      Height = 16
      Caption = 'Ex'#233'cutable      : '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object LabLigneCommande: TLabel
      Left = 168
      Top = 96
      Width = 131
      Height = 16
      Caption = 'Ligne de Commande :'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object LabProcedure: TLabel
      Left = 24
      Top = 16
      Width = 83
      Height = 20
      Caption = 'Proc'#233'dure'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object BtBnDico: TBitBtn
      Left = 680
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Dico'
      Enabled = False
      TabOrder = 0
      OnClick = BtBnDicoClick
    end
    object EdExecutable: TEdit
      Left = 320
      Top = 56
      Width = 121
      Height = 21
      TabOrder = 1
      Text = 'EdExecutable'
      OnClick = EdExecutableClick
    end
    object EdLigneCommande: TEdit
      Left = 320
      Top = 96
      Width = 121
      Height = 21
      TabOrder = 2
      Text = 'EdLigneCommande'
      OnClick = EdLigneCommandeClick
    end
    object EdProcedure: TEdit
      Left = 168
      Top = 16
      Width = 121
      Height = 28
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      Text = 'EdProcedure'
    end
    object RGExecutable: TRadioGroup
      Left = 24
      Top = 56
      Width = 89
      Height = 73
      Caption = 'Ex'#233'cutable'
      ItemIndex = 0
      Items.Strings = (
        'Excel'
        'Autre')
      TabOrder = 4
    end
  end
  object OpenDialog: TOpenDialog
    DefaultExt = '*.exe'
    Filter = 'tout '#233'x'#233'cutable|*.exe'
    Left = 312
    Top = 464
  end
end
