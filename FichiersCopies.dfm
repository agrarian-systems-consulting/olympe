object FichiersCopiesFrm: TFichiersCopiesFrm
  Left = 198
  Top = 114
  Width = 696
  Height = 480
  Caption = 'Fichiers Copi'#233's'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object RE: TRichEdit
    Left = 0
    Top = 0
    Width = 688
    Height = 405
    Align = alClient
    Lines.Strings = (
      'RE')
    TabOrder = 0
  end
  object PanBas: TPanel
    Left = 0
    Top = 405
    Width = 688
    Height = 41
    Align = alBottom
    TabOrder = 1
    object BtBnImp: TBitBtn
      Left = 464
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Imprimer'
      TabOrder = 0
      OnClick = BtBnImpClick
    end
  end
end
