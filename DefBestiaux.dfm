inherited DefBestiauxFrm: TDefBestiauxFrm
  Left = 166
  Top = 111
  Caption = 'Mouvement des Animaux'
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panell: TPanel
    inherited BtRecopBas: TBitBtn
      Visible = False
    end
    inherited BtBnNote: TBitBtn
      Enabled = True
    end
  end
  inherited PanHaut: TPanel
    inherited LabelModifie: TLabel
      Visible = False
    end
    inherited BtBnTva: TButton
      OnClick = BtBnTvaClick
    end
    object BtBnAide: TBitBtn
      Left = 664
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
      TabOrder = 2
      OnClick = BtBnAideClick
    end
  end
end
