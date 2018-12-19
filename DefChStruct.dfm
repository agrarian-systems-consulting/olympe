inherited DefChStructFrm: TDefChStructFrm
  Left = 219
  Top = 142
  Caption = 'DefChStructFrm'
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
  end
end
