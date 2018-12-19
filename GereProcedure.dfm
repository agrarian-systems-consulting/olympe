inherited GereProcedureFrm: TGereProcedureFrm
  Left = 0
  Top = 108
  Caption = 'GereProcedureFrm'
  PixelsPerInch = 96
  TextHeight = 13
  inherited GBEnsemble: TGroupBox
    inherited GBAtelier: TGroupBox
      Caption = 'Proc'#233'dures'
    end
  end
  object BtBnLesProcedures: TBitBtn
    Left = 16
    Top = 488
    Width = 75
    Height = 25
    Caption = 'Les Procedures'
    TabOrder = 4
    OnClick = BtBnLesProceduresClick
  end
  object OpenDProcedure: TOpenDialog
    DefaultExt = '*.xml'
    Filter = 'Procedures.xml|*.xml'
    Title = 'LesProc'#233'dures'
    Left = 112
    Top = 488
  end
  object XMLDoc: TXMLDocument
    FileName = 'C:\OlympeInter\LesProcedures.xml'
    Left = 144
    Top = 496
    DOMVendorDesc = 'MSXML'
  end
end
