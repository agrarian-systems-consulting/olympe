inherited AssolFrm: TAssolFrm
  Left = 202
  Top = 17
  Width = 791
  Caption = 'Assolement'
  OnHelp = FormHelp
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panell: TPanel
    Width = 783
    inherited BoutFermer: TBitBtn
      Hint = 'Fermer la page'
    end
    inherited BtClasser: TButton
      Left = 144
      Top = 16
      Visible = False
    end
    inherited PClasst: TPanel
      Left = 227
      inherited BtClBas: TBitBtn
        Hint = 'Report vers le bas'
      end
      inherited BtBnFermClasst: TBitBtn
        Hint = 'Arreter les reports'
      end
    end
    inherited ChBRepTout: TCheckBox
      Left = 152
      Top = 8
      Visible = False
    end
    object RGPrecision: TRadioGroup
      Left = 336
      Top = 0
      Width = 73
      Height = 39
      Caption = 'Precision'
      Columns = 2
      ItemIndex = 1
      Items.Strings = (
        '0  '
        '2')
      TabOrder = 8
      OnClick = RGPrecisionClick
    end
  end
  inherited Grille0: TStringGrid
    Top = 41
    Width = 783
    Height = 629
    Align = alClient
  end
  inherited PanHaut: TPanel
    Width = 783
    Visible = False
  end
end
