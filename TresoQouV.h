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
	__published: // Composants g�r�s par l'EDI
TRadioGroup	*RGQouV;
	TBitBtn *BtOk;
	void __fastcall RGQouVClick(TObject *Sender);
	void __fastcall BtOkClick(TObject *Sender);
private: // D�clarations de l'utilisateur
public:// D�clarations de l'utilisateur
	__fastcall TTresoQouVFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTresoQouVFrm *TresoQouVFrm;
//---------------------------------------------------------------------------
#endif
