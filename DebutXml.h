//---------------------------------------------------------------------------

#ifndef DebutXmlH
#define DebutXmlH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TDebutXmlFrm: public TForm {
	__published: // Composants gérés par l'EDI
TOpenDialog	*OpenDialog;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TLabel *LabDuree;
	TEdit *EdDuree;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall BitBtn2Click(TObject *Sender);
private: // Déclarations de l'utilisateur
public:// Déclarations de l'utilisateur
	__fastcall TDebutXmlFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDebutXmlFrm *DebutXmlFrm;
//---------------------------------------------------------------------------
#endif
