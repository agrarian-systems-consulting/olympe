inherited TresoResFrm: TTresoResFrm
  Left = 146
  Top = 47
  Width = 1020
  Caption = 'Tr'#233'sorerie Mensuelle'
  OnActivate = FormActivate
  OnCloseQuery = FormCloseQuery
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panell: TPanel
    Width = 1012
    object BtBnPlus12: TBitBtn
      Left = 40
      Top = 8
      Width = 33
      Height = 25
      Caption = '+12'
      TabOrder = 2
      OnClick = BtBnPlus12Click
    end
    object BtBnMoin12: TBitBtn
      Left = 8
      Top = 8
      Width = 33
      Height = 25
      Caption = '- 12'
      TabOrder = 3
      OnClick = BtBnMoin12Click
    end
    object RGPrecision: TRadioGroup
      Left = 184
      Top = 0
      Width = 73
      Height = 39
      Caption = 'Precision'
      Columns = 2
      ItemIndex = 0
      Items.Strings = (
        '0  '
        '2')
      TabOrder = 4
      OnClick = RGPrecisionClick
    end
    object BtBnGraphique: TBitBtn
      Left = 464
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Graphique'
      TabOrder = 5
      OnClick = BtBnGraphiqueClick
    end
    object BtBnExcel: TBitBtn
      Left = 112
      Top = 8
      Width = 25
      Height = 25
      Hint = 'Envoi vers Excel'
      TabOrder = 6
      OnClick = BtBnExcelClick
      Glyph.Data = {
        6E040000424D6E04000000000000360000002800000013000000120000000100
        18000000000038040000C40E0000C40E00000000000000000000DFDFDFC0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000DFDFDFC0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000DFDFDFC0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C000000000000000
        0000000000000000C0C0C0000000DFDFDFC0C0C0000000000000000000000000
        0000000000000000000000000000000000000000008080008080008080008080
        00000000C0C0C0000000DFDFDFC0C0C000000080808080808080808080808080
        8080808080808080808080000000808000FFFF00FFFF00FFFFFF000000C0C0C0
        C0C0C0000000DFDFDFC0C0C0C0C0C0000000FFFF008080008080008080008080
        00808000000000808000FFFF00FFFF00FFFFFF000000C0C0C0C0C0C0C0C0C000
        0000DFDFDFC0C0C0C0C0C0C0C0C0000000FFFF00808000808000808000000000
        808000FFFF00FFFF00FFFFFF000000808000000000C0C0C0C0C0C0000000DFDF
        DFC0C0C0C0C0C0C0C0C0C0C0C0000000FFFF00808000000000808000FFFF00FF
        FF00FFFFFF000000000000000000000000C0C0C0C0C0C0000000DFDFDFC0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0000000000000808000FFFF00FFFF00FFFFFF0000
        00C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000DFDFDFC0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0000000808000FFFF00FFFF00FFFFFF000000000000C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000DFDFDFC0C0C0C0C0C0C0C0C0C0C0
        C0000000808000FFFF00FFFF00FFFFFF000000808000808080000000C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0000000DFDFDFC0C0C0C0C0C0C0C0C0000000808000
        FFFF00FFFF00FFFFFF000000FFFF00808000808000808080000000C0C0C0C0C0
        C0C0C0C0C0C0C0000000DFDFDFC0C0C0C0C0C0000000808000FFFF00FFFF00FF
        FFFF000000C0C0C0000000FFFF00808000808000808080000000C0C0C0C0C0C0
        C0C0C0000000DFDFDFC0C0C0000000FFFFFFFFFFFFFFFFFFFFFFFF000000C0C0
        C0C0C0C0C0C0C0000000FFFF00FFFF00FFFF00FFFF00000000C0C0C0C0C0C000
        0000DFDFDFC0C0C0000000000000000000000000000000C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0000000000000000000000000000000C0C0C0C0C0C0000000DFDF
        DFC0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000DFDFDFC0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000DFDFDFC0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000}
    end
    object BtBnImp: TBitBtn
      Left = 88
      Top = 8
      Width = 25
      Height = 25
      Hint = 'Imprimer'
      TabOrder = 7
      OnClick = BtBnImpClick
      Glyph.Data = {
        36030000424D3603000000000000360000002800000010000000100000000100
        18000000000000030000C40E0000C40E00000000000000000000C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C000000000000000000000000000000000
        0000000000000000000000000000000000C0C0C0C0C0C0C0C0C0C0C0C0000000
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000C0C0
        C0000000C0C0C0C0C0C000000000000000000000000000000000000000000000
        0000000000000000000000000000000000C0C0C0000000C0C0C0000000C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C000FFFF00FFFF00FFFFC0C0C0C0C0C00000
        00000000000000C0C0C0000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C080
        8080808080808080C0C0C0C0C0C0000000C0C0C0000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        00C0C0C0C0C0C0000000000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0000000C0C0C0000000C0C0C0000000C0C0C0000000
        000000000000000000000000000000000000000000000000000000C0C0C00000
        00C0C0C0000000000000C0C0C0C0C0C0000000FFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFF000000C0C0C0000000C0C0C0000000C0C0C0C0C0C0
        C0C0C0000000FFFFFF000000000000000000000000000000FFFFFF0000000000
        00000000000000C0C0C0C0C0C0C0C0C0C0C0C0000000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFF000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0000000FFFFFF000000000000000000000000000000FFFFFF0000
        00C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000FFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
        00000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0}
    end
    object BtBnEffSelection: TBitBtn
      Left = 312
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Efface Selection'
      TabOrder = 8
      OnClick = BtBnEffSelectionClick
    end
  end
  object SG: TStringGrid
    Left = 0
    Top = 0
    Width = 1012
    Height = 670
    Align = alClient
    Color = clWhite
    ColCount = 122
    FixedColor = 12713921
    FixedCols = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goThumbTracking]
    TabOrder = 1
    OnClick = SGClick
    OnDrawCell = SGDrawCell
    ColWidths = (
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64
      64)
    RowHeights = (
      24
      24
      24
      24
      24)
  end
end
