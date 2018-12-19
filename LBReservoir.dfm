inherited LBReservoirFrm: TLBReservoirFrm
  Caption = 'LBReservoirFrm'
  OldCreateOrder = True
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  inherited LB: TListBox
    Top = 0
    Height = 295
    Align = alClient
    Items.Strings = ()
    OnClick = LBClick
  end
end
