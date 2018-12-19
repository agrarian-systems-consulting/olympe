//---------------------------------------------------------------------------

#ifndef TresoQouVH
#define TresoQouVH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TTresoQouVFrm: public TForm {
	__published: // Composants gérés par l'EDI
TRadioGroup	*RGQouV;
	TBitBtn *BtOk;
	void __fastcall RGQouVClick(TObject *Sender);
	void __fastcall BtOkClick(TObject *Sender);
private: // Déclarations de l'utilisateur
public:// Déclarations de l'utilisateur
	__fastcall TTresoQouVFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTresoQouVFrm *TresoQouVFrm;
//---------------------------------------------------------------------------
#endif
