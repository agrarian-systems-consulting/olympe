//---------------------------------------------------------------------------

#ifndef AgriMargeAtelierH
#define AgriMargeAtelierH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Forme00.h"
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TAgriMargeAtelierFrm: public TForme00Frm {
	__published: // Composants gérés par l'EDI
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:
	// Déclarations utilisateur

protected:
	virtual void __fastcall Personnaliser(void);virtual void __fastcall DefinirLesGrilles(void);virtual void __fastcall IniGrille(TStringGrid *grille);virtual void __fastcall VersGrille(TStringGrid *grille);

public:
	// Déclarations utilisateur
	CL_Agriculteur *Agri;
	CL_Vecteur<CL_QuanVal> *V_Produit;
	CL_Vecteur<CL_QuanVal> *V_Charge;
	CL_Vecteur<CL_QuanVal> *V_Exter;

	__fastcall TAgriMargeAtelierFrm(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TAgriMargeAtelierFrm *AgriMargeAtelierFrm;
//---------------------------------------------------------------------------
#endif
