//---------------------------------------------------------------------------

#ifndef TVChoixProduitH
#define TVChoixProduitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TTVChoixProduitFrm: public TForm {
	__published: // Composants g�r�s par l'EDI
TTreeView	*TV;
	void __fastcall TVClick(TObject *Sender);
private: // D�clarations utilisateur
public:// D�clarations utilisateur
	__fastcall TTVChoixProduitFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTVChoixProduitFrm *TVChoixProduitFrm;
//---------------------------------------------------------------------------
#endif
