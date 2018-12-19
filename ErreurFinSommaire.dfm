inherited ErreurFinSommaireFrm: TErreurFinSommaireFrm
  Left = 1102
  Top = 217
  Caption = 'ErreurFinSommaireFrm'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  inherited GB: TGroupBox
    inherited RE: TRichEdit
      Lines.Strings = (
        'La Formule'
        'Dette[n]='
        '       Dette(n-1)'
        '       -  Remboursement(n)'
        '       + Nouveau(n)'
        ' '
        'N'#39'EST PAS VERIFIEE !'
        ''
        ''
        '')
    end
  end
  inherited RG: TRadioGroup
    Items.Strings = (
      ' Dette'
      ' Remboursement'
      ' Ne rien faire')
  end
end
