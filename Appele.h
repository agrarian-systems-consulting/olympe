//---------------------------------------------------------------------------

#ifndef AppeleH
#define AppeleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TAppeleFrm: public TForm {
	__published: // Composants g�r�s par l'EDI
TLabel	*Label1;
	TBitBtn *BitBtn1;
	TBitBtn *BtBnAnimation;
	TAnimate *Logo1;
	void __fastcall BtBnAnimationClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall Logo1Stop(TObject *Sender);
private: // D�clarations de l'utilisateur
public:// D�clarations de l'utilisateur
	__fastcall TAppeleFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAppeleFrm *AppeleFrm;
//---------------------------------------------------------------------------
#endif
