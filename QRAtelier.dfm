object QRAtelierFrm: TQRAtelierFrm
  Left = 266
  Top = 138
  Width = 696
  Height = 480
  Caption = 'Atelier'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Scaled = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object QR: TQuickRep
    Left = 16
    Top = 16
    Width = 1123
    Height = 794
    Frame.Color = clBlack
    Frame.DrawTop = False
    Frame.DrawBottom = False
    Frame.DrawLeft = False
    Frame.DrawRight = False
    BeforePrint = QRBeforePrint
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = []
    Functions.Strings = (
      'PAGENUMBER'
      'COLUMNNUMBER'
      'REPORTTITLE')
    Functions.DATA = (
      '0'
      '0'
      #39#39)
    OnNeedData = QRNeedData
    Options = [FirstPageHeader, LastPageFooter]
    Page.Columns = 1
    Page.Orientation = poLandscape
    Page.PaperSize = A4
    Page.Values = (
      100
      2100
      100
      2970
      100
      100
      0)
    PrinterSettings.Copies = 1
    PrinterSettings.Duplex = False
    PrinterSettings.FirstPage = 0
    PrinterSettings.LastPage = 0
    PrinterSettings.OutputBin = Auto
    PrintIfEmpty = True
    SnapToGrid = True
    Units = MM
    Zoom = 100
    object ColumnHeaderBand1: TQRBand
      Left = 38
      Top = 121
      Width = 1047
      Height = 20
      Frame.Color = clBlack
      Frame.DrawTop = False
      Frame.DrawBottom = False
      Frame.DrawLeft = False
      Frame.DrawRight = False
      AlignToBottom = False
      Color = clLime
      ForceNewColumn = False
      ForceNewPage = False
      Size.Values = (
        52.9166666666667
        2770.1875)
      BandType = rbColumnHeader
      object Nom: TQRLabel
        Left = 0
        Top = 0
        Width = 28
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          0
          0
          74.0833333333333)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Nom'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object Categorie: TQRLabel
        Left = 100
        Top = 0
        Width = 56
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          264.583333333333
          0
          148.166666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Categorie'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object Unite: TQRLabel
        Left = 160
        Top = 0
        Width = 31
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          423.333333333333
          0
          82.0208333333333)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Unit'#233
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object Appro: TQRLabel
        Left = 240
        Top = 0
        Width = 35
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          635
          0
          92.6041666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Appro'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object UniteAppro: TQRLabel
        Left = 300
        Top = 0
        Width = 31
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          793.75
          0
          82.0208333333333)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Unit'#233
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object C0: TQRLabel
        Left = 368
        Top = 0
        Width = 17
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          973.666666666667
          0
          44.9791666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'C0'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object C1: TQRLabel
        Left = 417
        Top = 0
        Width = 17
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1103.3125
          0
          44.9791666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'C1'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object C2: TQRLabel
        Left = 466
        Top = 0
        Width = 17
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1232.95833333333
          0
          44.9791666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'C2'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object C3: TQRLabel
        Left = 516
        Top = 0
        Width = 17
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1365.25
          0
          44.9791666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'C3'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object C4: TQRLabel
        Left = 565
        Top = 0
        Width = 17
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1494.89583333333
          0
          44.9791666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'C4'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object C5: TQRLabel
        Left = 614
        Top = 0
        Width = 17
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1624.54166666667
          0
          44.9791666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'C5'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object C6: TQRLabel
        Left = 663
        Top = 0
        Width = 17
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1754.1875
          0
          44.9791666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'C6'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object C7: TQRLabel
        Left = 713
        Top = 0
        Width = 17
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1886.47916666667
          0
          44.9791666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'C7'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object C8: TQRLabel
        Left = 762
        Top = 0
        Width = 17
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          2016.125
          0
          44.9791666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'C8'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object C9: TQRLabel
        Left = 811
        Top = 0
        Width = 17
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          2145.77083333333
          0
          44.9791666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'C9'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object C10: TQRLabel
        Left = 860
        Top = 0
        Width = 24
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          2275.41666666667
          0
          63.5)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'C10'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object C11: TQRLabel
        Left = 910
        Top = 0
        Width = 24
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          2407.70833333333
          0
          63.5)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'C11'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object C12: TQRLabel
        Left = 959
        Top = 0
        Width = 24
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          2537.35416666667
          0
          63.5)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'C12'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object C13: TQRLabel
        Left = 1008
        Top = 0
        Width = 24
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          2667
          0
          63.5)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'C13'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
    end
    object TitleBand1: TQRBand
      Left = 38
      Top = 38
      Width = 1047
      Height = 83
      Frame.Color = clBlack
      Frame.DrawTop = False
      Frame.DrawBottom = False
      Frame.DrawLeft = False
      Frame.DrawRight = False
      AlignToBottom = False
      Color = clAqua
      ForceNewColumn = False
      ForceNewPage = False
      Size.Values = (
        219.604166666667
        2770.1875)
      BandType = rbTitle
      object QRSysData: TQRSysData
        Left = -1
        Top = 0
        Width = 65
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          -2.64583333333333
          0
          171.979166666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        Color = clAqua
        Data = qrsDateTime
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = [fsItalic]
        ParentFont = False
        Transparent = False
        FontSize = 8
      end
      object NomAgri: TQRLabel
        Left = 0
        Top = 16
        Width = 86
        Height = 25
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          66.1458333333333
          0
          42.3333333333333
          227.541666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'NomAgri '
        Color = clAqua
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 14
      end
      object TitreEtat: TQRLabel
        Left = 8
        Top = 40
        Width = 113
        Height = 33
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          87.3125
          21.1666666666667
          105.833333333333
          298.979166666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'TitreEtat'
        Color = clAqua
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -27
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 20
      end
    end
    object QRBand2: TQRBand
      Left = 38
      Top = 141
      Width = 1047
      Height = 20
      Frame.Color = clBlack
      Frame.DrawTop = False
      Frame.DrawBottom = False
      Frame.DrawLeft = False
      Frame.DrawRight = False
      AlignToBottom = False
      Color = clInfoBk
      ForceNewColumn = False
      ForceNewPage = False
      Size.Values = (
        52.9166666666667
        2770.1875)
      BandType = rbDetail
      object NomPro: TQRLabel
        Left = 38
        Top = 0
        Width = 48
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          100.541666666667
          0
          127)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'NomPro'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object NomCat: TQRLabel
        Left = 100
        Top = 0
        Width = 48
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          264.583333333333
          0
          127)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'NomCat'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object NomUnite: TQRLabel
        Left = 160
        Top = 0
        Width = 58
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          423.333333333333
          0
          153.458333333333)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'NomUnite'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object NomAppro: TQRLabel
        Left = 240
        Top = 0
        Width = 62
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          635
          0
          164.041666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'NomAppro'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object NomUniteAppro: TQRLabel
        Left = 300
        Top = 0
        Width = 92
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          793.75
          0
          243.416666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'NomUniteAppro'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object V0: TQRLabel
        Left = 365
        Top = 0
        Width = 17
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          965.729166666667
          0
          44.9791666666667)
        Alignment = taRightJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'V0'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object V1: TQRLabel
        Left = 414
        Top = 0
        Width = 17
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1095.375
          0
          44.9791666666667)
        Alignment = taRightJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'V1'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object V2: TQRLabel
        Left = 464
        Top = 0
        Width = 17
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1227.66666666667
          0
          44.9791666666667)
        Alignment = taRightJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'V2'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object V3: TQRLabel
        Left = 513
        Top = 0
        Width = 17
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1357.3125
          0
          44.9791666666667)
        Alignment = taRightJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'V3'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object V4: TQRLabel
        Left = 562
        Top = 0
        Width = 17
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1486.95833333333
          0
          44.9791666666667)
        Alignment = taRightJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'V4'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object V5: TQRLabel
        Left = 612
        Top = 0
        Width = 17
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1619.25
          0
          44.9791666666667)
        Alignment = taRightJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'V5'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object V6: TQRLabel
        Left = 661
        Top = 0
        Width = 17
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1748.89583333333
          0
          44.9791666666667)
        Alignment = taRightJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'V6'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object V7: TQRLabel
        Left = 710
        Top = 0
        Width = 17
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1878.54166666667
          0
          44.9791666666667)
        Alignment = taRightJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'V7'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object V8: TQRLabel
        Left = 759
        Top = 0
        Width = 17
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          2008.1875
          0
          44.9791666666667)
        Alignment = taRightJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'V8'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object V9: TQRLabel
        Left = 809
        Top = 0
        Width = 17
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          2140.47916666667
          0
          44.9791666666667)
        Alignment = taRightJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'V9'
        Color = clWhite
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object V10: TQRLabel
        Left = 858
        Top = 0
        Width = 24
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          2270.125
          0
          63.5)
        Alignment = taRightJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'V10'
        Color = clWhite
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object V11: TQRLabel
        Left = 907
        Top = 0
        Width = 24
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          2399.77083333333
          0
          63.5)
        Alignment = taRightJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'V11'
        Color = clWhite
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object V12: TQRLabel
        Left = 957
        Top = 0
        Width = 24
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          2532.0625
          0
          63.5)
        Alignment = taRightJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'V12'
        Color = clWhite
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object V13: TQRLabel
        Left = 1006
        Top = 0
        Width = 24
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          2661.70833333333
          0
          63.5)
        Alignment = taRightJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'V13'
        Color = clWhite
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
    end
  end
end
