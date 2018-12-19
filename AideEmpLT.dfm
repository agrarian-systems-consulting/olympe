object AideEmpLTFrm: TAideEmpLTFrm
  Left = 199
  Top = 110
  Width = 207
  Height = 377
  Caption = 'LT'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object RichEdit1: TRichEdit
    Left = 0
    Top = 0
    Width = 199
    Height = 350
    TabStop = False
    Align = alClient
    BorderStyle = bsNone
    BorderWidth = 2
    Color = clBtnFace
    Lines.Strings = (
      'AAAAAAAAA'
      'BBBBBBBBBBB')
    ReadOnly = True
    TabOrder = 0
    OnContextPopup = RichEdit1ContextPopup
    OnEnter = RichEdit1Enter
    OnSelectionChange = RichEdit1SelectionChange
  end
end
