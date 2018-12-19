inherited QRSortieQuantFrm: TQRSortieQuantFrm
  Caption = 'QRSortieQuantFrm'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 16
  inherited QR: TQuickRep
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
    inherited TitleBand1: TQRBand
      Height = 80
      Size.Values = (
        211.666666666667
        2770.1875)
      inherited NomAgri: TQRLabel
        Size.Values = (
          66.1458333333333
          0
          42.3333333333333
          214.3125)
        FontSize = 14
      end
      inherited QRSysData1: TQRSysData
        Size.Values = (
          44.9791666666667
          0
          0
          264.583333333333)
        FontSize = 8
      end
      inherited TitreEtat: TQRLabel
        Top = 48
        Size.Values = (
          87.3125
          0
          127
          298.979166666667)
        FontSize = 20
      end
      inherited ValeurEn: TQRLabel
        Top = 80
        Enabled = False
        Size.Values = (
          44.9791666666667
          10.5833333333333
          211.666666666667
          185.208333333333)
        FontSize = 10
      end
      inherited UniteMonnaie: TQRLabel
        Top = 80
        Enabled = False
        Size.Values = (
          44.9791666666667
          201.083333333333
          211.666666666667
          211.666666666667)
        FontSize = 10
      end
    end
    inherited ColumnHeaderBand1: TQRBand
      Top = 118
      Size.Values = (
        52.9166666666667
        2770.1875)
      inherited LabAn0: TQRLabel
        Left = 240
        Enabled = False
        Size.Values = (
          44.9791666666667
          635
          0
          119.0625)
        FontSize = 10
      end
      inherited LabAn1: TQRLabel
        Size.Values = (
          44.9791666666667
          756.708333333333
          0
          119.0625)
        FontSize = 10
      end
      inherited LabAn2: TQRLabel
        Size.Values = (
          44.9791666666667
          965.729166666667
          0
          119.0625)
        FontSize = 10
      end
      inherited LabAn3: TQRLabel
        Size.Values = (
          44.9791666666667
          1172.10416666667
          0
          119.0625)
        FontSize = 10
      end
      inherited LabAn4: TQRLabel
        Size.Values = (
          44.9791666666667
          1378.47916666667
          0
          119.0625)
        FontSize = 10
      end
      inherited LabAn5: TQRLabel
        Size.Values = (
          44.9791666666667
          1587.5
          0
          119.0625)
        FontSize = 10
      end
      inherited LabAn6: TQRLabel
        Size.Values = (
          44.9791666666667
          1793.875
          0
          119.0625)
        FontSize = 10
      end
      inherited LabAn7: TQRLabel
        Size.Values = (
          44.9791666666667
          2000.25
          0
          119.0625)
        FontSize = 10
      end
      inherited LabAn8: TQRLabel
        Size.Values = (
          44.9791666666667
          2206.625
          0
          119.0625)
        FontSize = 10
      end
      inherited LabAn9: TQRLabel
        Size.Values = (
          44.9791666666667
          2415.64583333333
          0
          119.0625)
        FontSize = 10
      end
      inherited LabAn10: TQRLabel
        Size.Values = (
          44.9791666666667
          2622.02083333333
          0
          137.583333333333)
        FontSize = 10
      end
      object Unite: TQRLabel
        Left = 192
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
          508
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
    end
    inherited DetailBand1: TQRBand
      Top = 138
      Size.Values = (
        52.9166666666667
        2770.1875)
      inherited IntituleP: TQRLabel
        Left = -2
        Size.Values = (
          44.9791666666667
          -5.29166666666667
          0
          127)
        FontSize = 10
      end
      inherited Val0: TQRLabel
        Left = 256
        Enabled = False
        Size.Values = (
          44.9791666666667
          677.333333333333
          0
          71.4375)
        FontSize = 10
      end
      inherited Val1: TQRLabel
        Size.Values = (
          44.9791666666667
          756.708333333333
          0
          71.4375)
        FontSize = 10
      end
      inherited Val2: TQRLabel
        Size.Values = (
          44.9791666666667
          965.729166666667
          0
          71.4375)
        FontSize = 10
      end
      inherited Val3: TQRLabel
        Size.Values = (
          44.9791666666667
          1172.10416666667
          0
          71.4375)
        FontSize = 10
      end
      inherited Val4: TQRLabel
        Size.Values = (
          44.9791666666667
          1378.47916666667
          0
          71.4375)
        FontSize = 10
      end
      inherited Val5: TQRLabel
        Size.Values = (
          44.9791666666667
          1587.5
          0
          71.4375)
        FontSize = 10
      end
      inherited Val6: TQRLabel
        Size.Values = (
          44.9791666666667
          1793.875
          0
          71.4375)
        FontSize = 10
      end
      inherited Val7: TQRLabel
        Size.Values = (
          44.9791666666667
          2000.25
          0
          71.4375)
        FontSize = 10
      end
      inherited Val8: TQRLabel
        Size.Values = (
          44.9791666666667
          2206.625
          0
          71.4375)
        FontSize = 10
      end
      inherited Val9: TQRLabel
        Size.Values = (
          44.9791666666667
          2415.64583333333
          0
          71.4375)
        FontSize = 10
      end
      inherited Val10: TQRLabel
        Size.Values = (
          44.9791666666667
          2622.02083333333
          0
          89.9583333333333)
        FontSize = 10
      end
      object NomUnite: TQRLabel
        Left = 192
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
          508
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
    end
    inherited PageFooterBand1: TQRBand
      Top = 158
      Size.Values = (
        42.3333333333333
        2770.1875)
      inherited QRSysData2: TQRSysData
        Size.Values = (
          44.9791666666667
          2645.83333333333
          0
          21.1666666666667)
        FontSize = 10
      end
    end
  end
end
