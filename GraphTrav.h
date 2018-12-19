//---------------------------------------------------------------------------

#ifndef GraphTravH
#define GraphTravH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TGraphTravFrm: public TForm {
	__published: // Composants g�r�s par l'EDI
TLabel	*Label1;
	TShape *Shape1;
private: // D�clarations utilisateur
	int __fastcall Xde(int x);
	int __fastcall Yde(int y);

public:// D�clarations utilisateur
	void __fastcall Dessiner(void);
	__fastcall TGraphTravFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGraphTravFrm *GraphTravFrm;
//---------------------------------------------------------------------------
#endif
