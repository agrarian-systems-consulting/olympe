inherited DefProcedureFrm: TDefProcedureFrm
  Left = 202
  Top = 75
  Width = 801
  Height = 596
  Caption = 'D'#233'finition de la Proc'#233'dure'
  OnHelp = FormHelp
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panell: TPanel
    Top = 528
    Width = 793
    inherited BtBnExcel: TBitBtn
      Visible = False
    end
    object BtBnSup: TBitBtn
      Left = 112
      Top = 8
      Width = 25
      Height = 25
      Hint = 'Supprimer la ligne'
      TabOrder = 8
      OnClick = BtBnSupClick
      Glyph.Data = {
        26040000424D2604000000000000360000002800000010000000150000000100
        180000000000F0030000C40E0000C40E00000000000000000000C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0000000000000000000000000000000000000C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000000000C0C0C0C0C0C0C0
        C0C0808080808080808080000000000000C0C0C0C0C0C0C0C0C0C0C0C0000000
        000000FFFFFFC0C0C0C0C0C0000000C0C0C08080800000008080808080808080
        80000000000000C0C0C0C0C0C0000000FFFFFFFFFFFFC0C0C0C0C0C0000000C0
        C0C0808080000000808080808080808080808080000000C0C0C0C0C0C0000000
        FFFFFF000000C0C0C0C0C0C0000000C0C0C08080800000008080808080800000
        00808080000000C0C0C0C0C0C0000000FFFFFF000000C0C0C0C0C0C0000000C0
        C0C0808080000000808080808080000000808080000000C0C0C0C0C0C0000000
        FFFFFF000000C0C0C0C0C0C0000000C0C0C08080800000008080808080800000
        00808080000000C0C0C0C0C0C0000000FFFFFF000000C0C0C0C0C0C0000000C0
        C0C0808080000000808080808080000000808080000000C0C0C0C0C0C0000000
        FFFFFF000000C0C0C0C0C0C0000000C0C0C08080800000008080808080800000
        00808080000000C0C0C0C0C0C0000000FFFFFF000000C0C0C0C0C0C0000000C0
        C0C0808080000000808080808080000000808080000000C0C0C0C0C0C0000000
        FFFFFF000000C0C0C0C0C0C0C0C0C0C0C0C08080808080808080808080800000
        00808080000000C0C0C0C0C0C0000000FFFFFFFFFFFFC0C0C000000000000000
        0000000000000000808080808080808080808080000000C0C0C0C0C0C0000000
        000000000000000000C0C0C0C0C0C0C0C0C08080808080800000000000000000
        00000000000000C0C0C0C0C0C0000000C0C0C0C0C0C0C0C0C000000000000000
        0000000000000000808080808080808080808080000000C0C0C0000000C0C0C0
        000000000000000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C00000000000000000
        00000000808080000000000000000000FFFFFFFFFFFFC0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000000000000000C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0000000000000C0C0C0C0C0C0C0C0C0C0C0C000000080808080
        8080808080000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000C0C0C0000000
        C0C0C0C0C0C0C0C0C0C0C0C0000000000000000000C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0000000C0C0C0C0C0C0C0C0C0000000000000000000C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0000000000000000000000000C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0000000000000000000000000000000C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0}
    end
    object BtBnVideTout: TBitBtn
      Left = 136
      Top = 8
      Width = 25
      Height = 25
      Hint = 'Vide le Tableau'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 9
      OnClick = BtBnVideToutClick
      Glyph.Data = {
        26040000424D2604000000000000360000002800000010000000150000000100
        180000000000F0030000C40E0000C40E00000000000000000000C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C00000FF0000FF0000FF0000FF0000FF0000FFC0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C00000FF0000FFC0C0C0C0C0C0C0
        C0C08080808080808080800000FF0000FFC0C0C0C0C0C0C0C0C0C0C0C00000FF
        0000FFFFFFFFC0C0C0C0C0C00000FFC0C0C08080800000FF8080808080808080
        800000FF0000FFC0C0C0C0C0C00000FFFFFFFFFFFFFFC0C0C0C0C0C00000FFC0
        C0C08080800000FF8080808080808080808080800000FFC0C0C0C0C0C00000FF
        FFFFFF0000FFC0C0C0C0C0C00000FFC0C0C08080800000FF8080808080800000
        FF8080800000FFC0C0C0C0C0C00000FFFFFFFF0000FFC0C0C0C0C0C00000FFC0
        C0C08080800000FF8080808080800000FF8080800000FFC0C0C0C0C0C00000FF
        FFFFFF0000FFC0C0C0C0C0C00000FFC0C0C08080800000FF8080808080800000
        FF8080800000FFC0C0C0C0C0C00000FFFFFFFF0000FFC0C0C0C0C0C00000FFC0
        C0C08080800000FF8080808080800000FF8080800000FFC0C0C0C0C0C00000FF
        FFFFFF0000FFC0C0C0C0C0C00000FFC0C0C08080800000FF8080808080800000
        FF8080800000FFC0C0C0C0C0C00000FFFFFFFF0000FFC0C0C0C0C0C00000FFC0
        C0C08080800000FF8080808080800000FF8080800000FFC0C0C0C0C0C00000FF
        FFFFFF0000FFC0C0C0C0C0C0C0C0C0C0C0C08080808080808080808080800000
        FF8080800000FFC0C0C0C0C0C00000FFFFFFFFFFFFFFC0C0C00000FF0000FF00
        00FF0000FF0000FF8080808080808080808080800000FFC0C0C0C0C0C00000FF
        0000FF0000FF0000FFC0C0C0C0C0C0C0C0C08080808080800000FF0000FF0000
        FF0000FF0000FFC0C0C0C0C0C00000FFC0C0C0C0C0C0C0C0C00000FF0000FF00
        00FF0000FF0000FF8080808080808080808080800000FFC0C0C00000FFC0C0C0
        0000FF0000FF0000FFC0C0C0C0C0C0C0C0C0C0C0C0C0C0C00000FF0000FF0000
        FF0000FF8080800000FF0000FF0000FFFFFFFFFFFFFFC0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C00000FF0000FF0000FFC0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C00000FF0000FFC0C0C0C0C0C0C0C0C0C0C0C00000FF80808080
        80808080800000FFC0C0C0C0C0C0C0C0C0C0C0C0C0C0C00000FFC0C0C00000FF
        C0C0C0C0C0C0C0C0C0C0C0C00000FF0000FF0000FFC0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C00000FFC0C0C0C0C0C0C0C0C00000FF0000FF0000FFC0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C00000FF0000FF0000FF0000FFC0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C00000FF0000FF0000FF0000FF0000FFC0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0}
    end
  end
  inherited Grille0: TStringGrid
    Top = 153
    Width = 793
    Height = 334
    Align = alClient
    Anchors = [akLeft, akTop, akBottom]
  end
  inherited PanHaut: TPanel
    Width = 793
    object RGModifiable: TRadioGroup
      Left = 576
      Top = 0
      Width = 105
      Height = 33
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
      TabOrder = 0
      OnClick = RGModifiableClick
    end
  end
  object PanB2: TPanel [3]
    Left = 0
    Top = 487
    Width = 793
    Height = 41
    Align = alBottom
    TabOrder = 3
    object BtBnExecuter: TBitBtn
      Left = 16
      Top = 8
      Width = 137
      Height = 25
      Caption = 'Lancer la Proc'#233'dure'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      OnClick = BtBnExecuterClick
    end
    object RGTraitement: TRadioGroup
      Left = 224
      Top = 0
      Width = 257
      Height = 35
      Color = clGradientActiveCaption
      Columns = 3
      ItemIndex = 0
      Items.Strings = (
        'Agri En cours'
        'Tous'
        'S'#233'lection')
      ParentColor = False
      TabOrder = 1
      OnClick = RGTraitementClick
    end
  end
  object PanH1: TPanel [4]
    Left = 0
    Top = 41
    Width = 793
    Height = 112
    Align = alTop
    TabOrder = 4
    object LabExecutable: TLabel
      Left = 24
      Top = 48
      Width = 118
      Height = 16
      Caption = 'Ex'#233'cutable               : '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object LabFichierTransfert: TLabel
      Left = 24
      Top = 80
      Width = 118
      Height = 16
      Caption = 'Fichier de transfert  :'
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
      TabOrder = 0
      OnClick = BtBnDicoClick
    end
    object EdProcedure: TEdit
      Left = 120
      Top = 8
      Width = 345
      Height = 28
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      Text = 'EdProcedure'
    end
    object EdExe: TEdit
      Left = 144
      Top = 48
      Width = 321
      Height = 21
      TabOrder = 2
      Text = 'EdExe'
      OnKeyPress = EdExeKeyPress
    end
    object EdFichier: TEdit
      Left = 144
      Top = 80
      Width = 321
      Height = 21
      TabOrder = 3
      Text = 'EdFichier'
      OnKeyPress = EdExeKeyPress
    end
    object BtExe: TButton
      Left = 472
      Top = 48
      Width = 25
      Height = 25
      Caption = '....'
      TabOrder = 4
      OnClick = BtExeClick
    end
    object BtFichier: TButton
      Left = 472
      Top = 80
      Width = 25
      Height = 25
      Caption = '....'
      TabOrder = 5
      OnClick = BtFichierClick
    end
  end
  object OpenDialogExe: TOpenDialog
    DefaultExt = '*.exe'
    Filter = 'tout '#233'x'#233'cutable|*.exe'
    Left = 504
    Top = 88
  end
  object OpenDialogFichier: TOpenDialog
    DefaultExt = 'csv'
    Filter = '*.csv'
    Left = 504
    Top = 120
  end
end