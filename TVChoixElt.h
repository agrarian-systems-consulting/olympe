//---------------------------------------------------------------------------
#ifndef TVChoixEltH
#define TVChoixEltH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TVChoix.h"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TTVChoixEltFrm: public TTVChoixFrm {
	__published: // Composants gérés par l'EDIvoid __fastcall TVDblClick(TObject *Sender);void __fastcall TVDblClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);void __fastcall TVDblClick(TObject *Sender);
private:
	// Déclarations de l'utilisateur
	TRichEdit *Edit;void __fastcall ClickIndic(void);void __fastcall ClickEtat(void);void __fastcall ClickResultat(void);void __fastcall ClickSerieComp(void);void __fastcall ClickAgri(void);

	void __fastcall CourbeEtat(CL_EtatSortie *etat);

	TStringGrid* LaGrille;
public:
	// Déclarations de l'utilisateur
	int Origine;
	CL_Agriculteur *Agri;
	bool EstInitialise;
	__fastcall TTVChoixEltFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTVChoixEltFrm *TVChoixEltFrm;
//---------------------------------------------------------------------------
#endif
