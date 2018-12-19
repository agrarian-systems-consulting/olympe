//---------------------------------------------------------------------------
#ifndef FormatH
#define FormatH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFormatFrm: public TForm {
	__published: // Composants gérés par l'EDI
TRadioGroup	*RadioGroup;
	TGroupBox *GroupBoxTrait;
	TColorDialog *ColorDialog;
	TComboBox *ComboBoxTrait;
	TBitBtn *BitBtn1;
	TGroupBox *GroupBoxCouleur;
	TButton *ButtonColor;
	TPanel *PanelColor;
	TButton *Buttoncolorfond;
	TPanel *PanelColor2;
	TScrollBar *ScrollBarEpai;
	TLabel *LabelEpai;
	TGroupBox *GroupBoxLegende;
	TEdit *EditTitre;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *EditAbsG;
	TLabel *Label3;
	TEdit *EditOrd;
	TCheckBox *CheckBox3D;
	void __fastcall FormActivate(TObject *Sender);

	void __fastcall RadioGroupClick(TObject *Sender);
	void __fastcall ComboBoxTraitChange(TObject *Sender);

	void __fastcall ButtonColorClick(TObject *Sender);

	void __fastcall ButtoncolorfondClick(TObject *Sender);
	void __fastcall CheckBox3DClick(TObject *Sender);
	void __fastcall ScrollBarEpaiChange(TObject *Sender);
	void __fastcall EditTitreChange(TObject *Sender);
	void __fastcall EditAbsGChange(TObject *Sender);
	void __fastcall EditOrdChange(TObject *Sender);

private: // Déclarations de l'utilisateur
public:// Déclarations de l'utilisateur
	__fastcall TFormatFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormatFrm *FormatFrm;
//---------------------------------------------------------------------------
#endif
