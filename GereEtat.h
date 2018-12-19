//---------------------------------------------------------------------------

#ifndef GereEtatH
#define GereEtatH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "GereAtelier.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TGereEtatFrm: public TGereAtelierFrm {
	__published: // Composants gérés par l'EDI
	void __fastcall FormActivate(TObject *Sender);void __fastcall TVDblClick(TObject *Sender);void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);void __fastcall TVClick(TObject *Sender);void __fastcall BtAtelierCopierClick(TObject *Sender);void __fastcall BtAtelierCreerClick(TObject *Sender);void __fastcall BtAtelierSupprimerClick(TObject *Sender);void __fastcall BtAtelierModifClick(TObject *Sender);void __fastcall BtCatCopierClick(TObject *Sender);bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
protected:
	void __fastcall CalculDonnees(void);virtual void __fastcall AffAtelier(void);virtual bool __fastcall VerifNomAtelier(AnsiString newNom,int action);virtual bool __fastcall CEstBon(void);virtual void __fastcall StockerOrdre(void);virtual void __fastcall CreeTV(void);
	CL_EtatSortie *Etat;
	CL_Vecteur<CL_EtatSortie> *V_Etat;

private:
	// Déclarations utilisateur
	// utilisé pour pointer sur V_EtatSortie ou V_Comparaison
public:
	// Déclarations utilisateur
//    int Nature;
	void TexteChaine();
	AnsiString L_NCatCopDe;
	AnsiString L_PasSel;
	AnsiString L_NEtat;
	AnsiString L_NComp;
	AnsiString L_Sup;
	AnsiString L_RienACop;
	AnsiString L_Prob;
	AnsiString L_Impo;
	AnsiString L_ModNom;
	AnsiString L_PasNom;
	AnsiString L_Existe;
	AnsiString L_Erreur;
	AnsiString L_CopDe;

	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_GBAtelier;
	AnsiString LC_GereEtatFrm;

	__fastcall TGereEtatFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGereEtatFrm *GereEtatFrm;
//---------------------------------------------------------------------------
#endif
