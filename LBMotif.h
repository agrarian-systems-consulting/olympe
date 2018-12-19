//---------------------------------------------------------------------------

#ifndef LBMotifH
#define LBMotifH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>

//---------------------------------------------------------------------------
class TLBMotifFrm: public TForm {
	__published: // Composants gérés par l'EDI
TBitBtn	*BtBnFermer;
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
			TShiftState Shift, int X, int Y);
private: // Déclarations utilisateur
	int X0,Y0,Largeur,Hauteur;
public:// Déclarations utilisateur
	CL_Atelier *Atelier;
	__fastcall TLBMotifFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLBMotifFrm *LBMotifFrm;
//---------------------------------------------------------------------------
#endif
