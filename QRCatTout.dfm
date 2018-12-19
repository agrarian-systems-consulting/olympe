inherited QRCatToutFrm: TQRCatToutFrm
  Left = 202
  Top = 262
  HorzScrollBar.Position = 305
  Caption = 'QRCatToutFrm'
  PixelsPerInch = 96
  TextHeight = 13
  inherited QR: TQuickRep
    Left = -292
    Functions.DATA = (
      '0'
      '0'
      #39#39)
    Page.Values = (
      100
      2100
      100
      2970
      100
      100
      0)
    inherited ColumnHeaderBand1: TQRBand
      Size.Values = (
        105.833333333333
        2770.1875)
      inherited Nom: TQRLabel
        Size.Values = (
          44.9791666666667
          100.541666666667
          0
          74.0833333333333)
        FontSize = 10
      end
      inherited Unite: TQRLabel
        Size.Values = (
          44.9791666666667
          592.666666666667
          0
          100.541666666667)
        FontSize = 10
      end
      inherited Atelier: TQRLabel
        Size.Values = (
          44.9791666666667
          658.8125
          63.5
          100.541666666667)
        FontSize = 10
      end
      inherited Expl: TQRLabel
        Size.Values = (
          44.9791666666667
          455.083333333333
          63.5
          82.0208333333333)
        FontSize = 10
      end
      inherited Region: TQRLabel
        Size.Values = (
          44.9791666666667
          857.25
          63.5
          108.479166666667)
        FontSize = 10
      end
      object Prix: TQRLabel
        Left = 416
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
          1100.66666666667
          0
          63.5)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Prix'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object Tva: TQRLabel
        Left = 544
        Top = 0
        Width = 20
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1439.33333333333
          0
          52.9166666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Tva'
        Color = clLime
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
    end
    inherited PageFooterBand1: TQRBand
      Size.Values = (
        105.833333333333
        2770.1875)
      inherited QRSysData1: TQRSysData
        Size.Values = (
          44.9791666666667
          2624.66666666667
          0
          145.520833333333)
        FontSize = 10
      end
    end
    inherited TitleBand1: TQRBand
      Size.Values = (
        219.604166666667
        2770.1875)
      inherited QRSysData2: TQRSysData
        Size.Values = (
          44.9791666666667
          -2.64583333333333
          0
          171.979166666667)
        FontSize = 8
      end
      inherited NomAgri: TQRLabel
        Size.Values = (
          66.1458333333333
          0
          42.3333333333333
          227.541666666667)
        FontSize = 14
      end
      inherited TitreEtat: TQRLabel
        Size.Values = (
          87.3125
          21.1666666666667
          105.833333333333
          298.979166666667)
        FontSize = 20
      end
    end
    inherited DetailBand1: TQRBand
      Size.Values = (
        52.9166666666667
        2770.1875)
      inherited Sup: TQRLabel
        Size.Values = (
          44.9791666666667
          21.1666666666667
          0
          63.5)
        FontSize = 10
      end
      inherited NomPro: TQRLabel
        Size.Values = (
          44.9791666666667
          190.5
          0
          127)
        FontSize = 10
      end
      inherited UUt: TQRLabel
        Left = 184
        Size.Values = (
          44.9791666666667
          486.833333333333
          0
          60.8541666666667)
        FontSize = 10
      end
      inherited UTrans: TQRLabel
        Left = 264
        Size.Values = (
          44.9791666666667
          698.5
          0
          111.125)
        FontSize = 10
      end
      inherited UGlobal: TQRLabel
        Left = 336
        Size.Values = (
          44.9791666666667
          889
          0
          124.354166666667)
        FontSize = 10
      end
      object PrixPro: TQRLabel
        Left = 432
        Top = 0
        Width = 44
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1143
          0
          116.416666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'PrixPro'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object UnPro: TQRLabel
        Left = 496
        Top = 0
        Width = 37
        Height = 17
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          44.9791666666667
          1312.33333333333
          0
          97.8958333333333)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'UnPro'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object TauxTva: TQRLabel
        Left = 568
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
          1502.83333333333
          0
          127)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'TauxTva'
        Color = clInfoBk
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
    end
  end
end
