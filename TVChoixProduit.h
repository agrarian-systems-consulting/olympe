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
	__published: // Composants gérés par l'EDI
TTreeView	*TV;
	void __fastcall TVClick(TObject *Sender);
private: // Déclarations utilisateur
public:// Déclarations utilisateur
	__fastcall TTVChoixProduitFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTVChoixProduitFrm *TVChoixProduitFrm;
//---------------------------------------------------------------------------
#endif
