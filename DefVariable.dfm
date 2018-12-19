inherited DefVariableFrm: TDefVariableFrm
  Caption = 'Variables'
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panell: TPanel
    inherited BtBnNote: TBitBtn
      Enabled = True
    end
  end
  inherited PanHaut: TPanel
    inherited LabelModifie: TLabel
      Visible = False
    end
    inherited BtBnUnite: TBitBtn
      OnClick = BtBnUniteClick
    end
  end
end
