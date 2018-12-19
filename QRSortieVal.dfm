object QRSortieValFrm: TQRSortieValFrm
  Left = 253
  Top = 251
  Width = 696
  Height = 480
  Caption = 'QRSortieValFrm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Scaled = False
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 16
  object QR: TQuickRep
    Tag = 10
    Left = 32
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
      Height = 90
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
        238.125
        2770.1875)
      BandType = rbTitle
      object NomAgri: TQRLabel
        Left = 0
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
          0
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
          0
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
      object ValeurEn: TQRLabel
        Left = 4
        Top = 72
        Width = 70
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          10.5833333333333
          190.5
          185.208333333333)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Valeur En : '
        Color = clAqua
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object UniteMonnaie: TQRLabel
        Left = 76
        Top = 72
        Width = 80
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          201.083333333333
          190.5
          211.666666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'UniteMonnaie'
        Color = clAqua
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
    end
    object ColumnHeaderBand1: TQRBand
      Left = 38
      Top = 128
      Width = 1047
      Height = 20
      Frame.Color = clBlack
      Frame.DrawTop = True
      Frame.DrawBottom = True
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
      object LabAn0: TQRLabel
        Left = 208
        Top = 0
        Width = 45
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
          119.0625)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'LabAn0'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object LabAn1: TQRLabel
        Left = 286
        Top = 0
        Width = 45
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          756.708333333333
          0
          119.0625)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'LabAn1'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object LabAn2: TQRLabel
        Left = 365
        Top = 0
        Width = 45
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
          119.0625)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'LabAn2'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object LabAn3: TQRLabel
        Left = 443
        Top = 0
        Width = 45
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1172.10416666667
          0
          119.0625)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'LabAn3'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object LabAn4: TQRLabel
        Left = 521
        Top = 0
        Width = 45
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1378.47916666667
          0
          119.0625)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'LabAn4'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object LabAn5: TQRLabel
        Left = 600
        Top = 0
        Width = 45
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1587.5
          0
          119.0625)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'LabAn5'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object LabAn6: TQRLabel
        Left = 678
        Top = 0
        Width = 45
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1793.875
          0
          119.0625)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'LabAn6'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object LabAn7: TQRLabel
        Left = 756
        Top = 0
        Width = 45
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          2000.25
          0
          119.0625)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'LabAn7'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object LabAn8: TQRLabel
        Left = 834
        Top = 0
        Width = 45
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          2206.625
          0
          119.0625)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'LabAn8'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object LabAn9: TQRLabel
        Left = 913
        Top = 0
        Width = 45
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          2415.64583333333
          0
          119.0625)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'LabAn9'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object LabAn10: TQRLabel
        Left = 991
        Top = 0
        Width = 52
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          2622.02083333333
          0
          137.583333333333)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'LabAn10'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
    end
    object DetailBand1: TQRBand
      Left = 38
      Top = 148
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
        Left = 286
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
          756.708333333333
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
        Left = 365
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
          965.729166666667
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
        Left = 443
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
          1172.10416666667
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
        Left = 521
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
          1378.47916666667
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
        Left = 600
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
          1587.5
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
        Left = 678
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
          1793.875
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
        Left = 756
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
          2000.25
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
        Left = 834
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
          2206.625
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
        Left = 913
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
          2415.64583333333
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
        Left = 991
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
          2622.02083333333
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
    end
    object PageFooterBand1: TQRBand
      Left = 38
      Top = 168
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
