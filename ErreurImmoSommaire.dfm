object ErreurImmoSommaireFrm: TErreurImmoSommaireFrm
  Left = 435
  Top = 213
  Width = 220
  Height = 331
  Caption = 'Immo Sommaire'
  Color = clAqua
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object GB: TGroupBox
    Left = 0
    Top = 0
    Width = 209
    Height = 161
    Caption = 'Erreur'
    Color = clAqua
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 0
    object RE: TRichEdit
      Left = 8
      Top = 16
      Width = 185
      Height = 137
      Color = clInfoBk
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Lines.Strings = (
        'La Formule'
        'Valeur R'#233'siduelle[n]='
        '       Valeur Residuelle(n-1)'
        '       -  Amortissement(n)'
        '       + Achat(n)'
        '       - Revente(n)'
        '       + Production d'#39'immo(n)'
        'N'#39'EST PAS VERIFIEE !'
        ''
        ''
        '')
      ParentFont = False
      TabOrder = 0
    end
  end
  object RG: TRadioGroup
    Left = 8
    Top = 176
    Width = 201
    Height = 81
    Caption = 'Calculer'
    Color = clInfoBk
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemIndex = 0
    Items.Strings = (
      ' Valeurs R'#233'siduelles'
      ' Amortissements'
      ' Ne rien faire')
    ParentColor = False
    ParentFont = False
    TabOrder = 1
  end
  object BtBnCalculer: TBitBtn
    Left = 56
    Top = 264
    Width = 75
    Height = 25
    Caption = 'Calculer'
    TabOrder = 2
    OnClick = BtBnCalculerClick
  end
end
