//---------------------------------------------------------------------------

#ifndef RaccourciH
#define RaccourciH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TRaccourciFrm: public TForm {
	__published: // Composants g�r�s par l'EDI
TPanel	*PanH;
	TPanel *PanB;
	TStringGrid *SG;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
private: // D�clarations de l'utilisateur
public:// D�clarations de l'utilisateur
	__fastcall TRaccourciFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TRaccourciFrm *RaccourciFrm;
//---------------------------------------------------------------------------
#endif
