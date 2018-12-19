object QRTresoFrm: TQRTresoFrm
  Left = 216
  Top = 128
  Width = 696
  Height = 480
  HorzScrollBar.Position = 453
  Caption = 'QRTresoFrm'
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
    Left = 8
    Top = 0
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
    ReportTitle = '"titre"'
    SnapToGrid = True
    Units = MM
    Zoom = 100
    object QRBand1: TQRBand
      Left = 38
      Top = 38
      Width = 1047
      Height = 105
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
        277.8125
        2770.1875)
      BandType = rbTitle
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
      object NomAgri: TQRLabel
        Left = 8
        Top = 16
        Width = 81
        Height = 25
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          66.1458333333333
          21.1666666666667
          42.3333333333333
          214.3125)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'NomAgri'
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
          21.1666666666667
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
      object ValeurEn: TQRLabel
        Left = 4
        Top = 80
        Width = 68
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          10.5833333333333
          211.666666666667
          179.916666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Valeur En : '
        Color = clAqua
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object QRValeurEn: TQRLabel
        Left = 4
        Top = 80
        Width = 68
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          10.5833333333333
          211.666666666667
          179.916666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Valeur En : '
        Color = clAqua
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object UniteMonnaie: TQRLabel
        Left = 76
        Top = 80
        Width = 84
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          201.083333333333
          211.666666666667
          222.25)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'UniteMonnaie'
        Color = clAqua
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
    end
    object QRBTitreCol: TQRBand
      Left = 38
      Top = 143
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
      object LabM0: TQRLabel
        Left = 208
        Top = 0
        Width = 42
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          550.333333333333
          0
          111.125)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'LabM0'
        Color = clLime
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object LabM1: TQRLabel
        Left = 270
        Top = 0
        Width = 42
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          714.375
          0
          111.125)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'LabM1'
        Color = clLime
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object LabM2: TQRLabel
        Left = 325
        Top = 0
        Width = 42
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          859.895833333333
          0
          111.125)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'LabM2'
        Color = clLime
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object LabM3: TQRLabel
        Left = 379
        Top = 0
        Width = 42
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1002.77083333333
          0
          111.125)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'LabM3'
        Color = clLime
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object LabM4: TQRLabel
        Left = 433
        Top = 0
        Width = 42
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1145.64583333333
          0
          111.125)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'LabM4'
        Color = clLime
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object LabM5: TQRLabel
        Left = 480
        Top = 0
        Width = 42
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1270
          0
          111.125)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'LabM5'
        Color = clLime
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object LabM6: TQRLabel
        Left = 526
        Top = 0
        Width = 42
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1391.70833333333
          0
          111.125)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'LabM6'
        Color = clLime
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object LabM7: TQRLabel
        Left = 580
        Top = 0
        Width = 42
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1534.58333333333
          0
          111.125)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'LabM7'
        Color = clLime
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object LabM8: TQRLabel
        Left = 634
        Top = 0
        Width = 42
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1677.45833333333
          0
          111.125)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'LabM8'
        Color = clLime
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object LabM9: TQRLabel
        Left = 689
        Top = 0
        Width = 42
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1822.97916666667
          0
          111.125)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'LabM9'
        Color = clLime
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object LabM10: TQRLabel
        Left = 743
        Top = 0
        Width = 49
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1965.85416666667
          0
          129.645833333333)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'LabM10'
        Color = clLime
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object LabM11: TQRLabel
        Left = 980
        Top = 0
        Width = 49
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          2592.91666666667
          0
          129.645833333333)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'LabM11'
        Color = clLime
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
    end
    object QRBDon: TQRBand
      Left = 38
      Top = 163
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
      object IntituleP: TQRLabel
        Left = 22
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
          58.2083333333333
          0
          127)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'IntituleP'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object Val1: TQRLabel
        Left = 272
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
          719.666666666667
          0
          71.4375)
        Alignment = taLeftJustify
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
        Left = 344
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
          910.166666666667
          0
          71.4375)
        Alignment = taLeftJustify
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
        Left = 398
        Top = 0
        Width = 23
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1053.04166666667
          0
          60.8541666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Val3'
        Color = clInfoBk
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 8
      end
      object Val4: TQRLabel
        Left = 440
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
          1164.16666666667
          0
          71.4375)
        Alignment = taLeftJustify
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
        Left = 488
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
          1291.16666666667
          0
          71.4375)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Val5'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object Val0: TQRLabel
        Left = 208
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
          550.333333333333
          0
          71.4375)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Val0'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object Val6: TQRLabel
        Left = 536
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
          1418.16666666667
          0
          71.4375)
        Alignment = taLeftJustify
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
        Left = 584
        Top = 0
        Width = 27
        Height = 25
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          66.1458333333333
          1545.16666666667
          0
          71.4375)
        Alignment = taLeftJustify
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
        Left = 632
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
          1672.16666666667
          0
          71.4375)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Val8'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object Val10: TQRLabel
        Left = 736
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
          1947.33333333333
          0
          89.9583333333333)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Val10'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object Val9: TQRLabel
        Left = 688
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
          1820.33333333333
          0
          71.4375)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Val9'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object Val11: TQRLabel
        Left = 800
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
          2116.66666666667
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
    end
    object PageFooterBand1: TQRBand
      Left = 38
      Top = 183
      Width = 1047
      Height = 18
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
        47.625
        2770.1875)
      BandType = rbPageFooter
      object QRSysData2: TQRSysData
        Left = 912
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
          2413
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
