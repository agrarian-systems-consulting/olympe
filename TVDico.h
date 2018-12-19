//---------------------------------------------------------------------------
#ifndef TVDicoH
#define TVDicoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TVChoix.h"
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TTVDicoFrm: public TTVChoixFrm {
	__published: // Composants gérés par l'EDIvoid __fastcall TVDblClick(TObject *Sender);void __fastcall TVDblClick(TObject *Sender);
TPanel	*PanBas;
	TBitBtn *BtBnRafraichir;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall TVDblClick(TObject *Sender);
	void __fastcall BtBnRafraichirClick(TObject *Sender);
private: // Déclarations de l'utilisateur
	TRichEdit *Edit;
	void __fastcall ClickIndic(void);
	void __fastcall ClickEtat(void);
	void __fastcall ClickResultat(void);
	void __fastcall ClickSerieComp(void);
	void __fastcall ClickAgri(void);
	void __fastcall ClickAction(void);

	void __fastcall CourbeEtat(CL_EtatSortie *etat);
	void EtablirNomMvtAni(AnsiString &aInserer,CL_Elt *elt);

	TStringGrid* LaGrille;
public:// Déclarations de l'utilisateur
	int Origine;
//    AnsiString VientDe;
	bool Complet;//Tv Contient tous les elements true ne contient que les éléments utilisés false
				 // cf Fome0Frm CreeTvToutElt
	CL_Agriculteur *Agri,*AncAgri;
	int AncTVItemCount;
	bool AncComplet;
	void TexteChaine(void);
	AnsiString L_Dico;
	AnsiString L_Raf;
	AnsiString TrouveMvtType(int type);

	__fastcall TTVDicoFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTVDicoFrm *TVDicoFrm;
//---------------------------------------------------------------------------
#endif
