object QRGrille00Frm: TQRGrille00Frm
  Left = 253
  Top = 225
  Width = 696
  Height = 480
  Caption = 'QRGrille00Frm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Scaled = False
  OnClick = FormClick
  PixelsPerInch = 96
  TextHeight = 13
  object QR: TQuickRep
    Tag = 10
    Left = 21
    Top = 27
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
    PrinterSettings.FirstPage = 1
    PrinterSettings.LastPage = 0
    PrinterSettings.OutputBin = Auto
    PrintIfEmpty = True
    ReportTitle = '"titre"'
    SnapToGrid = True
    Units = MM
    Zoom = 100
    object TitleBand1: TQRBand
      Left = 38
      Top = 38
      Width = 1047
      Height = 107
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
        283.104166666667
        2770.1875)
      BandType = rbTitle
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
      object QRSysData1: TQRSysData
        Left = 0
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
          0
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
      object TitreEtat: TQRLabel
        Left = 0
        Top = 48
        Width = 113
        Height = 33
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          87.3125
          0
          127
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
    object DetailBand1: TQRBand
      Left = 38
      Top = 145
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
      object Val0: TQRLabel
        Left = -1
        Top = 0
        Width = 27
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
          71.4375)
        Alignment = taRightJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Val0'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object Val1: TQRLabel
        Left = 78
        Top = 0
        Width = 27
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          206.375
          0
          71.4375)
        Alignment = taRightJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Val1'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object Val2: TQRLabel
        Left = 157
        Top = 0
        Width = 27
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          415.395833333333
          0
          71.4375)
        Alignment = taRightJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Val2'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object Val3: TQRLabel
        Left = 235
        Top = 0
        Width = 27
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          621.770833333333
          0
          71.4375)
        Alignment = taRightJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Val3'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object Val4: TQRLabel
        Left = 313
        Top = 0
        Width = 27
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          828.145833333333
          0
          71.4375)
        Alignment = taRightJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Val4'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object Val5: TQRLabel
        Left = 392
        Top = 0
        Width = 27
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1037.16666666667
          0
          71.4375)
        Alignment = taRightJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Val5'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object Val6: TQRLabel
        Left = 470
        Top = 0
        Width = 27
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1243.54166666667
          0
          71.4375)
        Alignment = taRightJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Val6'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object Val7: TQRLabel
        Left = 548
        Top = 0
        Width = 27
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1449.91666666667
          0
          71.4375)
        Alignment = taRightJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Val7'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object Val8: TQRLabel
        Left = 626
        Top = 0
        Width = 27
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1656.29166666667
          0
          71.4375)
        Alignment = taRightJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Val8'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object Val9: TQRLabel
        Left = 705
        Top = 0
        Width = 27
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1865.3125
          0
          71.4375)
        Alignment = taRightJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Val9'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object Val10: TQRLabel
        Left = 735
        Top = 0
        Width = 34
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1944.6875
          0
          89.9583333333333)
        Alignment = taRightJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Val10'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object Val11: TQRLabel
        Left = 785
        Top = 0
        Width = 34
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          2076.97916666667
          0
          89.9583333333333)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Val11'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object Val12: TQRLabel
        Left = 833
        Top = 0
        Width = 34
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          2203.97916666667
          0
          89.9583333333333)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Val12'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object Val13: TQRLabel
        Left = 880
        Top = 0
        Width = 34
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          2328.33333333333
          0
          89.9583333333333)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Val13'
        Color = clWhite
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object Val14: TQRLabel
        Left = 920
        Top = 0
        Width = 34
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          2434.16666666667
          0
          89.9583333333333)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Val14'
        Color = clWhite
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object Val15: TQRLabel
        Left = 968
        Top = 0
        Width = 34
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          2561.16666666667
          0
          89.9583333333333)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Val15'
        Color = clWhite
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
    end
    object PageFooterBand1: TQRBand
      Left = 38
      Top = 165
      Width = 1047
      Height = 16
      Frame.Color = clBlack
      Frame.DrawTop = False
      Frame.DrawBottom = False
      Frame.DrawLeft = False
      Frame.DrawRight = False
      AlignToBottom = False
      Color = clWhite
      ForceNewColumn = False
      ForceNewPage = False
      Size.Values = (
        42.3333333333333
        2770.1875)
      BandType = rbPageFooter
      object QRSysData2: TQRSysData
        Left = 1000
        Top = 0
        Width = 55
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          2645.83333333333
          0
          145.520833333333)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        Color = clWhite
        Data = qrsPageNumber
        Transparent = False
        FontSize = 10
      end
    end
  end
end
